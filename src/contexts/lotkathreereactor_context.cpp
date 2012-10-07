#include "lotkathreereactor_context.h"
#include "simpledistribution_context.h"
#include "../datas/cellreaction_data.h"
#include "../datas/dimerreactioncapture_data.h"
#include "../datas/dimerreactionexchange_data.h"

LotkaThreeReactorContext::LotkaThreeReactorContext() {
    addReaction(new DimerReactionCaptureData(1, 2, 0.07 / 4));
    addReaction(new DimerReactionCaptureData(2, 3, 0.07 / 4));
    addReaction(new DimerReactionCaptureData(3, 4, 1.0 / 4));
    addReaction(new CellReactionData(4, 1, 0.07));

//    addReaction(new DimerReactionExchangeData(4, 1, 0.1 / 4));
    addReaction(new DimerReactionExchangeData(4, 2, 3.0 / 4));
}

BaseDistributionContext *LotkaThreeReactorContext::createDistrubutor() const {
    float concs[] = { 0.1, 0.1, 0.1 };
    return new SimpleDistributionContext(concs, 3);
}

void LotkaThreeReactorContext::solveToOut(std::ostream &out) const {
}
