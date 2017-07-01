#include<QtGlobal>

#include <initializer_list>

#include "Matrix.h"

namespace CalcApp
{

Matrix::Matrix(unsigned int columnCount, unsigned int rowCount, double fillValue)
{
    Q_UNUSED(columnCount);
    Q_UNUSED(rowCount);
    Q_UNUSED(fillValue);
}

Matrix::Matrix(std::initializer_list<double> const &data)
{
    Q_UNUSED(data);
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> const &data)
{
    Q_UNUSED(data);
}

unsigned int Matrix::GetColumnCount() const
{
}

unsigned int Matrix::GetRowCount() const
{
}

double Matrix::GetValue(unsigned row, unsigned column) const
{
    Q_UNUSED(row);
    Q_UNUSED(column);
}

void Matrix::SetValue(unsigned row, unsigned column, double value)
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    Q_UNUSED(value);
}

Matrix operator+(Matrix const &left, Matrix const &right)
{
    Q_UNUSED(left);
    Q_UNUSED(right);
}

Matrix operator-(Matrix const &left, Matrix const &right)
{
    Q_UNUSED(left);
    Q_UNUSED(right);
}

Matrix operator*(Matrix const &left, Matrix const &right)
{
    Q_UNUSED(left);
    Q_UNUSED(right);
}

Matrix& operator+=(Matrix& left, Matrix const& right)
{
    Q_UNUSED(left);
    Q_UNUSED(right);
}

Matrix& operator-=(Matrix& left, Matrix const& right)
{
    Q_UNUSED(left);
    Q_UNUSED(right);
}

Matrix& operator*=(Matrix& left, Matrix const& right)
{
    Q_UNUSED(left);
    Q_UNUSED(right);
}

}
