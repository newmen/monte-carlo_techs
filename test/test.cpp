#include <cstdlib>
#include <ctime>
#include <iostream>
#include "process_mem_usage.h"

#include "area_data.h"
#include "dynamicsimulation_context.h"
#include "kineticsimulation_context.h"

using namespace std;

template <class SimulationContext>
void runTest(const char *name, const int sizeX, const int sizeY) {
    cout << name << endl;

    const long long repeats = 10;
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
         << " s; Iterations: " << ((float)iterations / repeats) << endl;

    double vm, rss;
    process_mem_usage(vm, rss);
    cout << "VM: " << vm << "; RSS: " << rss << endl;
    cout << "Calculating time: " << (stopTime - startTime) << "\n" << endl;
}

int main() {
    srand(time(0));
    const int sizeX = 50, sizeY = 50;

    runTest<DynamicSimulationContext>("Dynamic MC", sizeX, sizeY);
    runTest<KineticSimulationContext>("Kinetic MC", sizeX, sizeY);

    return 0;
}
