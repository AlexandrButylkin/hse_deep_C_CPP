#include "Figure.hpp"
#include <cstdio>

class Rectangle : public Figure {
public:
    Rectangle(int id, int x, int y, int width, int height);
    ~Rectangle() override = default;

    void print() const override;
    bool is_inside(int x, int y) const override;
    void zoom(int factor) override;

private:
    int _width;
    int _height;
};
