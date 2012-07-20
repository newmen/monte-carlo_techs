#include <fstream>
#include <iostream>
#include "reactorbase_context.h"

ReactorBaseContext::~ReactorBaseContext() {
    for (auto p = _cellReactions.begin(); p != _cellReactions.end(); ++p) delete *p;
    for (auto p = _dimerReactions.begin(); p != _dimerReactions.end(); ++p) delete *p;
}

CellData *ReactorBaseContext::createCell(int *cell, int x, int y) const {
    return new CellData(cell, x, y);
}

DimerData *ReactorBaseContext::createDimer(CellData *first, CellData *second) const {
    return new DimerData(first, second);
}

void ReactorBaseContext::solve(const std::string &fileName) const {
    std::ofstream out(fileName);
    if (!out) {
        std::cerr << "File " << fileName << " open error!" << std::endl;
    } else {
        solveToOut(out);
    }
}

template <>
void ReactorBaseContext::eachReaction<CellData>(const std::function<void (const ReactionData<CellData> *const)> &lambda) const {
    for (auto p = _cellReactions.cbegin(); p != _cellReactions.cend(); ++p) lambda(*p);
}

template <>
void ReactorBaseContext::eachReaction<DimerData>(const std::function<void (const ReactionData<DimerData> *const)> &lambda) const {
    for (auto p = _dimerReactions.cbegin(); p != _dimerReactions.cend(); ++p) lambda(*p);
}

template <>
void ReactorBaseContext::addReaction<CellData>(const ReactionData<CellData> *const reaction) {
    _cellReactions.push_back(reaction);
}

template <>
void ReactorBaseContext::addReaction<DimerData>(const ReactionData<DimerData> *const reaction) {
    _dimerReactions.push_back(reaction);
}
