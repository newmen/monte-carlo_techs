#ifndef KINETICSIMULATION_CONTEXT_H
#define KINETICSIMULATION_CONTEXT_H

#include <map>
#include <vector>
#include <set>
#include "simulationbase_context.h"
#include "site_data.h"

class KineticSimulationContext : public SimulationBaseContext
{
    struct PerSite {
        SiteData _site;
        double _commonRate;
        double _normedRates[REACTIONS_NUM];

        PerSite(int *cell, int **neighbours) : _site(cell, neighbours) {}
    };

public:
    KineticSimulationContext(AreaData *area);
    ~KineticSimulationContext();

    double doReaction();

private:
    void calcRatesPerSite(PerSite *perSite) const;
    int siteRandomIndex(double *dt) const;
    IReactingRole *randomReaction(int index) const;

    void updateData(std::set<PerSite *> *cache, PerSite *perSite, int depth = 2);

private:
    std::vector<PerSite *> _perSites;
    std::map<int *, PerSite *> _cellsToPerSites;
};

#endif // KINETICSIMULATION_CONTEXT_H
