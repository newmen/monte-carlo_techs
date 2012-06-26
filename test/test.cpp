#include <sys/time.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "process_mem_usage.h"
#include "pathbuilder.h"
#include "performancesaver.h"
#include "solving_ode.h"

#include "area_data.h"
#include "dynamicsimulation_context.h"
#include "kineticsimulation_context.h"
#include "rejectionsimulation_context.h"
#include "rejectionfreesimulation_context.h"
#include "treebasedsimulation_context.h"
#include "store_context.h"

#define MAX_TIME 2.0

using namespace std;

struct TestConfig {
    const PathBuilder pathBuilder;
    PerformanceSaver perfSaver;
    const int sizeX, sizeY;
    const int repeats;
    const bool needGraph;

    TestConfig(const char *resultDir, int sizeX, int sizeY, int repeats, bool needGraph) :
        pathBuilder(resultDir), perfSaver(&pathBuilder),
        sizeX(sizeX), sizeY(sizeY), repeats(repeats),
        needGraph(needGraph) {}
};

template <class SimulationContext>
void runTest(TestConfig *tc, const char *name, const char *fileName)
{
    const string fullFilePath = tc->pathBuilder.buildPath(fileName, "mcr");

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
        simulationContext = new SimulationContext(area);
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
        tc->perfSaver.storeValue("times", size, calcTime);
        tc->perfSaver.storeValue("iterations", size, meanIterations);
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
        const string originalFileName = tc.pathBuilder.buildPath("original", "mcr");
        solveODE(originalFileName.c_str(), MAX_TIME);
        tc.pathBuilder.printFileWasSaved(originalFileName);
    }

    srand(time(0));
//    runTest<DynamicSimulationContext>(&tc, "Dynamic MC", "dynamic");
//    runTest<KineticSimulationContext>(&tc, "Kinetic MC", "kinetic");
//    runTest<RejectionSimulationContext>(&tc, "Rejection MC", "rejection");
//    runTest<RejectionFreeSimulationContext>(&tc, "Rejection-free MC", "rejection-free");

    runTest<TreeBasedSimulationContext<2000> >(&tc, "Faster <2000> MC", "faster_2000");
    runTest<TreeBasedSimulationContext<1000> >(&tc, "Faster <1000> MC", "faster_1000");
    runTest<TreeBasedSimulationContext<500> >(&tc, "Faster <500> MC", "faster_500");
    runTest<TreeBasedSimulationContext<200> >(&tc, "Faster <200> MC", "faster_200");
    runTest<TreeBasedSimulationContext<100> >(&tc, "Faster <100> MC", "faster_100");
    runTest<TreeBasedSimulationContext<50> >(&tc, "Faster <50> MC", "faster_50");
    runTest<TreeBasedSimulationContext<20> >(&tc, "Faster <20> MC", "faster_20");
    runTest<TreeBasedSimulationContext<10> >(&tc, "Faster <10> MC", "faster_10");
    runTest<TreeBasedSimulationContext<5> >(&tc, "Faster <5> MC", "faster_5");
    runTest<TreeBasedSimulationContext<2> >(&tc, "Faster Binary MC", "faster_binary");

    return 0;
}
