#ifndef NOCOREACTOR_CONTEXT_H
#define NOCOREACTOR_CONTEXT_H

#include "rtreactor_context.h"

class NOCOReactorContext : public RTReactorContext
{
public:
    NOCOReactorContext();

    int numOfSpecs() const { return 2; }
    long double maxTime() const { return 50.0; }
    long double timeStep() const { return 0.25; }

    CellData *createCell(int *cell, int x, int y) const;
    DimerData *createDimer(CellData *first, CellData *second) const;

    void reinitCell(CellData *cell, const AreaData *area) const;
    void reinitDimer(DimerData *dimer, const AreaData *area) const;

protected:
    void solveToOut(std::ostream &out) const;

private:
    template <class SData, class LData>
    void reinitSite(SData *site, const AreaData *area) const;
};

#endif // NOCOREACTOR_CONTEXT_H
