#pragma once

#include <initializer_list>
#include <memory>

namespace CalcApp
{

class MatrixImpl;

class Matrix
{
public:
    Matrix(unsigned int rowCount, unsigned int columnCount, double fillValue = 0);
    explicit Matrix(std::initializer_list<double> const &data);
    explicit Matrix(std::initializer_list<std::initializer_list<double>> const &data);
    explicit Matrix(std::shared_ptr<MatrixImpl> impl);

    // TODO (std_string) : think about default/custom impl
    Matrix(Matrix const &other) = default;
    Matrix(Matrix &&other) = default;
    Matrix& operator=(Matrix const &other) = default;
    Matrix& operator=(Matrix &&other) = default;

    unsigned int GetColumnCount() const;
    unsigned int GetRowCount() const;
    double GetValue(unsigned row, unsigned column) const;
    void SetValue(unsigned row, unsigned column, double value);
    std::shared_ptr<MatrixImpl> GetMatrixImpl() const;

    static Matrix CreateRowMatrix(std::initializer_list<double> const &data);
    static Matrix CreateColumnMatrix(std::initializer_list<double> const &data);

private:
    std::shared_ptr<MatrixImpl> _impl;
};

Matrix operator+(Matrix const &left, Matrix const &right);
Matrix operator-(Matrix const &left, Matrix const &right);
Matrix operator*(Matrix const &left, Matrix const &right);

Matrix& operator+=(Matrix& left, Matrix const& right);
Matrix& operator-=(Matrix& left, Matrix const& right);
Matrix& operator*=(Matrix& left, Matrix const& right);

}
