#include <cmath>
#include <cfloat>
#include "kineticsimulation_context.h"

KineticSimulationContext::KineticSimulationContext(AreaData *area) : SimulationBaseContext(area) {
    throughArea([this](int *cell, int **neighbours){
        PerSite *perSite = new PerSite(cell, neighbours);
        calcRatesPerSite(perSite);

        _perSites.push_back(perSite);
        _cellsToPerSites[cell] = *(_perSites.rbegin());
    });
}

KineticSimulationContext::~KineticSimulationContext() {
    for (PerSite *perSite : _perSites) delete perSite;
}

float KineticSimulationContext::doReaction() {
    float dt;
    int index = siteRandomIndex(&dt);
    if (index < 0) return 0;

    randomReaction(index)->doIt(&(_perSites[index]->_site));

    std::set<PerSite *> cache;
    updateData(&cache, _perSites[index]);

    return dt;
}

void KineticSimulationContext::calcRatesPerSite(PerSite *perSite) const {
    perSite->_commonRate = 0;
    for (int i = 0; i < REACTIONS_NUM; ++i) {
        perSite->_normedRates[i] = reaction(i)->couldBe(perSite->_site) * reaction(i)->rate();
        perSite->_commonRate += perSite->_normedRates[i];
    }

    for (int i = 0; i < REACTIONS_NUM; ++i) perSite->_normedRates[i] /= perSite->_commonRate;
    for (int i = 1; i < REACTIONS_NUM; ++i) perSite->_normedRates[i] += perSite->_normedRates[i - 1];
}

int KineticSimulationContext::siteRandomIndex(float *dt) const {
    int indexOfMin = -1;
    float min_dt = 0;
    for (int i = 0; i < _perSites.size(); ++i) {
        float u = 0;
        while (u == 0) u = randomN01();

        if (_perSites[i]->_commonRate == 0) continue;
        float local_dt = -log(u) / _perSites[i]->_commonRate;

        if (min_dt != 0 && local_dt >= min_dt) continue;
        min_dt = local_dt;
        indexOfMin = i;
    }
    *dt = min_dt;
    return indexOfMin;
}

IReactingRole *KineticSimulationContext::randomReaction(int index) const {
    float r = randomN01(); // TODO: тут нужно учитывать то, что иногда нормированные скорости дают чуть больше единицы
    for (int i = 0; i < REACTIONS_NUM - 1; ++i) {
        if (r < _perSites[index]->_normedRates[i]) return reaction(i);
    }
    return reaction(REACTIONS_NUM - 1);
}

void KineticSimulationContext::updateData(std::set<PerSite *> *cache, PerSite *perSite, int depth) {
    if (cache->find(perSite) != cache->end()) return;
    cache->insert(perSite);

    calcRatesPerSite(perSite);
    if (depth == 0) return;

    perSite->_site.neighboursIterator([this, &cache, &depth](int *neighbourCell) {
        updateData(cache, _cellsToPerSites[neighbourCell], depth - 1);
    });
}
