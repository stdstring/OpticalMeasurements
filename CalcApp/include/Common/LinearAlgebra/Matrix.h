#pragma once

#include <initializer_list>

namespace CalcApp
{

class Matrix
{
public:
    Matrix(unsigned int columnCount, unsigned int rowCount, double fillValue = 0);
    explicit Matrix(std::initializer_list<double> const &data);
    explicit Matrix(std::initializer_list<std::initializer_list<double>> const &data);
    // TODO (std_string) : think about default/custom impl
    explicit Matrix(Matrix const &other) = default;
    explicit Matrix(Matrix &&other) = default;
    Matrix& operator=(Matrix const &other) = default;
    Matrix& operator=(Matrix &&other) = default;

    unsigned int GetColumnCount() const;
    unsigned int GetRowCount() const;
    double GetValue(unsigned row, unsigned column) const;
    void SetValue(unsigned row, unsigned column, double value);
};

Matrix operator+(Matrix const &left, Matrix const &right);
Matrix operator-(Matrix const &left, Matrix const &right);
Matrix operator*(Matrix const &left, Matrix const &right);

Matrix& operator+=(Matrix& left, Matrix const& right);
Matrix& operator-=(Matrix& left, Matrix const& right);
Matrix& operator*=(Matrix& left, Matrix const& right);

}
