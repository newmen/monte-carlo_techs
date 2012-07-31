#include "abcddimerreactor_context.h"
#include "../datas/cellreaction_data.h"
#include "../datas/dimerreactioncapture_data.h"
#include "../datas/dimerreactionstabilization_data.h"

ABCDDimerReactorContext::ABCDDimerReactorContext() {
    addReaction(new DimerReactionStabilizationData(8, 3, 4));
    addReaction(new CellReactionData(5, 3, 5));
    addReaction(new DimerReactionCaptureData(233, 5, 1));
}
