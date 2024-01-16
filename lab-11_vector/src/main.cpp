#include <iostream>
#include <sstream>
#include <cstring>

#include "my_vector.h"

namespace product {

    class Product {
    public:
        Product(const char* name, int quantity, double price) : _quantity(quantity), _price(price)  {
            _name = new char[strlen(name) + 1];
            strcpy(_name, name);
        }

        Product(const Product& prod) : _quantity(prod._quantity), _price(prod._price)  {
            _name = new char[strlen(prod._name) + 1];
            strcpy(_name, prod._name);
        }

        ~Product() {
            delete [] _name;
        }

        char* Name() const { return _name; }
        int Quantity() const { return _quantity; }
        double Price() const { return _price; }

    private:
        char* _name = nullptr;  // Указатель владеет C-style строкой, на которую указывает.
        int _quantity = 0;
        double _price = 0.0;
    };

    std::ostream& operator<<(std::ostream& os, const product::Product& prod){
        os << prod.Name() << " " << prod.Quantity() << " " << prod.Price();
        return os;
    }

    void print(const containers::my_vector<Product>& v) {
        std::cout << v << std::endl;
    }

}  // namespace product


namespace {
    template <typename T>
    bool TestDefaultCtor() {
        containers::my_vector<T> vec;
        const bool result = vec.size() == 0 &&
                            vec.capacity() == 0 &&
                            vec.empty() == true;

        return result;
    }

    template <typename T>
    bool TestSizeCtor(const T& obj1, const T& obj2) {
        containers::my_vector<T> vec1(0);
        const bool result1 = vec1.size() == 0 && vec1.capacity() == 0 && vec1.empty() == true;

        containers::my_vector<T> vec2(10);
        const bool result2 = vec2.size() == 10 && vec2.capacity() == 16 && vec2.empty() == false;

        containers::my_vector<T> vec3(3, obj1);
        const bool result3 = vec3.size() == 3 && vec3.capacity() == 4 && vec3.empty() == false;

        return result1 && result2 && result3;
    }

    template <typename T>
    bool TestReserve() {
        containers::my_vector<T> vec;
        bool result = vec.size() == 0 &&
                      vec.capacity() == 0 &&
                      vec.empty() == true;

        vec.reserve(5);
        result &= vec.size() == 0 &&
                  vec.capacity() == 8 &&
                  vec.empty() == true;

        vec.reserve(2);
        result &= vec.size() == 0 &&
                  vec.capacity() == 8 &&
                  vec.empty() == true;

        vec.reserve(10);
        result &= vec.size() == 0 &&
                  vec.capacity() == 16 &&
                  vec.empty() == true;

        vec.reserve(0);
        result &= vec.size() == 0 &&
                  vec.capacity() == 16 &&
                  vec.empty() == true;

        vec.reserve(15);
        result &= vec.size() == 0 &&
                  vec.capacity() == 16 &&
                  vec.empty() == true;

        return result;
    }

    template <typename T>
    bool TestPushBack(const T& obj1, const T& obj2) {
        containers::my_vector<T> vec;
        bool result = vec.size() == 0 &&
                      vec.capacity() == 0 &&
                      vec.empty() == true;

        vec.push_back(obj1);
        result &= vec.size() == 1 &&
                  vec.capacity() == 1 &&
                  vec.empty() == false;

        vec.push_back(obj2);
        result &= vec.size() == 2 &&
                  vec.capacity() == 2 &&
                  vec.empty() == false;

        vec.push_back(obj1);
        result &= vec.size() == 3 &&
                  vec.capacity() == 4 &&
                  vec.empty() == false;

        vec.push_back(obj2);
        result &= vec.size() == 4 &&
                  vec.capacity() == 4 &&
                  vec.empty() == false;

        vec.push_back(obj1);
        result &= vec.size() == 5 &&
                  vec.capacity() == 8 &&
                  vec.empty() == false;

        return result;
    }

    template <typename T>
    bool TestAssignmentOperator(const T& obj1, const T& obj2) {
        containers::my_vector<T> vec1;
        bool result = vec1.size() == 0 &&
                      vec1.capacity() == 0 &&
                      vec1.empty() == true;

        vec1.push_back(obj1);
        vec1.push_back(obj2);
        vec1.push_back(obj1);
        vec1.push_back(obj2);

        result &= vec1.size() == 4 &&
                  vec1.capacity() == 4 &&
                  vec1.empty() == false;

        containers::my_vector<T> vec2;
        result &= vec2.size() == 0 &&
                  vec2.capacity() == 0 &&
                  vec2.empty() == true;

        vec2 = vec1;
        result &= vec2.size() == 4 &&
                  vec2.capacity() == 4 &&
                  vec2.empty() == false;

        return result;
    }

    template <typename T>
    bool TestCopyCtor(const T& obj1, const T& obj2) {
        containers::my_vector<T> vec1;
        for(std::size_t i = 0, size = 5; i < size; ++i){
            vec1.push_back(obj1);
        }

        containers::my_vector<T> vec2(vec1);

        bool result = vec1.size() == 5 &&
                      vec1.empty() == false &&
                      vec1.capacity() == 8 &&
                      vec2.size() == 5 &&
                      vec2.empty() == false &&
                      vec2.capacity() == 8;

        std::stringstream os1;
        std::stringstream os2;
        for(std::size_t i = 0, size = vec1.size(); result && i < size; ++i){
            os1 << vec1[i];
            os2 << vec2[i];
        }

        result &= os1.str() == os2.str();

        return result;
    }

    template <typename T>
    bool TestResize() {
        containers::my_vector<T> vec;
        bool result = vec.size() == 0 && vec.capacity() == 0 && vec.empty() == true;

        vec.resize(5);
        result &= vec.size() == 5 && vec.capacity() == 8 && vec.empty() == false;

        vec.resize(2);
        result &= vec.size() == 2 && vec.capacity() == 8 && vec.empty() ==false;

        vec.resize(10);
        result &= vec.size() == 10 && vec.capacity() == 16 && vec.empty() == false;

        vec.resize(0);
        result &= vec.size() == 0 && vec.capacity() == 16 && vec.empty() == true;

        vec.resize(15);
        result &= vec.size() == 15 && vec.capacity() == 16 && vec.empty() == false;

        return result;
    }

    template <typename T>
    bool TestPopBack(const T& obj1, const T& obj2) {
        containers::my_vector<T> vec;
        for(std::size_t i = 0, size = 5; i < size; ++i){
            vec.push_back(obj1);
        }

        bool result = vec.size() == 5 &&
                      vec.empty() == false &&
                      vec.capacity() == 8;

        vec.pop_back();
        result &= vec.size() == 4 &&
                  vec.empty() == false &&
                  vec.capacity() == 8;
        vec.pop_back();
        result &= vec.size() == 3 &&
                  vec.empty() == false &&
                  vec.capacity() == 8;
        vec.pop_back();
        result &= vec.size() == 2 &&
                  vec.empty() == false &&
                  vec.capacity() == 8;
        vec.pop_back();
        result &= vec.size() == 1 &&
                  vec.empty() == false &&
                  vec.capacity() == 8;
        vec.pop_back();
        result &= vec.size() == 0 &&
                  vec.empty() == true &&
                  vec.capacity() == 8;
        return result;
    }

    template <typename T>
    bool TestClear(const T& obj1, const T& obj2) {
        containers::my_vector<T> vec;
        for(std::size_t i = 0, size = 5; i < size; ++i){
            vec.push_back(obj1);
        }

        bool result = vec.size() == 5 &&
                      vec.empty() == false &&
                      vec.capacity() == 8;

        vec.clear();
        result &= vec.size() == 0 &&
                  vec.empty() == true &&
                  vec.capacity() == 8;

        return result;
    }
}


template <typename T>
bool test_my_vector_default_constructible(const T& obj1, const T& obj2){
    const bool defaultCtor = TestDefaultCtor<T>();
    const bool sizeCtor = TestSizeCtor<T>(obj1, obj2);
    const bool reserve = TestReserve<T>();
    const bool pushBack = TestPushBack<T>(obj1, obj2);
    const bool assignmentOperator = TestAssignmentOperator<T>(obj1, obj2);
    const bool copyCtor = TestCopyCtor<T>(obj1, obj2);
    const bool resize = TestResize<T>();
    const bool popBack = TestPopBack(obj1, obj2);
    const bool clear = TestClear(obj1, obj2);

    return defaultCtor && sizeCtor && reserve && pushBack && assignmentOperator && copyCtor && resize && popBack && clear;
};

template <typename T>
bool test_my_vector(const T& obj1, const T& obj2){
    const bool defaultCtor = TestDefaultCtor<T>();
    const bool reserve = TestReserve<T>();
    const bool pushBack = TestPushBack<T>(obj1, obj2);
    const bool assignmentOperator = TestAssignmentOperator<T>(obj1, obj2);
    const bool copyCtor = TestCopyCtor<T>(obj1, obj2);
    const bool popBack = TestPopBack(obj1, obj2);
    const bool clear = TestClear(obj1, obj2);

    return defaultCtor && reserve && pushBack && assignmentOperator && copyCtor && popBack && clear;
};

int main() {

    containers::my_vector<int> v;
    v.push_back(2);
    const int n { 3 };
    v.push_back(n);
    std::cout << v << std::endl;

    int int_a = 1, int_b = 2;
    product::Product product_a("abc", 123, 1.23);
    product::Product product_b("dfe", 456, 5.56);

    containers::my_vector<product::Product> vec(3, product_a);
    vec.reserve(20);


    std::cout << test_my_vector<int>(int_a, int_b) << std::endl;
    std::cout << test_my_vector<product::Product>(product_a, product_b) << std::endl;
    std::cout << test_my_vector_default_constructible<int>(int_a, int_b) << std::endl;

    return 0;

}

