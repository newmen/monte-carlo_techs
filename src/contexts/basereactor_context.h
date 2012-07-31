#ifndef BASEREACTOR_CONTEXT_H
#define BASEREACTOR_CONTEXT_H

#include <functional>
#include <vector>
#include <string>
#include "../datas/reaction_data.h"
#include "../datas/area_data.h"
#include "../datas/cell_data.h"
#include "../datas/dimer_data.h"

class BaseReactorContext
{
public:
    virtual ~BaseReactorContext();

    virtual int numOfSpecs() const = 0;
    virtual long double maxTime() const = 0;
    virtual long double timeStep() const = 0;

    virtual CellData *createCell(int *cell, int x, int y) const;
    virtual DimerData *createDimer(CellData *first, CellData *second) const;

    virtual void reinitCell(CellData *, const AreaData *) const {}
    virtual void reinitDimer(DimerData *, const AreaData *) const {}

    void solve(const std::string &fileName) const;

    template <class SData>
    void eachReaction(const std::function<void (const ReactionData<SData> *const)> &lambda) const;

protected:
    BaseReactorContext() {}

    template <class SData>
    void addReaction(const ReactionData<SData> *const reaction);

    virtual void solveToOut(std::ostream &out) const = 0;

private:
    std::vector<const ReactionData<CellData> *> _cellReactions;
    std::vector<const ReactionData<DimerData> *> _dimerReactions;
};

#endif // BASEREACTOR_CONTEXT_H
