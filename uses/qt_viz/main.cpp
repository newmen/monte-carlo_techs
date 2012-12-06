#include <QApplication>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "shotsave_context.h"

int main(int argc, char *argv[]) {
    srand(time(0));

    if (argc < 3) {
        std::cerr << "Invalid run!" << std::endl;
        std::cerr << argv[0] << " shotDataPath shotDirPath everySecond cellSideLength" << std::endl;
        return 1;
    }

    Config config;
    config.shotDataPath = QString(argv[1]);
    config.shotDirPath = QString(argv[2]);

    if (argc > 3) {
        config.cellSideLength = atoi(argv[3]);
    }

    QApplication app(argc, argv);

    ShotSaveContext shotSaver(&config);
    shotSaver.storeShots();

    return 0;
}
