#ifndef VECTORT_MY_VECTOR_H
#define VECTORT_MY_VECTOR_H

#include <cstddef>
#include <algorithm>
#include <ostream>
#include <cmath>

namespace containers {

    template <typename T>
    class my_vector_buf {
    protected:
        explicit my_vector_buf(std::size_t capacity);

        my_vector_buf(const my_vector_buf&) = delete;
        my_vector_buf& operator=(const my_vector_buf&) = delete;

        my_vector_buf(my_vector_buf&&) noexcept;
        my_vector_buf& operator=(my_vector_buf&&) noexcept;

        ~my_vector_buf();
    protected:

        void allocate(std::size_t capacity) {
            _array = capacity == 0 ? nullptr : static_cast<T*>(::operator new(sizeof(T) * capacity));
            _capacity = capacity;
        }

    protected:
        T* _array = nullptr;
        std::size_t _capacity = 0;
        std::size_t _size = 0;
    };

    template<typename T>
    class my_vector : private my_vector_buf<T>{
    protected:
        using my_vector_buf<T>::_array;
        using my_vector_buf<T>::_size;
        using my_vector_buf<T>::_capacity;

    public:
        my_vector();
        my_vector(std::size_t, const T& = T());

        my_vector(const my_vector&);
        my_vector& operator=(const my_vector&);

        my_vector(my_vector &&rhs) = default;
        my_vector &operator=(my_vector &&rhs) = default;
    private:
        static my_vector createAndCopy(std::size_t capacity, const T* start, const T* end);

    public:
        std::size_t size() const;
        std::size_t capacity() const;
        bool empty() const;

        void resize(std::size_t, const T& obj = T());
        void reserve(std::size_t);

        const T& operator[](std::size_t) const;
        T& operator[](std::size_t);

        void push_back(const T&);
        void pop_back();
        void clear();
    };

    template<typename T>
    std::ostream& operator<<(std::ostream&, const my_vector<T>&);
}

namespace containers {

    std::size_t getMinCapacity(std::size_t capacity){
        std::size_t newCapacity = 1;
        std::size_t degree = 0;
        while(newCapacity < capacity){
            newCapacity = static_cast<std::size_t>(std::pow(2, static_cast<double>(degree)));
            ++degree;
        }
        return newCapacity;
    }

    template <typename T>
    void Construct(T* pos, const T& obj){
        new(pos) T(obj);
    }

    template <typename T>
    void Destroy(T* obj) noexcept {
        obj->~T();
    }

    template <typename FwdIter>
    void Destroy(FwdIter start, FwdIter end) noexcept {
        while(start != end){
            Destroy(&*start++);
        }
    }

    template <typename T>
    my_vector_buf<T>::my_vector_buf(size_t capacity) :
            _array(capacity == 0 ? nullptr : static_cast<T*>(::operator new(sizeof(T) * capacity))),
            _capacity(capacity)
    {}

    template <typename T>
    my_vector_buf<T>::my_vector_buf(my_vector_buf&& other) noexcept : _array(other._array), _capacity(other._capacity), _size(other._size) {
        other._array = nullptr;
        other._capacity = 0;
        other._size = 0;
    }

    template <typename T>
    my_vector_buf<T>& my_vector_buf<T>::operator=(my_vector_buf<T>&& other) noexcept {
        std::swap(_array, other._array);
        std::swap(_capacity, other._capacity);
        std::swap(_size, other._size);
        return *this;
    }

    template <typename T>
    my_vector_buf<T>::~my_vector_buf() {
        Destroy(_array, _array + _size);
        ::operator delete(_array);
    }

    template <typename T>
    my_vector<T>::my_vector() : my_vector_buf<T>(0) {}

    template <typename T>
    my_vector<T>::my_vector(std::size_t capacity, const T& obj) : my_vector_buf<T>(capacity > 0 ? getMinCapacity(capacity) : capacity) {
        while(_size < capacity){
            Construct(_array + _size, obj);
            ++_size;
        }
    }

    template <typename T>
    my_vector<T>::my_vector(const my_vector& other) : my_vector_buf<T>(other._capacity) {
        while(_size < other._size){
            Construct(_array + _size, other._array[_size]);
            ++_size;
        }
    }

    template <typename T>
    my_vector<T>& my_vector<T>::operator=(const my_vector<T>& other) {
        my_vector tmp(other);
        std::swap(*this, tmp);
        return *this;
    }

    template <typename T>
    my_vector<T> my_vector<T>::createAndCopy(std::size_t capacity, const T* start, const T* end){
        my_vector vec;
        vec.allocate(capacity);
        while(start != end){
            Construct(vec._array + vec._size, *start++);
            ++vec._size;
        }
        return vec;
    }

    template <typename T>
    std::size_t my_vector<T>::size() const { return _size; }

    template <typename T>
    std::size_t my_vector<T>::capacity() const { return _capacity; }

    template <typename T>
    bool my_vector<T>::empty() const { return _size == 0; }

    template <typename T>
    void my_vector<T>::resize(std::size_t size, const T& obj){
        std::size_t newCapacity = 0;
        if(size > 2 * _capacity)    newCapacity = size;
        else if(size > _capacity)   newCapacity = 2 * _capacity;

        if(newCapacity != 0){
            reserve(newCapacity);
        }

        if(_size > size){
            Destroy(_array + size, _array + _size);
            _size = size;
        }
        else if(_size < size){
            while(_size != size){
                Construct(_array + _size, obj);
                ++_size;
            }
        }
    }

    template <typename T>
    void my_vector<T>::reserve(std::size_t capacity) {
        if(capacity > _capacity) {
            my_vector<T> tmp = my_vector::createAndCopy(getMinCapacity(capacity), _array, _array + _size);
            std::swap(*this, tmp);
        }
    }

    template <typename T>
    const T& my_vector<T>::operator[](std::size_t index) const {
        return _array[index];
    }

    template <typename T>
    T& my_vector<T>::operator[](std::size_t index) {
        return const_cast<T&>(static_cast<const my_vector&>(*this)[index]);
    }

    template <typename T>
    void my_vector<T>::push_back(const T& t) {
        if(_size == 0 && _capacity == 0)
            reserve(1);
        else if(_size == _capacity)
            reserve(_capacity * 2);
        Construct(_array + _size, t);
        ++_size;
    }

    template <typename T>
    void my_vector<T>::pop_back() {
        --_size;
        Destroy(_array + _size);
    }

    template <typename T>
    void my_vector<T>::clear() {
        Destroy(_array, _array + _size);
        _size = 0;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const my_vector<T>& vector) {
        for(std::size_t i = 0, size = vector.size(); i < size; ++i){
            if (i != 0)
                os << " ";
            os << vector[i];
        }

        return os;
    }
}

#endif //VECTORT_MY_VECTOR_H
