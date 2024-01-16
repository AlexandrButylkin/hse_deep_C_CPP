#include "Figure.hpp"

Figure::Figure(int id, int x, int y) : _id(id), _x(x), _y(y) {}

void Figure::move(int new_x, int new_y) {
    _x = new_x;
    _y = new_y;
}

int Figure::GetId() {
    return _id;
}
