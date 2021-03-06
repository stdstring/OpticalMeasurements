#define ARMA_USE_CXX11
#define ARMA_DONT_USE_LAPACK
#define ARMA_DONT_USE_BLAS
#define ARMA_DONT_USE_NEWARP
#define ARMA_DONT_USE_ARPACK
#define ARMA_DONT_USE_SUPERLU
#define ARMA_DONT_USE_HDF5
#define ARMA_DONT_USE_OPENMP

#include<QtGlobal>

#include <initializer_list>
#include <stdexcept>

#include <armadillo>

#include "Matrix.h"

namespace CalcApp
{

class MatrixImpl
{
public:
    explicit MatrixImpl(arma::Mat<double> const &matrix);

    arma::Mat<double> Matrix;
};

MatrixImpl::MatrixImpl(arma::Mat<double> const &matrix) :
    Matrix(matrix)
{
}

Matrix::Matrix(unsigned int rowCount, unsigned int columnCount, double fillValue) :
     _impl(std::make_shared<MatrixImpl>(arma::Mat<double>(rowCount, columnCount)))
{
    _impl.get()->Matrix.fill(fillValue);
}

Matrix::Matrix(std::initializer_list<double> const &data) :
    _impl(std::make_shared<MatrixImpl>(arma::Mat<double>(data)))
{
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> const &data) :
    _impl(std::make_shared<MatrixImpl>(arma::Mat<double>(data)))
{
}

Matrix::Matrix(std::shared_ptr<MatrixImpl> impl) : _impl(impl)
{
}

unsigned int Matrix::GetColumnCount() const
{
    return _impl.get()->Matrix.n_cols;
}

unsigned int Matrix::GetRowCount() const
{
    return _impl.get()->Matrix.n_rows;
}

double Matrix::GetValue(unsigned row, unsigned column) const
{
    return _impl.get()->Matrix.at(row, column);
}

void Matrix::SetValue(unsigned row, unsigned column, double value)
{
    _impl.get()->Matrix.at(row, column) = value;
}

std::shared_ptr<MatrixImpl> Matrix::GetMatrixImpl() const
{
    return _impl;
}

Matrix Matrix::CreateRowMatrix(std::initializer_list<double> const &data)
{
    return Matrix(data);
}

Matrix Matrix::CreateColumnMatrix(std::initializer_list<double> const &data)
{
    Matrix matrix(data.size(), 1, 0);
    int row = 0;
    for (std::initializer_list<double>::iterator iterator = data.begin(); iterator != data.end(); ++iterator)
    {
        matrix.SetValue(row, 0, *iterator);
        ++row;
    }
    return matrix;
}

Matrix operator+(Matrix const &left, Matrix const &right)
{
    if (left.GetRowCount() != right.GetRowCount())
        throw std::invalid_argument("RowCount");
    if (left.GetColumnCount() != right.GetColumnCount())
        throw std::invalid_argument("ColumnCount");
    return Matrix(std::make_shared<MatrixImpl>(left.GetMatrixImpl().get()->Matrix + right.GetMatrixImpl().get()->Matrix));
}

Matrix operator-(Matrix const &left, Matrix const &right)
{
    if (left.GetRowCount() != right.GetRowCount())
        throw std::invalid_argument("RowCount");
    if (left.GetColumnCount() != right.GetColumnCount())
        throw std::invalid_argument("ColumnCount");
    return Matrix(std::make_shared<MatrixImpl>(left.GetMatrixImpl().get()->Matrix - right.GetMatrixImpl().get()->Matrix));
}

Matrix operator*(Matrix const &left, Matrix const &right)
{
    if (left.GetColumnCount() != right.GetRowCount())
        throw std::invalid_argument("ColumnCount/RowCount");
    return Matrix(std::make_shared<MatrixImpl>(left.GetMatrixImpl().get()->Matrix * right.GetMatrixImpl().get()->Matrix));
}

Matrix& operator+=(Matrix& left, Matrix const& right)
{
    if (left.GetRowCount() != right.GetRowCount())
        throw std::invalid_argument("RowCount");
    if (left.GetColumnCount() != right.GetColumnCount())
        throw std::invalid_argument("ColumnCount");
    left.GetMatrixImpl().get()->Matrix += right.GetMatrixImpl().get()->Matrix;
    return left;
}

Matrix& operator-=(Matrix& left, Matrix const& right)
{
    if (left.GetRowCount() != right.GetRowCount())
        throw std::invalid_argument("RowCount");
    if (left.GetColumnCount() != right.GetColumnCount())
        throw std::invalid_argument("ColumnCount");
    left.GetMatrixImpl().get()->Matrix -= right.GetMatrixImpl().get()->Matrix;
    return left;
}

Matrix& operator*=(Matrix& left, Matrix const& right)
{
    if (left.GetColumnCount() != right.GetRowCount())
        throw std::invalid_argument("ColumnCount/RowCount");
    left.GetMatrixImpl().get()->Matrix *= right.GetMatrixImpl().get()->Matrix;
    return left;
}

}
