#include <ctime>
#include <cstdlib>
#include <iostream>

#include "area_data.h"

#include "abcdcellreactor_context.h"
#include "abcddimerreactor_context.h"
#include "nocoreactor_context.h"

#include "rejectionsimulation_context.h"
#include "rejectionfreesimulation_context.h"
#include "dynamicsimulation_context.h"
#include "kineticsimulation_context.h"
#include "treebasedsimulation_context.h"
#include "store_context.h"

template <class SimulationContext>
void run() {
    AreaData area(5, 5);
//    AreaData area(13, 13);

//    ABCDCellReactorContext reactor;
//    ABCDDimerReactorContext reactor;
    NOCOReactorContext reactor;

    SimulationContext sc(&area, &reactor);
    double dt, totalTime = 0;
    int counter = 0;
    do {
        EventInfoData ei = sc.doReaction();
        dt = ei.dt();
        totalTime += dt;

        if (counter++ == 100000) {
            std::cout << "Intermediate time: " << totalTime << std::endl;
            counter = 0;
//            break;
        }
    } while (dt > 0 && totalTime < reactor.maxTime());

    std::cout << "Total time: " << totalTime << " sec" << std::endl;
}

int main() {
    srand(time(0));

    std::cout << "Running..." << std::endl;

//    run<RejectionSimulationContext>();
//    run<RejectionFreeSimulationContext>();
//    run<DynamicSimulationContext>();
//    run<KineticSimulationContext>();
    run<TreeBasedSimulationContext>();

    std::cout << "Complete :)" << std::endl;

    return 0;
}
