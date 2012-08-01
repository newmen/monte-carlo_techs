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
#include <contexts/store_context.h>

#define GRAPH_EXT "mcr"

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
    const string graphExt = GRAPH_EXT;
    const string fullFilePath = tc->pathBuilder.buildPath(fileName, graphExt);

    cout << name << endl;
    if (!tc->needGraph) tc->perfSaver.storeName(name);

    AreaData *area = 0;
    BaseSimulationContext *simulationContext = 0;
    StoreContext *storeContext = 0;
    auto freeUpMemory = [&area, &simulationContext, &storeContext]() {
        delete storeContext;
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
    for (int i = 0; i < tc->repeats; ++i) {
        freeUpMemory();

        area = new AreaData(tc->sizeX, tc->sizeY);
        simulationContext = tc->simFactory->createContext(area, tc->reactor);
        if (tc->needGraph) {
            storeContext = new StoreContext(area, tc->reactor->numOfSpecs(), fullFilePath, name);
        }

        totalTime = 0;
        long double counter = 0.0;
        while (totalTime < tc->reactor->maxTime()) {
            EventInfoData ei = simulationContext->doReaction();
            dt = ei.dt();
            if (tc->needGraph && counter > tc->reactor->timeStep()) {
                storeContext->store(totalTime);
                counter = 0;
            }
            if (dt == 0.0) {
                std::cout << "Stacionar" << std::endl;
                break;
            }

            counter += dt;
            totalTime += dt;
            ++iterations;
        }
        if (tc->needGraph && counter != 0) storeContext->store(totalTime); // last value
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

    if (tc->needGraph) tc->pathBuilder.printFileWasSaved(fullFilePath);
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

    ABCDCellReactorContext reactor;
//    NOCOReactorContext reactor;
//    LotkaReactorContext reactor;
    TestConfig tc(&reactor, argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]),
                  (argc == 6 && strcmp(argv[5], "true") == 0));

    cout << "Running with:\n"
         << "sizeX = " << tc.sizeX << "\n"
         << "sizeY = " << tc.sizeY << "\n"
         << "repeats = " << tc.repeats << "\n" << endl;

    if (tc.needGraph) {
        const string originalFileName = tc.pathBuilder.buildPath("original", GRAPH_EXT);
        reactor.solve(originalFileName);
        tc.pathBuilder.printFileWasSaved(originalFileName);
    }

    srand(time(0));

    tc.changeFactory(new TypicalSimContextFactory<RejectionSimulationContext>);
    runTest(&tc, "Rejection MC", "rejection");
    tc.changeFactory(new TypicalSimContextFactory<RejectionFreeSimulationContext>);
    runTest(&tc, "Rejection-free MC", "rejection-free");
    tc.changeFactory(new TypicalSimContextFactory<DynamicSimulationContext>);
    runTest(&tc, "Dynamic MC", "dynamic");
    tc.changeFactory(new TypicalSimContextFactory<KineticSimulationContext>);
    runTest(&tc, "Kinetic MC", "kinetic");

    TreeSimContextFactory *factory = new TreeSimContextFactory(2);
    tc.changeFactory(factory);
    runTest(&tc, "Faster Sqrt MC", "faster_sqrt");
    factory->setWidth((int)log2(tc.sizeX * tc.sizeY));
    runTest(&tc, "Faster Binary MC", "faster_binary");

    factory->setWidth(3);
    runTest(&tc, "Faster 3 MC", "faster_3");
    factory->setWidth(4);
    runTest(&tc, "Faster 4 MC", "faster_4");
    factory->setWidth(6);
    runTest(&tc, "Faster 6 MC", "faster_6");

    tc.changeFactory(new TypicalSimContextFactory<TreeBasedSimulationContext>);
    runTest(&tc, "Faster Optimal (5) MC", "faster_optimal");

    return 0;
}
