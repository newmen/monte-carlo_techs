#include "abcdcellreactor_context.h"
#include "../datas/cellreaction_data.h"

ABCDCellReactorContext::ABCDCellReactorContext() {
    addReaction(new CellReactionData(8, 3, 4));
    addReaction(new CellReactionData(5, 3, 5));
    addReaction(new CellReactionData(233, 5, 1));
}
