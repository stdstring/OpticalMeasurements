#define ARMA_USE_CXX11

#include<QtGlobal>

#include <initializer_list>

#include <armadillo>

#include "Matrix.h"

namespace CalcApp
{

class Matrix::MatrixImpl
{
public:
    arma::Mat<double> Matrix;
    unsigned int ColumnCount;
    unsigned int RowCount;
};

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
    return _impl.get()->ColumnCount;
}

unsigned int Matrix::GetRowCount() const
{
    return _impl.get()->RowCount;
}

double Matrix::GetValue(unsigned row, unsigned column) const
{
    return _impl.get()->Matrix.at(row, column);
}

void Matrix::SetValue(unsigned row, unsigned column, double value)
{
    _impl.get()->Matrix.at(row, column) = value;
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
