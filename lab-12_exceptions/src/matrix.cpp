#include "matrix.h"
#include <iostream>
#include <array>

MatrixException::MatrixException(const std::string& msg) : _msg(msg) {}

std::string MatrixException::GetMsg() const {
    return _msg;
}


Matrix::Matrix() :_matrix(0) {}

Matrix::Matrix(int rows, int columns) : _matrix(rows, Row(columns)) {}

Matrix::Matrix(const Matrix& matrix) : _matrix(matrix._matrix) {}

Matrix& Matrix::operator= (const Matrix& matrix) {
    _matrix = matrix._matrix;
    return *this;
}

Matrix::Matrix(Matrix&& matrix) : _matrix(std::move(matrix._matrix)) {}

Matrix& Matrix::operator=(Matrix&& matrix) {
    _matrix = std::move(matrix._matrix);
    return *this;
}

int Matrix::Get(int row, int column){
    if(row >= 0 && row < Rows() && column >= 0 && column < Columns())
        return _matrix[row][column];
    throw MatrixException("ACCESS: bad index.");
}

Matrix::Row& Matrix::operator[] (int index) {
    if(index >= 0 && index < Rows())
        return _matrix[index];
    throw MatrixException("ACCESS: bad index.");
}

const Matrix::Row& Matrix::operator[] (int index) const {
    if(index >= 0 && index < Rows())
        return _matrix[index];
    throw MatrixException("ACCESS: bad index.");
}

int Matrix::Rows() const {
    return static_cast<int>(_matrix.size());
}

int Matrix::Columns() const {
    return !_matrix.empty() ? static_cast<int>(_matrix[0].size()) : 0;
}

Matrix& operator+=(Matrix& left, const Matrix& right){
    if(left.Rows() != right.Rows() || left.Columns() != right.Columns())
        throw MatrixException("ADD: dimensions do not match.");
    else {
        Matrix matrix(left.Rows(), left.Columns());
        for(int i = 0; i < left.Rows(); ++i){
            for(int j = 0; j < left.Columns(); ++j){
                matrix[i][j] = left[i][j] + right[i][j];
            }
        }
        std::swap(left, matrix);
        return left;
    }
}

Matrix& operator *=(Matrix& left, const Matrix& right) {
    if(left.Columns() != right.Rows())
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    else {
        Matrix matrix(left.Rows(), right.Columns());
        for(int i = 0; i < left.Rows(); ++i){
            for(int j = 0; j < right.Columns(); ++j){
                for (int inner = 0; inner < left.Columns(); inner++) {
                    matrix[i][j] += left[i][inner] * right[inner][j];
                }
            }
        }
        std::swap(left, matrix);
        return left;
    }
}

void ReadNumber(std::ifstream& in, int& number) {
    if(in >> number)
        return;
    throw MatrixException("LOAD: invalid file format.");
}

std::ifstream OpenFile(const std::string& path){
    std::ifstream file;
    file.open(path);
    if(!file.is_open()) {
        throw MatrixException("LOAD: unable to open file.");
    }
    return file;
}


Manager::Manager() {
    _regs.fill(Matrix());
}

void Manager::Load(int index, const std::string& path) {
    try{
        std::ifstream file = OpenFile(path);

        int rows, columns, number;
        ReadNumber(file, rows);
        ReadNumber(file, columns);
        Matrix matrix(rows, columns);

        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < columns; ++j) {
                ReadNumber(file, number);
                matrix[i][j] = number;
            }
        }
        _regs[index] = std::move(matrix);

    }
    catch (MatrixException& msg) {
        std::cout << msg.GetMsg() << std::endl;
    }
    catch(const std::bad_alloc& ex){
        std::cout << "Unable to allocate memory." << std::endl;
    }
}

void Manager::Print(int index) const {
    for(int i = 0; i < _regs[index].Rows(); ++i){
        for(int j = 0; j < _regs[index].Columns(); ++j){
            if(j != 0){
                std::cout << " ";
            }
            std::cout << _regs[index][i][j];
        }
        std::cout << std::endl;
    }
}

void Manager::Add(int left, int right) {
    try {
        _regs[left] += _regs[right];
    }
    catch (MatrixException& msg) {
        std::cout << msg.GetMsg() << std::endl;
    }
    catch(const std::bad_alloc& ex){
        std::cout << "Unable to allocate memory." << std::endl;
    }
}

void Manager::Mul(int left, int right) {
    try {
        _regs[left] *= _regs[right];
    }
    catch (MatrixException& msg) {
        std::cout << msg.GetMsg() << std::endl;
    }
    catch(const std::bad_alloc& ex){
        std::cout << "Unable to allocate memory." << std::endl;
    }
}

void Manager::Elem(int index, int row, int column){
    try {
        std::cout << _regs[index].Get(row, column) << std::endl;
    }
    catch (MatrixException& msg){
        std::cout << msg.GetMsg() << std::endl;
    }
}