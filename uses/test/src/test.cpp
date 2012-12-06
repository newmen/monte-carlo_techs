#include <sys/time.h>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "process_mem_usage.h"
#include "pathbuilder.h"
#include "performancesaver.h"

#include "typicalsimcontextfactory.h"
#include "treesimcontextfactory.h"

#include <datas/area_data.h>
#include <contexts/abcdcellreactor_context.h>
#include <contexts/abcddimerreactor_context.h>
#include <contexts/nocoreactor_context.h>
#include <contexts/lotkareactor_context.h>
#include <contexts/lotkathreereactor_context.h>

#include <contexts/dynamicsimulation_context.h>
#include <contexts/kineticsimulation_context.h>
#include <contexts/rejectionsimulation_context.h>
#include <contexts/rejectionfreesimulation_context.h>
#include <contexts/treebasedsimulation_context.h>

#include <contexts/store_concentrations_context.h>
#include <contexts/storeshot_context.h>
#include <contexts/storeevent_context.h>

#define GRAPH_CONC_EXT "mcr"
#define GRAPH_SHOT_EXT "mcs"
#define GRAPH_EVENT_EXT "mcd"

using namespace std;

struct TestConfig {
    const PathBuilder pathBuilder;
    PerformanceSaver perfSaver;
    SimulationContextFactory *simFactory;
    const BaseReactorContext *reactor;
    const int sizeX, sizeY;
    const int repeats;
    const bool needGraph;

    TestConfig(BaseReactorContext *reactor, const string &resultDir, int sizeX, int sizeY, int repeats, bool needGraph) :
        pathBuilder(resultDir), perfSaver(&pathBuilder), simFactory(0), reactor(reactor),
        sizeX(sizeX), sizeY(sizeY), repeats(repeats),
        needGraph(needGraph) {}

    ~TestConfig() {
        delete simFactory;
    }

    void changeFactory(SimulationContextFactory *factory) {
        delete simFactory;
        simFactory = factory;
    }
};

void runTest(TestConfig *tc, const string &name, const string &fileName)
{
    const string graphConcExt = GRAPH_CONC_EXT;
    const string fullFileConcPath = tc->pathBuilder.buildPath(fileName, graphConcExt);
//    const string graphEventExt = GRAPH_EVENT_EXT;
//    const string fullFileEventPath = tc->pathBuilder.buildPath(fileName, graphEventExt);
    const string graphShotExt = GRAPH_SHOT_EXT;
    const string fullFileShotPath = tc->pathBuilder.buildPath(fileName, graphShotExt);

    cout << name << endl;
    if (!tc->needGraph) tc->perfSaver.storeName(name);

    AreaData *area = 0;
    BaseSimulationContext *simulationContext = 0;
    StoreConcentrationsContext *storeConcContext = 0;
//    StoreEventContext *storeEventContext = 0;
    StoreShotContext *storeShotContext = 0;
    auto freeUpMemory = [&area, &simulationContext, &storeConcContext, &storeShotContext]() {
        delete storeShotContext;
//        delete storeEventContext;
        delete storeConcContext;
        delete simulationContext;
        delete area;
    };

    timeval tv;
    auto currTime = [&tv]() {
        gettimeofday(&tv, 0);
        return tv.tv_sec + tv.tv_usec / 1e6;
    };
    double startTime = currTime();

    long double totalTime, dt;
    unsigned long long iterations = 0;
    auto storeLambda = [&totalTime, &storeConcContext, &storeShotContext]() {
        storeConcContext->store(totalTime);
//        storeShotContext->store(totalTime);
    };

    for (int i = 0; i < tc->repeats; ++i) {
        freeUpMemory();

        area = new AreaData(tc->sizeX, tc->sizeY);
        simulationContext = tc->simFactory->createContext(area, tc->reactor);
        if (tc->needGraph) {
            storeConcContext = new StoreConcentrationsContext(fullFileConcPath, name, area, tc->reactor->numOfSpecs());
//            storeShotContext = new StoreShotContext(fullFileShotPath, area);
//            storeEventContext = new StoreEventContext(fullFileEventPath, *area);
        }

        totalTime = 0;
        long double counter = 0.0;
        while (totalTime < tc->reactor->maxTime()) {
            EventInfoData ei = simulationContext->doReaction();
            dt = ei.dt();
            if (tc->needGraph) {
//                storeEventContext->storeByInfo(ei);
                if (counter > tc->reactor->timeStep()) {
                    storeLambda();
                    counter = 0;
                }
            }
            if (dt == -1.0) {
                std::cout << "Stacionar" << std::endl;
                break;
            }

            counter += dt;
            totalTime += dt;
            ++iterations;
        }
        if (tc->needGraph && counter != 0) { // last value
            storeLambda();
        }
    }

    double stopTime = currTime();

    double meanIterations = (double)iterations / tc->repeats;
    cout << "Total process time: " << totalTime
         << " (sec); Iterations: " << meanIterations << endl;

    double vm, rss;
    process_mem_usage(vm, rss);
    cout << "VM: " << vm << "; RSS: " << rss << endl;
    double calcTime = (stopTime - startTime) / tc->repeats;
    cout << "Calculating time: " << calcTime << " seconds" << endl;

    if (tc->needGraph) tc->pathBuilder.printFileWasSaved(fullFileConcPath);
    else {
        cout << endl;

        unsigned int size = tc->sizeX * tc->sizeY;
        tc->perfSaver.storeValue("iterations", size, meanIterations);
        tc->perfSaver.storeValue("times", size, calcTime);
        tc->perfSaver.storeValue("virtuals", size, vm);
        tc->perfSaver.storeValue("rss", size, rss);
    }

    freeUpMemory();
}

int main(int argc, char *argv[]) {
    if (argc < 5 || argc > 6) {
        cerr << "Wrong test running! Try this:\n"
             << argv[0] << " resultDirPath sizeX sizeY repeats store?" << endl;
        return 1;
    }

//    ABCDCellReactorContext reactor;
    NOCOReactorContext reactor;
//    LotkaReactorContext reactor;
    TestConfig tc(&reactor, argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]),
                  (argc == 6 && strcmp(argv[5], "true") == 0));

    cout << "Running with:\n"
         << "sizeX = " << tc.sizeX << "\n"
         << "sizeY = " << tc.sizeY << "\n"
         << "repeats = " << tc.repeats << "\n" << endl;

    if (tc.needGraph) {
        const string originalFileName = tc.pathBuilder.buildPath("original", GRAPH_CONC_EXT);
        reactor.solve(originalFileName);
        tc.pathBuilder.printFileWasSaved(originalFileName);
    }

    srand(time(0));

//    tc.changeFactory(new TypicalSimContextFactory<RejectionSimulationContext>);
//    runTest(&tc, "Метод отказа", "rejection");
//    tc.changeFactory(new TypicalSimContextFactory<RejectionFreeSimulationContext>);
//    runTest(&tc, "Метод частичных сумм", "rejection-free");
//    tc.changeFactory(new TypicalSimContextFactory<DynamicSimulationContext>);
//    runTest(&tc, "Динамический метод", "dynamic");
//    tc.changeFactory(new TypicalSimContextFactory<KineticSimulationContext>);
//    runTest(&tc, "Кинетический метод", "kinetic");

//    TreeSimContextFactory *factory = new TreeSimContextFactory(2);
//    tc.changeFactory(factory);
//    runTest(&tc, "Многоуровневый метод (кв. корень)", "faster_sqrt");
//    factory->setWidth((int)log2(tc.sizeX * tc.sizeY));
//    runTest(&tc, "Многоуровневый метод (бинарный)", "faster_binary");

//    factory->setWidth(3);
//    runTest(&tc, "Многоуровневый метод (4 уровня)", "faster_3");

//    factory->setWidth(4);
//    runTest(&tc, "Faster 5 MC", "faster_5");
//    factory->setWidth(6);
//    runTest(&tc, "Faster 6 MC", "faster_6");

    tc.changeFactory(new TypicalSimContextFactory<TreeBasedSimulationContext>);
    runTest(&tc, "Многоуровневый метод (5 уровней)", "faster_optimal");

    return 0;
}
