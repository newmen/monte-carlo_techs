#include <ctime>
#include <cstdlib>
#include <iostream>

#include "app/datas/area_data.h"

#include "app/contexts/abcdcellreactor_context.h"
#include "app/contexts/abcddimerreactor_context.h"
#include "app/contexts/nocoreactor_context.h"
#include "app/contexts/lotkareactor_context.h"

#include "app/contexts/rejectionsimulation_context.h"
#include "app/contexts/rejectionfreesimulation_context.h"
#include "app/contexts/dynamicsimulation_context.h"
#include "app/contexts/kineticsimulation_context.h"
#include "app/contexts/treebasedsimulation_context.h"
#include "app/contexts/store_context.h"

template <class SimulationContext>
void run() {
    AreaData area(100, 100);
//    AreaData area(13, 13);

//    ABCDCellReactorContext reactor;
//    ABCDDimerReactorContext reactor;
    NOCOReactorContext reactor;
//    LotkaReactorContext reactor;

    SimulationContext sc(&area, &reactor);
    long double dt, totalTime = 0;
    int counter = 0, iterations = 0;
    do {
        EventInfoData ei = sc.doReaction();
        dt = ei.dt();
        totalTime += dt;

        if (dt > reactor.maxTime()) {
            std::cout << "Overtime! " << dt << " sec. "
                      << "It is a " << ((ei.cell() == 0) ? "dimer" : "cell") << " reaction" << std::endl;
        }

        iterations++;
        if (counter++ == 100000) {
            std::cout << "Intermediate time: " << totalTime << " sec" << std::endl;
            counter = 0;
//            break;
        }
    } while (dt > 0 && totalTime < reactor.maxTime());

    std::cout << "Total time: " << totalTime << " sec" << std::endl;
    std::cout << "Iterations: " << iterations << std::endl;
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
