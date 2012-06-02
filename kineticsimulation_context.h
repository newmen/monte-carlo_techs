#ifndef KINETICSIMULATION_CONTEXT_H
#define KINETICSIMULATION_CONTEXT_H

#include <map>
#include <vector>
#include <set>
#include "simulationbase_context.h"
#include "site_data.h"

class KineticSimulationContext : public SimulationBaseContext
{
public:
    KineticSimulationContext(AreaData *area);
    ~KineticSimulationContext();

    float doReaction();

private:
    struct PerSite {
        SiteData _site;
        float _commonRate;
        float _normedRates[REACTIONS_NUM];

        PerSite(int *cell, int **neighbours) : _site(cell, neighbours) {}
    };

    void calcRatesPerSite(PerSite *perSite) const;
    int siteRandomIndex(float *dt) const;
    IReactingRole *randomReaction(int index) const;

    void updateData(std::set<PerSite *> *cache, PerSite *perSite, int depth = 2);

    std::vector<PerSite *> _perSites;
    std::map<int *, PerSite *> _cellsToPerSites;
};

#endif // KINETICSIMULATION_CONTEXT_H
