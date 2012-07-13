#include "abcdcellreactor_data.h"
#include "cellreaction_data.h"
#include "dimerreactionexchange_data.h"

ABCDCellReactorData::ABCDCellReactorData() {
    addReaction(new DimerReactionExchangeData(1e2, 3, 1));
    addReaction(new CellReactionData(8, 3, 4));
    addReaction(new CellReactionData(5, 3, 5));
    addReaction(new CellReactionData(233, 5, 1));
}
