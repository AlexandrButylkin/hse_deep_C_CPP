#include "Bitset.h"

//Bitset::Bitset(const Bitset& bitset) : _bitset(bitset._bitset) {}

Bitset::Bitset(char ch){
    for(int i = 0; i < 8; ++i){
        _bitset.push_back(ch & (1 << i));
    }
}

/*Bitset Bitset::operator=(const Bitset& bitset) {
    _bitset = bitset._bitset;
}*/

Bitset::Iter Bitset::begin() {
    return _bitset.begin();
}

Bitset::Iter Bitset::end() {
    return _bitset.end();
}

Bitset::ConstIter Bitset::cbegin() const {
    return _bitset.cbegin();
}

Bitset::ConstIter Bitset::cend() const {
    return _bitset.cend();
}

int Bitset::Size() const {
    return _bitset.size();
}

bool Bitset::Empty() const {
    return Size() == 0;
}

bool Bitset::operator[](int index) const {
    return _bitset[index];
}

void Bitset::Push(bool bit){
    _bitset.push_back(bit);
}

Bitset& Bitset::Push(Iter start, Iter end){
    while(start != end) {
        _bitset.push_back(*start);
        ++start;
    }
    return *this;
}

Bitset& Bitset::Push(const Bitset& other){
    ConstIter start = other._bitset.begin();
    ConstIter end = other._bitset.end();
    while(start != end) {
        _bitset.push_back(*start);
        ++start;
    }
    return *this;
}

Bitset Bitset::operator+(bool bit){
    Bitset res = *this;
    res._bitset.push_back(bit);
    return res;
}

std::pair<char, Bitset::ConstIter> Bitset::GetByte(std::vector<bool>::const_iterator it) const {
    char ch = 0;
    int index = 0;
    while(index != 8){
        if(it + index < _bitset.end() && *(it + index))
            ch |= (1 << index);
        else
            ch &= ~(1 << index);
        ++index;
    }
    return {ch, it + index < _bitset.end() ? it + index : _bitset.end() };
}
