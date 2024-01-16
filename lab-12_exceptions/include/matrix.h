#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>
#include <vector>
#include <array>
#include <fstream>

class MatrixException : public std::exception {
public:
    MatrixException(const std::string& msg);
    std::string GetMsg() const;
private:
    std::string _msg;
};

class Matrix {
private:
    using Row = std::vector<int>;
public:
    Matrix();
    Matrix(int rows, int columns);
    Matrix(const Matrix& matrix);
    Matrix& operator= (const Matrix& matrix);
    Matrix(Matrix&& matrix);
    Matrix& operator=(Matrix&& matrix);

    int Get(int row, int column);
    Row& operator[] (int index);
    const Row& operator[] (int index) const;

    int Rows() const;
    int Columns() const;

private:
    using MatrixCont = std::vector<Row>;

    MatrixCont _matrix;
};

Matrix& operator+=(Matrix& left, const Matrix& right);
Matrix& operator *=(Matrix& left, const Matrix& right);

void ReadNumber(std::ifstream& in, int& number);
std::ifstream OpenFile(const std::string& path);

class Manager {
public:

    Manager();

    void Load(int index, const std::string& path);
    void Print(int index) const;
    void Add(int left, int right);
    void Mul(int left, int right);
    void Elem(int index, int row, int column);

private:
    std::array<Matrix, 10> _regs;
};


#endif //MATRIX_MATRIX_H
