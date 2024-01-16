#include "Circle.hpp"
#include <cstring>
#include <cstdio>

Circle::Circle(int id, int x, int y, int radius, const char* label) : Figure(id, x, y), _radius(radius){
    _label = new char[strlen(label) + 1];
    strcpy(_label, label);
}

Circle::~Circle() {
    delete [] _label;
}

void Circle::print() const{
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", _id, _x, _y, _radius, _label);
}

bool Circle::is_inside(int x, int y) const {
    return (x - _x) * (x - _x) + (y - _y) * (y - _y) <= _radius * _radius;
}

void Circle::zoom(int factor){
    _radius *= factor;
}
