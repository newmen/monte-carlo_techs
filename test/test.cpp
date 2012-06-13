#include <sys/time.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "process_mem_usage.h"

#include "area_data.h"
#include "dynamicsimulation_context.h"
#include "kineticsimulation_context.h"
#include "rejectionsimulation_context.h"
#include "rejectionfreesimulation_context.h"
#include "treebasedsimulation_context.h"

#include <sstream>
#include "store_context.h"
#include "reaction12_data.h"
#include "reaction21_data.h"
#include "reaction23_data.h"
#include "reaction34_data.h"
#include "reaction35_data.h"
#include "reaction51mr_data.h"

#ifndef STATES_NUM
// TODO: нужно как-то выпилить
#define STATES_NUM 4
#endif

using namespace std;

const char *buildFilePath(const char *fileName, const char *ext) {
    stringstream ss;
    ss << "results/" << fileName << "." << ext;
    return ss.str().c_str();
}

void printFileWasSaved(const string &fileName) {
    cout << fileName << " file saved\n" << endl;
}

class PerformanceSaver {
public:
    PerformanceSaver() {}

    ~PerformanceSaver() {
        if (_dataNames.empty()) return;

        const char ext[4] = "prf";

        bool filesAlreadyExists = true;
        ifstream temp;
        for (auto filePair = _dataValues.cbegin(); filePair != _dataValues.cend(); ++filePair) {
            string fullFilePath = buildFilePath(filePair->first.c_str(), ext);
            temp.open(fullFilePath.c_str());
            if (!temp) {
                cout << fullFilePath << " does not exists" << endl;
                filesAlreadyExists = false;
                break;
            } else {
                temp.close();
            }
        }

        ofstream out;
        for (auto filePair = _dataValues.cbegin(); filePair != _dataValues.cend(); ++filePair) {
            string fullFilePath = buildFilePath(filePair->first.c_str(), ext);
            out.open(fullFilePath.c_str(), ((filesAlreadyExists) ? ios_base::app : ios_base::trunc));
            if (!filesAlreadyExists) {
                out << "#";
                for (const string &name : _dataNames) out << "\t" << name;
                out << "\n";
            }

            for (auto p = filePair->second.cbegin(); p != filePair->second.cend(); ++p) {
                out << p->first;
                for (float value : p->second) out << "\t" << value;
                out << endl;
            }
            out.close();

            printFileWasSaved(fullFilePath);
        }
    }

    void storeName(const char *mcName) {
        _dataNames.push_back(mcName);
    }

    void storeValue(const char *fileName, unsigned int size, float value) {
        _dataValues[fileName][size].push_back(value);
    }

private:
    vector<string> _dataNames;
    map<string, map<unsigned int, vector<float> > > _dataValues;
};

void solveODE(const char *fileName) {
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
    Reaction51MRData r51;

    float dt = 1e-3; // bad value
    double tt = 0;

    float concs[STATES_NUM], csNext[STATES_NUM];
    for (int i = 0; i < STATES_NUM; ++i) concs[i] = 0;

    while (tt < 2) { // bad value
        float csSum = 0;
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

template <class SimulationContext>
void runTest(PerformanceSaver &ps,
             const char *name, const int sizeX, const int sizeY, const int repeats,
             const char *fileName, bool needGraph)
{
    const string fullFilePath = buildFilePath(fileName, "mcr");

    cout << name << endl;
    if (!needGraph) ps.storeName(name);

    double totalTime = 0, dt = 0;
    unsigned long long iterations = 0;

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

    for (int i = 0; i < repeats; ++i) {
        freeUpMemory();
        area = new AreaData(sizeX, sizeY);
        simulationContext = new SimulationContext(area);
        if (needGraph) storeContext = new StoreContext(area, fullFilePath.c_str(), name);

        while (true) {
            dt = simulationContext->doReaction();
            if (needGraph) storeContext->store(dt);
            if (dt == 0) break;

            totalTime += dt;
            ++iterations;
        }
    }

    double stopTime = currTime();

    cout << "Total process time: " << (totalTime / repeats)
         << " (sec); Iterations: " << ((double)iterations / repeats) << endl;

    double calcTime = (stopTime - startTime) / repeats;
    double vm, rss;
    process_mem_usage(vm, rss);
    cout << "VM: " << vm << "; RSS: " << rss << endl;
    cout << "Calculating time: " << calcTime << " seconds" << endl;

    if (needGraph) printFileWasSaved(fullFilePath);
    else {
        cout << endl;

        unsigned int size = sizeX * sizeY;
        ps.storeValue("times", size, calcTime);
        ps.storeValue("virtuals", size, vm);
        ps.storeValue("rss", size, rss);
    }

    freeUpMemory();
}

int main(int argc, char *argv[]) {
    if (argc < 4 || argc > 5) {
        cerr << "Wrong test running! Try this:\n"
             << argv[0] << " sizeX sizeY repeats store?" << endl;
        return 1;
    }
    const int sizeX = atoi(argv[1]), sizeY = atoi(argv[2]);
    const int repeats = atoi(argv[3]);
    const bool needGraph = (argc == 5 && strcmp(argv[4], "true") == 0);

    cout << "Running with:\n"
         << "sizeX = " << sizeX << "\n"
         << "sizeY = " << sizeY << "\n"
         << "repeats = " << repeats << "\n" << endl;

    if (needGraph) {
        const string originalFileName = buildFilePath("original", "mcr");
        solveODE(originalFileName.c_str());
        printFileWasSaved(originalFileName);
    }

    PerformanceSaver ps;

    srand(time(0));
    runTest<DynamicSimulationContext>(ps, "Dynamic MC", sizeX, sizeY, repeats, "dynamic", needGraph);
    runTest<KineticSimulationContext>(ps, "Kinetic MC", sizeX, sizeY, repeats, "kinetic", needGraph);
    runTest<RejectionSimulationContext>(ps, "Rejection MC", sizeX, sizeY, repeats, "rejection", needGraph);
    runTest<RejectionFreeSimulationContext>(ps, "Rejection-free MC", sizeX, sizeY, repeats, "rejection-free", needGraph);

    runTest<TreeBasedSimulationContext<100> >(ps, "Faster <100> MC", sizeX, sizeY, repeats, "faster_100", needGraph);
    runTest<TreeBasedSimulationContext<20> >(ps, "Faster <20> MC", sizeX, sizeY, repeats, "faster_20", needGraph);
    runTest<TreeBasedSimulationContext<10> >(ps, "Faster <10> MC", sizeX, sizeY, repeats, "faster_10", needGraph);
    runTest<TreeBasedSimulationContext<5> >(ps, "Faster <5> MC", sizeX, sizeY, repeats, "faster_5", needGraph);
    runTest<TreeBasedSimulationContext<2> >(ps, "Faster Binary MC", sizeX, sizeY, repeats, "faster_binary", needGraph);

    return 0;
}
