#include "reactorbase_data.h"

ReactorBaseData::~ReactorBaseData() {
    for (auto p = _cellReactions.begin(); p != _cellReactions.end(); ++p) delete *p;
    for (auto p = _dimerReactions.begin(); p != _dimerReactions.end(); ++p) delete *p;
}

template <>
void ReactorBaseData::eachReaction<CellData>(const std::function<void (const ReactionData<CellData> *const)> &lambda) const {
    for (auto p = _cellReactions.cbegin(); p != _cellReactions.cend(); ++p) lambda(*p);
}

template <>
void ReactorBaseData::eachReaction<DimerData>(const std::function<void (const ReactionData<DimerData> *const)> &lambda) const {
    for (auto p = _dimerReactions.cbegin(); p != _dimerReactions.cend(); ++p) lambda(*p);
}

template <>
void ReactorBaseData::addReaction<CellData>(const ReactionData<CellData> *const reaction) {
    _cellReactions.push_back(reaction);
}

template <>
void ReactorBaseData::addReaction<DimerData>(const ReactionData<DimerData> *const reaction) {
    _dimerReactions.push_back(reaction);
}
