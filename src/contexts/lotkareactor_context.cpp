#include "lotkareactor_context.h"
#include "../datas/cellreaction_data.h"
#include "../datas/dimerreactioncapture_data.h"
#include "../datas/dimerreactionexchange_data.h"

LotkaReactorContext::LotkaReactorContext() {
//    addReaction(new DimerReactionCaptureData(0.1 / 4, 1, 2));
//    addReaction(new DimerReactionCaptureData(0.5 / 4, 2, 3));
//    addReaction(new CellReactionData(0.07, 3, 1));
////    addReaction(new DimerReactionExchangeData(0, 2, 1));
//    addReaction(new DimerReactionExchangeData(0.5 / 4, 3, 1));

//    addReaction(new DimerReactionCaptureData(0.07 / 4, 1, 2));
//    addReaction(new DimerReactionCaptureData(1.0 / 4, 2, 3));
//    addReaction(new CellReactionData(0.07, 3, 1));
////    addReaction(new DimerReactionExchangeData(0, 2, 1));
////    addReaction(new DimerReactionExchangeData(0, 3, 1));

//    addReaction(new DimerReactionCaptureData(10.0 / 4, 1, 2));
//    addReaction(new DimerReactionCaptureData(15.0 / 4, 2, 3));
//    addReaction(new CellReactionData(1.0, 3, 1));
////    addReaction(new DimerReactionExchangeData(0, 2, 1));
////    addReaction(new DimerReactionExchangeData(0, 3, 1));

//    addReaction(new DimerReactionCaptureData(0.1 / 4, 1, 2));
//    addReaction(new DimerReactionCaptureData(0.5 / 4, 2, 3));
//    addReaction(new CellReactionData(0.07, 3, 1));
//    addReaction(new DimerReactionExchangeData(1000, 2, 1));
////    addReaction(new DimerReactionExchangeData(0, 3, 1));

//    addReaction(new DimerReactionCaptureData(0.05 / 4, 1, 2));
//    addReaction(new DimerReactionCaptureData(1.0 / 4, 2, 3));
//    addReaction(new CellReactionData(0.05, 3, 1));
////    addReaction(new DimerReactionExchangeData(0, 2, 1));
//    addReaction(new DimerReactionExchangeData(1000, 3, 1));

//    addReaction(new DimerReactionCaptureData(0.1 / 4, 1, 2));
//    addReaction(new DimerReactionCaptureData(0.5 / 4, 2, 3));
//    addReaction(new CellReactionData(0.07, 3, 1));
//    addReaction(new DimerReactionExchangeData(20, 2, 1));
//    addReaction(new DimerReactionExchangeData(0.01, 3, 1));

    addReaction(new DimerReactionCaptureData(0.07 / 4, 1, 2));
    addReaction(new DimerReactionCaptureData(1.0 / 4, 2, 3));
    addReaction(new CellReactionData(0.07, 3, 1));
    addReaction(new DimerReactionExchangeData(0.0001, 2, 1));
    addReaction(new DimerReactionExchangeData(20.0, 3, 1));
}

void LotkaReactorContext::solveToOut(std::ostream &out) const {
}
