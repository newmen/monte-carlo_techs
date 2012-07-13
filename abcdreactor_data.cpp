#include "abcdreactor_data.h"
#include "cellreaction_data.h"

ABCDReactorData::ABCDReactorData() {
    addReaction(new CellReactionData(144, 1, 2));
    addReaction(new CellReactionData(34, 2, 1));
    addReaction(new CellReactionData(55, 2, 3));
}
