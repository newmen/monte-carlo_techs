#include <ctime>
#include <cstdlib>
#include <iostream>
#include "area_data.h"
#include "rejectionsimulation_context.h"
#include "rejectionfreesimulation_context.h"
#include "dynamicsimulation_context.h"
#include "kineticsimulation_context.h"
#include "treebasedsimulation_context.h"

int main() {
    srand(time(0));

    AreaData area(5, 5);
//    AreaData area(25, 25);

//    RejectionSimulationContext sc(&area);
//    RejectionFreeSimulationContext sc(&area);
//    DynamicSimulationContext sc(&area);
//    KineticSimulationContext sc(&area);
    TreeBasedSimulationContext sc(&area, 5);
    double dt, totalTime = 0;
    do {
        dt = sc.doReaction();
        totalTime += dt;
    } while (dt > 0);

    std::cout << "Total time: " << totalTime << " sec" << std::endl;

    return 0;
}
