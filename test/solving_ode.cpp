#include "solving_ode.h"

#include <fstream>
#include <iostream>
#include "../reaction12_data.h"
#include "../reaction21_data.h"
#include "../reaction23_data.h"
#include "../reaction34_data.h"
#include "../reaction35_data.h"
#include "../reaction51_data.h"

#ifndef STATES_NUM
// TODO: нужно как-то выпилить
#define STATES_NUM 4
#endif

void solveODE(const std::string &fileName, double maxTime) {
    std::ofstream out(fileName);
    if (!out) {
        std::cerr << "File " << fileName << " open error!" << std::endl;
        exit(1);
    }

    Reaction12Data r12;
    Reaction21Data r21;
    Reaction23Data r23;
    Reaction34Data r34;
    Reaction35Data r35;
    Reaction51Data r51;

    double dt = 1e-3; // bad value
    double tt = 0;

    double concs[STATES_NUM], csNext[STATES_NUM];
    for (int i = 0; i < STATES_NUM; ++i) concs[i] = 0;

    while (tt < maxTime) {
        double csSum = 0;
        for (int i = 0; i < STATES_NUM; ++i) csSum += concs[i];

        csNext[0] = concs[0] + dt * (r12.k() * (1 - csSum) - concs[0] * (r21.k() + r23.k()));
        csNext[1] = concs[1] + dt * (r23.k() * concs[0] - concs[1] * (r34.k() + r35.k()));
        csNext[2] = concs[2] + dt * (r34.k() * concs[1]);
        csNext[3] = concs[3] + dt * (r35.k() * concs[1] - r51.k() * concs[3]);

        for (int i = 0; i < STATES_NUM; ++i) concs[i] = csNext[i];
        tt += dt;

        out << tt;
        for (int i = 0; i < STATES_NUM; ++i) out << "\t" << concs[i];
        out << std::endl;
    }
}
