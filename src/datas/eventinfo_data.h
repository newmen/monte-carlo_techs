#ifndef EVENTINFO_DATA_H
#define EVENTINFO_DATA_H

#include "cell_data.h"
#include "dimer_data.h"

class EventInfoData
{
public:
    EventInfoData(long double dt) : _dt(dt), _cell(0), _dimer(0) {}

    template <class SData>
    void set(SData *site);

    long double dt() const { return _dt; }
    const CellData *cell() const { return _cell; }
    const DimerData *dimer() const { return _dimer; }

private:
    long double _dt;
    CellData *_cell;
    DimerData *_dimer;
};

#endif // EVENTINFO_DATA_H
