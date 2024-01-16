#include "my_vector.hpp"
#include <algorithm>

constexpr int defaultSize = 2;

void MyVector::copy_vector(MyVector& dist, const MyVector& src){
    delete [] dist._data;

    dist._size = src.size();
    dist._capacity = src.capacity();
    dist._data = new int[dist._capacity];

    for(size_t i = 0; i < dist._size; ++i){
        dist._data[i] = src._data[i];
    }
}


MyVector::MyVector() :
        _data(new int[defaultSize]{}),
        _size(0),
        _capacity(defaultSize)
{}

MyVector::MyVector(size_t size) :
        _data(new int[size]{}),
        _size(size),
        _capacity(size)
{}

MyVector::MyVector(const MyVector& vec){
    copy_vector(*this, vec);
}

MyVector& MyVector::operator=(const MyVector& vec) {
    copy_vector(*this, vec);
}

MyVector::~MyVector(){
    delete[] _data;
}

void MyVector::set(std::size_t index, int value){
    _data[index] = value;
}

int MyVector::get(std::size_t index) const{
    return _data[index];
}

std::size_t MyVector::size() const{
    return _size;
}

std::size_t MyVector::capacity() const{
    return _capacity;
}

void MyVector::reserve(std::size_t new_capacity){
    if(new_capacity){
        delete [] _data;
        _data = new int[new_capacity]{};
        _capacity = new_capacity;
    }
}

void MyVector::resize(std::size_t new_size){
    int* tmp = _data;
    _capacity = new_size > _capacity ? std::max(new_size, _capacity * 2) : _capacity;
    _data = new int[_capacity]();

    for(size_t i = 0; i < _size; ++i){
        _data[i] = tmp[i];
    }

    _size = new_size;

    delete tmp;
}

void MyVector::push_back(int value){
    if(_size >= _capacity)
        resize(_capacity * 2);
    _data[_size] = value;
    ++_size;
}

void MyVector::insert(std::size_t index, int value){
    if(_size >= _capacity)
        resize(_capacity * 2);
    ++_size;
    for(size_t i = index; i < _size - 1; ++i){
        _data[i + 1] = _data[i];
    }
    _data[index] = value;
}

void MyVector::erase(std::size_t index){
    for(size_t i = index; i < _size - 1; ++i){
        _data[i] = _data[i + 1];
    }
    --_size;
}