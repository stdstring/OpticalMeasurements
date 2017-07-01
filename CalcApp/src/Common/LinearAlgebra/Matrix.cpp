#include <initializer_list>

#include "Matrix.h"

namespace CalcApp
{

Matrix::Matrix(unsigned int columnCount, unsigned int rowCount, double fillValue)
{
}

Matrix::Matrix(std::initializer_list<double> const &data)
{
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> const &data)
{
}

unsigned int Matrix::GetColumnCount() const
{
}

unsigned int Matrix::GetRowCount() const
{
}

double Matrix::GetValue(unsigned row, unsigned column) const
{
}

void Matrix::SetValue(unsigned row, unsigned column, double value)
{
}

Matrix operator+(Matrix const &left, Matrix const &right)
{
}

Matrix operator-(Matrix const &left, Matrix const &right)
{
}

Matrix operator*(Matrix const &left, Matrix const &right)
{
}

Matrix& operator+=(Matrix& left, Matrix const& right)
{
}

Matrix& operator-=(Matrix& left, Matrix const& right)
{
}

Matrix& operator*=(Matrix& left, Matrix const& right)
{
}

}
