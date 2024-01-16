#pragma once

#include "Figure.hpp"
#include <cstdio>

class Scheme {
public:
    explicit Scheme(int capacity);
    ~Scheme();

    void push_back_figure(Figure* fg);
    void remove_figure(int id);

    void print_all_figures();
    void zoom_figure(int id, int factor);
    Figure* is_inside_figure(int x, int y);
    void move(int id, int new_x, int new_y);

private:
    Figure** _figures;
    int _size;
};
