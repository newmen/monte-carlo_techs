#ifndef KINETICSIMULATION_CONTEXT_H
#define KINETICSIMULATION_CONTEXT_H

#include <vector>
#include "perdatasimulation_context.h"

class KineticSimulationContext : public PerDataSimulationContext
{
public:
    KineticSimulationContext(AreaData *area);
    ~KineticSimulationContext();

    double doReaction();

protected:
    PerSite *createData(const SharedSite &site) const;
    PerDimer *createData(const SharedDimer &dimer) const;

    void store(PerSite *site);
    void store(PerDimer *dimer);

private:
    template <class SDData>
    PerSiteOrDimerData<SDData> *findMin(double *dt, const std::vector<PerSiteOrDimerData<SDData> *> &pers) const;

    template <class PerData>
    void doRandomReaction(PerData *perData);

private:
    std::vector<PerSite *> _perSites;
    std::vector<PerDimer *> _perDimers;
};

#endif // KINETICSIMULATION_CONTEXT_H
