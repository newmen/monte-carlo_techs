#include <cstdlib>
#include <ctime>
#include <iostream>
#include "process_mem_usage.h"

#include "area_data.h"
#include "dynamicsimulation_context.h"
#include "kineticsimulation_context.h"
#include "rejectionsimulation_context.h"
#include "rejectionfreesimulation_context.h"

using namespace std;

template <class SimulationContext>
void runTest(const char *name, const int sizeX, const int sizeY, const int repeats) {
    cout << name << endl;

    float totalTime = 0, dt = 0;
    int iterations = 0;

    AreaData *area = 0;
    SimulationBaseContext *simulationContext = 0;

    time_t startTime = time(0);

    for (int i = 0; i < repeats; ++i) {
        area = new AreaData(sizeX, sizeY);
        simulationContext = new SimulationContext(area);

        while (true) {
            dt = simulationContext->doReaction();
            if (dt == 0) break;

            totalTime += dt;
            ++iterations;
        }

        delete simulationContext;
        delete area;
    }

    time_t stopTime = time(0);

    cout << "Total process time: " << (totalTime / repeats)
         << " (sec); Iterations: " << ((float)iterations / repeats) << endl;

    double vm, rss;
    process_mem_usage(vm, rss);
    cout << "VM: " << vm << "; RSS: " << rss << endl;
    cout << "Calculating time: " << (stopTime - startTime) << " seconds\n" << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Wrong test running! Try this:\n"
             << argv[0] << " sizeX sizeY repeats" << endl;
        return 1;
    }
    const int sizeX = atoi(argv[1]), sizeY = atoi(argv[2]);
    const int repeats = atoi(argv[3]);

    cout << "Running with:\n"
         << "sizeX = " << sizeX << "\n"
         << "sizeY = " << sizeY << "\n"
         << "repeats = " << repeats << "\n" << endl;

    srand(time(0));
    runTest<DynamicSimulationContext>("Dynamic MC", sizeX, sizeY, repeats);
    runTest<KineticSimulationContext>("Kinetic MC", sizeX, sizeY, repeats);
    runTest<RejectionSimulationContext>("Rejection MC", sizeX, sizeY, repeats);
    runTest<RejectionFreeSimulationContext>("Rejection-free MC", sizeX, sizeY, repeats);

    return 0;
}
