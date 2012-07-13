#include <ctime>
#include <cstdlib>
#include <iostream>
#include "area_data.h"
#include "rejectionsimulation_context.h"
#include "rejectionfreesimulation_context.h"
#include "dynamicsimulation_context.h"
#include "kineticsimulation_context.h"
#include "treebasedsimulation_context.h"
#include "store_context.h"

#include "abcdcellreactor_data.h"
#include "abcddimerreactor_data.h"

template <class SimulationContext>
void run() {
//    AreaData area(5, 5);
    AreaData area(12, 12);

    ABCDCellReactorData reactor;
//    ABCDDimerReactorContext reactor;

    SimulationContext sc(&area, &reactor);
    double dt, totalTime = 0;
    do {
        dt = sc.doReaction();
        totalTime += dt;
    } while (dt > 0);

    std::cout << "Total time: " << totalTime << " sec" << std::endl;
}

int main() {
    srand(time(0));

    std::cout << "Running..." << std::endl;

    run<RejectionSimulationContext>();
    run<RejectionFreeSimulationContext>();
    run<DynamicSimulationContext>();
    run<KineticSimulationContext>();
    run<TreeBasedSimulationContext>();

    std::cout << "Complete :)" << std::endl;

    return 0;
}
