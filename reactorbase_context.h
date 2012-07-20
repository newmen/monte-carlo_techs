#ifndef REACTORBASE_CONTEXT_H
#define REACTORBASE_CONTEXT_H

#include <functional>
#include <vector>
#include <string>
#include "reaction_data.h"
#include "area_data.h"
#include "cell_data.h"
#include "dimer_data.h"

class ReactorBaseContext
{
public:
    virtual ~ReactorBaseContext();

    virtual int numOfSpecs() const = 0;
    virtual double maxTime() const = 0;

    virtual CellData *createCell(int *cell, int x, int y) const;
    virtual DimerData *createDimer(CellData *first, CellData *second) const;

    virtual void reinitCell(CellData *, const AreaData *) const {}
    virtual void reinitDimer(DimerData *, const AreaData *) const {}

    void solve(const std::string &fileName) const;

    template <class SData>
    void eachReaction(const std::function<void (const ReactionData<SData> *const)> &lambda) const;

protected:
    ReactorBaseContext() {}

    template <class SData>
    void addReaction(const ReactionData<SData> *const reaction);

    virtual void solveToOut(std::ostream &out) const = 0;

private:
    std::vector<const ReactionData<CellData> *> _cellReactions;
    std::vector<const ReactionData<DimerData> *> _dimerReactions;
};

#endif // REACTORBASE_CONTEXT_H
