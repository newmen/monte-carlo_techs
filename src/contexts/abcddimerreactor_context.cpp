#include "abcddimerreactor_context.h"
#include "../datas/cellreaction_data.h"
#include "../datas/dimerreactioncapture_data.h"
#include "../datas/dimerreactionstabilization_data.h"

ABCDDimerReactorContext::ABCDDimerReactorContext() {
    addReaction(new DimerReactionStabilizationData(3, 4, 8));
    addReaction(new CellReactionData(3, 5, 5));
    addReaction(new DimerReactionCaptureData(5, 1, 233));
}
