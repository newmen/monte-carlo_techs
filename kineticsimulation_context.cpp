#include <cmath>
#include "kineticsimulation_context.h"

KineticSimulationContext::KineticSimulationContext(AreaData *area) : SimulationBaseContext(area) {
    throughArea([this](int *cell, int **neighbours){
        PerSite *perSite = new PerSite(cell, neighbours, this->reactionsNum());
        calcRatesPerSite(perSite);

        _perSites.push_back(perSite);
        _cellsToPerSites[cell] = *(_perSites.rbegin());
    });
}

KineticSimulationContext::~KineticSimulationContext() {
    for (auto p = _perSites.begin(); p != _perSites.end(); ++p) delete *p;
//    for (PerSite *perSite : _perSites) delete perSite;
}

double KineticSimulationContext::doReaction() {
    double dt;
    int index = siteRandomIndex(&dt);
    if (index < 0) return 0;

    randomReaction(index)->doIt(&(_perSites[index]->_site));

    std::set<PerSite *> cache;
    updateData(&cache, _perSites[index]);

    return dt;
}

void KineticSimulationContext::calcRatesPerSite(PerSite *perSite) const {
    perSite->_commonRate = 0;
    for (int i = 0; i < reactionsNum(); ++i) {
        perSite->_normedRates[i] = reaction(i)->couldBe(perSite->_site) * reaction(i)->rate();
        perSite->_commonRate += perSite->_normedRates[i];
    }
}

int KineticSimulationContext::siteRandomIndex(double *dt) const {
    int indexOfMin = -1;
    double min_dt = 0;
    for (int i = 0; i < (int)(_perSites.size()); ++i) {
        if (_perSites[i]->_commonRate == 0) continue;
        double local_dt = negativLogU() / _perSites[i]->_commonRate;

        if (min_dt != 0 && local_dt >= min_dt) continue;
        min_dt = local_dt;
        indexOfMin = i;
    }
    *dt = min_dt;
    return indexOfMin;
}

IReactingRole *KineticSimulationContext::randomReaction(int index) const {
    for (int i = 0; i < reactionsNum(); ++i) _perSites[index]->_normedRates[i] /= _perSites[index]->_commonRate;
    for (int i = 1; i < reactionsNum(); ++i) _perSites[index]->_normedRates[i] += _perSites[index]->_normedRates[i - 1];

    double r = randomN01(); // тут нужно учитывать то, что иногда нормированные скорости дают чуть больше единицы (даже с double?)
    for (int i = 0; i < reactionsNum() - 1; ++i) {
        if (r < _perSites[index]->_normedRates[i]) return reaction(i);
    }
    return reaction(reactionsNum() - 1);
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
