#include <ctime>
#include <cstdlib>
#include <iostream>

#include "datas/area_data.h"

#include "contexts/abcdcellreactor_context.h"
#include "contexts/abcddimerreactor_context.h"
#include "contexts/lotkareactor_context.h"
#include "contexts/simplenocoreactor_context.h"
#include "contexts/fullnocoreactor_context.h"

#include "contexts/eventbasedsimulation_context.h"
#include "contexts/optimizedeventbasedsimulation_context.h"
#include "contexts/rejectionsimulation_context.h"
#include "contexts/rejectionfreesimulation_context.h"
#include "contexts/muchoptimizedrejectionfreesimulation_context.h"
#include "contexts/dynamicsimulation_context.h"
#include "contexts/optimizeddynamicsimulation_context.h"
#include "contexts/kineticsimulation_context.h"
#include "contexts/treebasedsimulation_context.h"

#include "contexts/readshot_context.h"
#include "contexts/storeshot_context.h"
#include "contexts/store_concentrations_context.h"

#define FILE_NAME "/home/newmen/c++/monte_carlo_techs/uses/test/results/full_noco/faster-tree"
//#define FILE_NAME "oe"

template <class SimulationContext>
void run() {
//    ABCDCellReactorContext reactor;
//    ABCDDimerReactorContext reactor;
//    LotkaReactorContext reactor;
    SimpleNOCOReactorContext reactor;
//    FullNOCOReactorContext reactor;

    std::string mcr = std::string(FILE_NAME) + std::string(".mcr");
    std::string mcs = std::string(FILE_NAME) + std::string(".mcs");

//    std::cout << "Opening " << mcs << std::endl;
//    ReadShotContext reader(mcs);
//    Point2D sizes = reader.areaSizes();
//    std::cout << "Readed: x = " << sizes.x << ", y = " << sizes.y << std::endl;
//    AreaData area(sizes.x, sizes.y);
    AreaData area(50, 50);

    long double dt, totalTime = 0;
    SimulationContext sc(&area, &reactor);
//    // сначала распределили случайно из реактора по ареа, а потом задали ласт шот.. :(
//    totalTime = reader.setLastShotToArea(&area);
//    reader.close();

    StoreConcentrationsContext concStorage(mcr, "faster_optimal", &area, reactor.numOfSpecs());
    StoreShotContext shotStorage(mcs, &area);
    auto storeLambda = [&totalTime, &concStorage, &shotStorage]() {
        std::cout << "Stored " << totalTime << std::endl;
        concStorage.store(totalTime);
        shotStorage.store(totalTime);
    };

    std::cout << "Initialization complete" << std::endl;

    long double counter = 0.0;
    int iterations = 0;
    do {
        EventInfoData ei = sc.doReaction();
        dt = ei.dt();
        if (dt == -1.0) {
            std::cout << "Stacionar" << std::endl;
            break;
        }

        totalTime += dt;
        counter += dt;
        iterations++;

        if (dt > reactor.maxTime()) {
            std::cout << "Overtime! " << dt << " sec. "
                      << "It is a " << ((ei.cell() == 0) ? "dimer" : "cell") << " reaction" << std::endl;
        }

        if (counter > reactor.timeStep()) {
            storeLambda();
            counter = 0;
        }
    } while (totalTime < reactor.maxTime());
    if (counter > 0 && iterations > 1) {
        storeLambda();
    }

    std::cout << "Total time: " << totalTime << " sec" << std::endl;
    std::cout << "Iterations: " << iterations << std::endl;
}

int main() {
    srand(time(0));

    std::cout << "Running..." << std::endl;

//    run<RejectionSimulationContext<EventBasedSimulationContext> >();
//    run<RejectionFreeSimulationContext<EventBasedSimulationContext> >();
//    run<DynamicSimulationContext>();
//    run<KineticSimulationContext>();
//    run<TreeBasedSimulationContext>();

    run<RejectionSimulationContext<OptimizedEventBasedSimulationContext> >();
//    run<RejectionFreeSimulationContext<OptimizedEventBasedSimulationContext> >();
//    run<MuchOptimizedRejectionFreeSimulationContext>();
    run<OptimizedDynamicSimulationContext>();

//    SimpleNOCOReactorContext reactor;
//    reactor.solve("odu.mcr");

    std::cout << "Complete :)" << std::endl;

    return 0;
}
