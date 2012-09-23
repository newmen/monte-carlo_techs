#include <fstream>
#include <iostream>
#include "basereactor_context.h"

BaseReactorContext::~BaseReactorContext() {
    for (auto p = _cellReactions.begin(); p != _cellReactions.end(); ++p) delete *p;
    for (auto p = _dimerReactions.begin(); p != _dimerReactions.end(); ++p) delete *p;
}

CellData *BaseReactorContext::createCell(CellType *cell, CoordType x, CoordType y) const {
    return new CellData(cell, x, y);
}

DimerData *BaseReactorContext::createDimer(CellData *first, CellData *second) const {
    return new DimerData(first, second);
}

void BaseReactorContext::solve(const std::string &fileName) const {
    std::ofstream out(fileName);
    if (!out) {
        std::cerr << "File " << fileName << " open error!" << std::endl;
    } else {
        solveToOut(out);
    }
}

template <>
void BaseReactorContext::eachReaction<CellData>(const std::function<void (const ReactionData<CellData> *const)> &lambda) const {
    for (auto p = _cellReactions.cbegin(); p != _cellReactions.cend(); ++p) lambda(*p);
}

template <>
void BaseReactorContext::eachReaction<DimerData>(const std::function<void (const ReactionData<DimerData> *const)> &lambda) const {
    for (auto p = _dimerReactions.cbegin(); p != _dimerReactions.cend(); ++p) lambda(*p);
}

template <>
void BaseReactorContext::addReaction<CellData>(const ReactionData<CellData> *const reaction) {
    _cellReactions.push_back(reaction);
}

template <>
void BaseReactorContext::addReaction<DimerData>(const ReactionData<DimerData> *const reaction) {
    _dimerReactions.push_back(reaction);
}
