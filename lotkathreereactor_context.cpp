#include "lotkathreereactor_context.h"
#include "cellreaction_data.h"
#include "dimerreactioncapture_data.h"
#include "dimerreactionexchange_data.h"

LotkaThreeReactorContext::LotkaThreeReactorContext() {
    addReaction(new DimerReactionCaptureData(0.07 / 4, 1, 2));
    addReaction(new DimerReactionCaptureData(0.07 / 4, 2, 3));
    addReaction(new DimerReactionCaptureData(1.0 / 4, 3, 4));
    addReaction(new CellReactionData(0.07, 4, 1));

//    addReaction(new DimerReactionExchangeData(0.1 / 4, 4, 1));
    addReaction(new DimerReactionExchangeData(3.0 / 4, 4, 2));
}

void LotkaThreeReactorContext::solveToOut(std::ostream &out) const {
}
