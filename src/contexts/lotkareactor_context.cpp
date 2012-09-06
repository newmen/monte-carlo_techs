#include "lotkareactor_context.h"
#include "../datas/cellreaction_data.h"
#include "../datas/dimerreactioncapture_data.h"
#include "../datas/dimerreactionexchange_data.h"

LotkaReactorContext::LotkaReactorContext() {
//    addReaction(new DimerReactionCaptureData(1, 2, 0.1 / 4));
//    addReaction(new DimerReactionCaptureData(2, 3, 0.5 / 4));
//    addReaction(new CellReactionData(3, 1, 0.07));
////    addReaction(new DimerReactionExchangeData(2, 1, 0));
//    addReaction(new DimerReactionExchangeData(3, 1, 0.5 / 4));

    addReaction(new DimerReactionCaptureData(1, 2, 0.07 / 4));
    addReaction(new DimerReactionCaptureData(2, 3, 1.0 / 4));
    addReaction(new CellReactionData(3, 1, 0.07));
//    addReaction(new DimerReactionExchangeData(2, 1, 0));
//    addReaction(new DimerReactionExchangeData(3, 1, 0));

//    addReaction(new DimerReactionCaptureData(1, 2, 10.0 / 4));
//    addReaction(new DimerReactionCaptureData(2, 3, 15.0 / 4));
//    addReaction(new CellReactionData(3, 1, 1.0));
////    addReaction(new DimerReactionExchangeData(2, 1, 0));
////    addReaction(new DimerReactionExchangeData(3, 1, 0));

//    addReaction(new DimerReactionCaptureData(1, 2, 0.1 / 4));
//    addReaction(new DimerReactionCaptureData(2, 3, 0.5 / 4));
//    addReaction(new CellReactionData(3, 1, 0.07));
//    addReaction(new DimerReactionExchangeData(2, 1, 1000));
////    addReaction(new DimerReactionExchangeData(3, 1, 0));

//    addReaction(new DimerReactionCaptureData(1, 2, 0.05 / 4));
//    addReaction(new DimerReactionCaptureData(2, 3, 1.0 / 4));
//    addReaction(new CellReactionData(3, 1, 0.05));
////    addReaction(new DimerReactionExchangeData(2, 1, 0));
//    addReaction(new DimerReactionExchangeData(3, 1, 1000));

//    addReaction(new DimerReactionCaptureData(1, 2, 0.1 / 4));
//    addReaction(new DimerReactionCaptureData(2, 3, 0.5 / 4));
//    addReaction(new CellReactionData(3, 1, 0.07));
//    addReaction(new DimerReactionExchangeData(2, 1, 20));
//    addReaction(new DimerReactionExchangeData(3, 1, 0.01));

//    addReaction(new DimerReactionCaptureData(1, 2, 0.07 / 4));
//    addReaction(new DimerReactionCaptureData(2, 3, 1.0 / 4));
//    addReaction(new CellReactionData(3, 1, 0.07));
//    addReaction(new DimerReactionExchangeData(2, 1, 0.0001));
//    addReaction(new DimerReactionExchangeData(3, 1, 20.0));
}

void LotkaReactorContext::solveToOut(std::ostream &out) const {
}
