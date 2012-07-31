#include "eventinfo_data.h"

template <>
void EventInfoData::set<CellData>(CellData *cell) {
    _cell = cell;
}

template <>
void EventInfoData::set<DimerData>(DimerData *dimer) {
    _dimer = dimer;
}
