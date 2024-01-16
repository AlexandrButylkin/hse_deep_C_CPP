#include "matrix.h"
#include <algorithm>

void Matrix::init_memory(){
    int* tmp = new int[_rows * _cols] ();
    _data = new int* [_rows] ();
    for(size_t i = 0; i < _rows; ++i){
        _data[i] = tmp + _cols * i;
    }
}

void Matrix::copy_elements(Matrix& dist, const Matrix& src){
    for(size_t i = 0; i < src._rows; ++i){
        for(size_t j = 0; j < src._cols; ++j){
            dist._data[i][j] = src._data[i][j];
        }
    }
}

Matrix::Matrix(std::size_t r, std::size_t c) :_rows(r), _cols(c) {
    init_memory();
}

Matrix::Matrix(const Matrix& m) :_rows(m._rows), _cols(m._cols) {
    init_memory();
    copy_elements(*this, m);
}

Matrix::~Matrix(){
    delete[] _data[0];
    delete[] _data;
}

Matrix& Matrix::operator=(const Matrix &m) {
    delete[] _data[0];
    delete[] _data;
    _rows = m._rows;
    _cols = m._cols;
    init_memory();
    copy_elements(*this, m);
    return *this;
}

std::size_t Matrix::get_rows() const {
    return _rows;
}

std::size_t Matrix::get_cols() const {
    return _cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  return _data[i][j];
}

void Matrix::print(FILE* f) {

    const char* format = " %d";
    const char* firstFormat = "%d";
    for(size_t i = 0; i < _rows; ++i){
        for(size_t j = 0; j < _cols; ++j){
            fprintf(f, j == 0 ? firstFormat : format, get(i, j));
        }
        fprintf(f, "\n");
    }
}

bool Matrix::operator==(const Matrix& m) const {
    if(_cols == m._cols && _rows == m._rows){
        for(size_t i = 0; i < _rows; ++i){
            int* row1 = _data[i];
            int* row2 = m._data[i];
            for(size_t j = 0; j < _cols; ++j){
                if(row1[j] != row2[j]){
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool Matrix::operator!=(const Matrix& m) const {
  return !(*this == m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
    *this = *this + m;
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    *this = *this - m;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    *this = *this * m;
    return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
    Matrix tmp(_rows, _cols);
    for(size_t i = 0; i < _rows; ++i){
        int* row1 = _data[i];
        int* row2 = m._data[i];
        for(size_t j = 0; j < _cols; ++j){
            tmp.set(i, j, row1[j] + row2[j]);
        }
    }
    return tmp;
}

Matrix Matrix::operator-(const Matrix& m) const {
    Matrix tmp(_rows, _cols);
    for(size_t i = 0; i < _rows; ++i){
        int* row1 = _data[i];
        int* row2 = m._data[i];
        for(size_t j = 0; j < _cols; ++j){
            tmp.set(i, j, row1[j] - row2[j]);
        }
    }
    return tmp;
}

Matrix Matrix::operator*(const Matrix& m) const {
    Matrix tmp(_rows, m._cols);
    for(size_t row = 0; row < tmp._rows; ++row){
        for(size_t col = 0; col < tmp._cols; ++col){
            int val = 0;
            for(size_t i = 0; i < _cols; ++i){
                val += _data[row][i] * m._data[i][col];
            }
            tmp.set(row, col, val);
        }
    }
    return tmp;
}
