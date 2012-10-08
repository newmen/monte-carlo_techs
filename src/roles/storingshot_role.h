#ifndef STORINGSHOT_ROLE_H
#define STORINGSHOT_ROLE_H

#include <ostream>
#include "../datas/cell_data.h"

template <class AData>
class StoringShotRole : public AData
{
public:
    void store(std::ostream &os) const;
};

template <class AData>
void StoringShotRole<AData>::store(std::ostream &os) const {
    this->eachCell([this, &os](CellType *const value, CoordType, CoordType) {
        os << value;
    });
}

#endif // STORINGSHOT_ROLE_H
