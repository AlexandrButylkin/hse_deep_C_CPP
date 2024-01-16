#ifndef VECTOR_MY_VECTOR_H
#define VECTOR_MY_VECTOR_H

#include <cstddef>
#include <utility>

class MyVector {
public:
    MyVector();
    explicit MyVector(std::size_t init_capacity);
    MyVector(const MyVector& vec);
    MyVector& operator=(const MyVector& vec);
    ~MyVector();

    void set(std::size_t index, int value);
    int get(std::size_t index) const;

    std::size_t size() const;
    std::size_t capacity() const;

    void reserve(std::size_t new_capacity);
    void resize(std::size_t new_size);

    void push_back(int value);
    void insert(std::size_t index, int value);
    void erase(std::size_t index);
private:
    static void copy_vector(MyVector& dist, const MyVector& src);

private:
    std::size_t _size = 0;
    std::size_t _capacity = 0;
    int * _data = nullptr;
};

#endif //VECTOR_MY_VECTOR_H

