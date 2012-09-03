#include "abcdcellreactor_context.h"
#include "../datas/cellreaction_data.h"

ABCDCellReactorContext::ABCDCellReactorContext() {
    addReaction(new CellReactionData(3, 4, 8));
    addReaction(new CellReactionData(3, 5, 5));
    addReaction(new CellReactionData(5, 1, 233));
}
