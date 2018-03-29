#include "Cell.h"

namespace game {

Cell::Cell() {}

Cell::~Cell() {}

Cell::Cell(int x, int y, int status) : x(x), y(y), status(status) {}

bool Cell::operator<(const Cell &o) const {
    if (x != o.x)
        return x < o.x;
    return y < o.y;
}

} // namespace game
