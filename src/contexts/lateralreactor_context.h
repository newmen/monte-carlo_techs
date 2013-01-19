#ifndef LATERALREACTOR_CONTEXT_H
#define LATERALREACTOR_CONTEXT_H

#include "rtreactor_context.h"

class LateralReactorContext : public RTReactorContext
{
public:
    LateralReactorContext(double T);

    CellData *createCell(CellType *cell, CoordType x, CoordType y) const;
    DimerData *createDimer(CellData *first, CellData *second) const;

    void reinitCell(CellData *cell, const AreaData *area) const;
    void reinitDimer(DimerData *dimer, const AreaData *area) const;

private:
    template <class SData, class LData>
    void reinitSite(SData *site, const AreaData *area) const;
};

#endif // LATERALREACTOR_CONTEXT_H
