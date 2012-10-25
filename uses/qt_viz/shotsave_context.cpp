#include <QtGui>
#include <iostream>
#include "shotsave_context.h"

ShotSaveContext::ShotSaveContext(Config *config) : _config(config), _area(0), _readContext(0), _renderArea(0) {
    _renderArea = new RenderAreaContext(_config->cellSideLength);

    readFile();
}

ShotSaveContext::~ShotSaveContext() {
    delete _readContext;
    delete _renderArea;
    delete _area;
}

void ShotSaveContext::storeShots() {
     while (true) {
        _currentTime = _readContext->setShotToArea(_area);
        if (_currentTime < 0) break;

        _renderArea->update();
        saveSnapShot();
     }
}

void ShotSaveContext::readFile() {
    _readContext = new ReadShotContext(_config->shotDataPath.toStdString());

    Point2D sizes = _readContext->areaSizes();
    _area = new AreaData(sizes.x, sizes.y);
    _renderArea->resetArea(_area);
    _currentTime = 0;
}

void ShotSaveContext::saveSnapShot() {
    QPixmap pixmap = QPixmap::grabWidget(_renderArea, 0, 0,
                                         _area->sizeX() * _config->cellSideLength, _area->sizeY() * _config->cellSideLength);

    QString out = _config->shotDirPath + QString('/') + QString::number(_currentTime) + QString(".png");
    if (pixmap.save(out)) {
//        std::cout << out.toStdString() << std::endl;
    } else {
        QString msgText = QString("Failed to write into ") + out;
        std::cerr << msgText.toStdString() << std::endl;
    }
}
