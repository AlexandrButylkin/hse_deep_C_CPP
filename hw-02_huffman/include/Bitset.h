#ifndef HUFFMAN_BITSET_H
#define HUFFMAN_BITSET_H

#include <vector>

class Bitset{
public:
    Bitset() = default;
    //Bitset(const Bitset& bitset);
    Bitset(char ch);
    //Bitset operator=(const Bitset& bitset);

    using Iter = std::vector<bool>::iterator;
    using ConstIter = std::vector<bool>::const_iterator;

    Iter begin();
    Iter end();
    ConstIter cbegin() const;
    ConstIter cend() const;

    int Size() const;
    bool Empty() const ;
    bool operator[](int index) const;

    void Push(bool bit);
    Bitset& Push(Iter start, Iter end);
    Bitset& Push(const Bitset& other);
    Bitset operator+(bool bit);

    std::pair<char, ConstIter> GetByte(std::vector<bool>::const_iterator it) const;

private:
    std::vector<bool> _bitset;
};

#endif //HUFFMAN_BITSET_H
