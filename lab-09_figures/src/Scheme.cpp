#include "Scheme.hpp"

Scheme::Scheme(int capacity) : _figures(new Figure*[capacity]), _size(0) {}

Scheme::~Scheme() {
    for(int i = 0; i < _size; ++i){
        delete _figures[i];
    }
    delete [] _figures;
}

void Scheme::push_back_figure(Figure* fg) {
    _figures[_size] = fg;
    ++_size;
}

void Scheme::remove_figure(int id){
    int pos = _size;
    for(int i = 0; i < _size; ++i){
        if(id == _figures[i]->GetId()) {
            pos = i;
            delete _figures[i];
        }
    }

    for(int i = pos; i < _size - 1; ++i){
        _figures[i] = _figures[i + 1];
    }
    --_size;
}

void Scheme::print_all_figures(){
    for(int i = 0; i < _size; ++i){
        _figures[i]->print();
    }
}

void Scheme::zoom_figure(int id, int factor){
    for(int i = 0; i < _size; ++i){
        if(id == _figures[i]->GetId())
            _figures[i]->zoom(factor);
    }
}

Figure* Scheme::is_inside_figure(int x, int y){
    for(int i = 0; i < _size; ++i){
        if(_figures[i]->is_inside(x, y))
            return _figures[i];
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y){
    for(int i = 0; i < _size; ++i){
        if(id == _figures[i]->GetId())
            _figures[i]->move(new_x, new_y);
    }
}