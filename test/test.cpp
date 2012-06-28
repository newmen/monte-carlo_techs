#include <sys/time.h>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "process_mem_usage.h"
#include "pathbuilder.h"
#include "performancesaver.h"
#include "solving_ode.h"

#include "typicalsimcontextfactory.h"
#include "treesimcontextfactory.h"

#include "../area_data.h"
#include "../dynamicsimulation_context.h"
#include "../kineticsimulation_context.h"
#include "../rejectionsimulation_context.h"
#include "../rejectionfreesimulation_context.h"
#include "../treebasedsimulation_context.h"
#include "../store_context.h"

#define MAX_TIME 2.0
#define GRAPH_EXT "mcr"

using namespace std;

struct TestConfig {
    const PathBuilder pathBuilder;
    PerformanceSaver perfSaver;
    SimulationContextFactory *simFactory;
    const int sizeX, sizeY;
    const int repeats;
    const bool needGraph;

    TestConfig(const char *resultDir, int sizeX, int sizeY, int repeats, bool needGraph) :
        pathBuilder(resultDir), perfSaver(&pathBuilder), simFactory(0),
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

void runTest(TestConfig *tc, const char *name, const char *fileName)
{
    const char graphExt[] = GRAPH_EXT;
    const string fullFilePath = tc->pathBuilder.buildPath(fileName, graphExt);

    cout << name << endl;
    if (!tc->needGraph) tc->perfSaver.storeName(name);

    AreaData *area = 0;
    SimulationBaseContext *simulationContext = 0;
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

    double totalTime, dt;
    unsigned long long iterations = 0;
    for (int i = 0; i < tc->repeats; ++i) {
        freeUpMemory();

        area = new AreaData(tc->sizeX, tc->sizeY);
        simulationContext = tc->simFactory->createContext(area);
        if (tc->needGraph) {
            storeContext = new StoreContext(area, fullFilePath.c_str(), name);
        }

        totalTime = 0;
        while (totalTime < MAX_TIME) {
            dt = simulationContext->doReaction();
            if (tc->needGraph) storeContext->store(dt);
            if (dt == 0.0) break;

            totalTime += dt;
            ++iterations;
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

    TestConfig tc(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]),
                  (argc == 6 && strcmp(argv[5], "true") == 0));

    cout << "Running with:\n"
         << "sizeX = " << tc.sizeX << "\n"
         << "sizeY = " << tc.sizeY << "\n"
         << "repeats = " << tc.repeats << "\n" << endl;

    if (tc.needGraph) {
        const string originalFileName = tc.pathBuilder.buildPath("original", GRAPH_EXT);
        solveODE(originalFileName.c_str(), MAX_TIME);
        tc.pathBuilder.printFileWasSaved(originalFileName);
    }

    srand(time(0));
//    tc.changeFactory(new TypicalSimContextFactory<DynamicSimulationContext>);
//    runTest(&tc, "Dynamic MC", "dynamic");
//    tc.changeFactory(new TypicalSimContextFactory<KineticSimulationContext>);
//    runTest(&tc, "Kinetic MC", "kinetic");
//    tc.changeFactory(new TypicalSimContextFactory<RejectionSimulationContext>);
//    runTest(&tc, "Rejection MC", "rejection");
//    tc.changeFactory(new TypicalSimContextFactory<RejectionFreeSimulationContext>);
//    runTest(&tc, "Rejection-free MC", "rejection-free");


    int size = tc.sizeX * tc.sizeY;
    int maxWidth = calcTreeWidthByK(size, 0.5);
    int minWidth = 2;
    TreeSimContextFactory *factory = new TreeSimContextFactory(maxWidth);
    tc.changeFactory(factory);
    runTest(&tc, "Faster Sqrt MC", "faster_sqrt");
    factory->setWidth(minWidth);
    runTest(&tc, "Faster Binary MC", "faster_binary");

    int optimalWidth = optimalTreeWidth(size);
    if (optimalWidth < minWidth) optimalWidth = minWidth;
    factory->setWidth(optimalWidth);
    runTest(&tc, "Faster Optimal MC", "faster_optimal");
    int lessWidth = optimalWidth - 1;
    if (lessWidth < minWidth) lessWidth = minWidth;
    factory->setWidth(lessWidth);
    runTest(&tc, "Faster Less MC", "faster_less");
    int moreWidth = optimalWidth + 1;
    if (moreWidth > maxWidth) moreWidth = maxWidth;
    factory->setWidth(moreWidth);
    runTest(&tc, "Faster More MC", "faster_more");

    return 0;
}
