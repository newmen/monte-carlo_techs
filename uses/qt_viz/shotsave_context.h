#ifndef SHOTSAVE_CONTEXT_H
#define SHOTSAVE_CONTEXT_H

#include "../../src/contexts/readshot_context.h"
#include "../../src/datas/area_data.h"
#include "config.h"
#include "renderarea_context.h"

class ShotSaveContext
{
public:
    ShotSaveContext(Config *config);
    ~ShotSaveContext();
    
    void storeShots();

private:
    void doReaction();

    void readFile();
    void saveSnapShot();

private:
    Config *_config;
    double _currentTime;

    AreaData *_area;
    ReadShotContext *_readContext;
    RenderAreaContext *_renderArea;
};

#endif // SHOTSAVE_CONTEXT_H
