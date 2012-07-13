#ifndef REACTORBASE_DATA_H
#define REACTORBASE_DATA_H

#include <functional>
#include <vector>
#include "reaction_data.h"
#include "cell_data.h"
#include "dimer_data.h"

class ReactorBaseData
{
public:
    virtual ~ReactorBaseData();

    template <class SData>
    void eachReaction(const std::function<void (const ReactionData<SData> *const)> &lambda) const;

protected:
    ReactorBaseData() {}

    template <class SData>
    void addReaction(const ReactionData<SData> *const reaction);

private:
    std::vector<const ReactionData<CellData> *> _cellReactions;
    std::vector<const ReactionData<DimerData> *> _dimerReactions;
};

#endif // REACTORBASE_DATA_H
