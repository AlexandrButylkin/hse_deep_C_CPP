#include "Rectangle.hpp"
#include <cstdio>

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y), _width(width), _height(height) {}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", _id, _x, _y, _width, _height);
}

bool Rectangle::is_inside(int x, int y) const {
    return x >= _x - _width / 2 && x <= _x + _width / 2 &&
           y >= _y - _height / 2 && y <= _y + _height / 2;
}

void Rectangle::zoom(int factor) {
    _width *= factor;
    _height *= factor;
}
