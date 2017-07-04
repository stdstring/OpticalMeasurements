#include <cmath>

#include "Matrix.h"
#include "MatrixFactory.h"

namespace CalcApp
{

// Rotation matrices
Matrix CreateXRotationMatrix(double angle)
{
    double cosValue = cos(angle);
    double sinValue = sin(angle);
    return Matrix({{1, 0, 0, 0}, {0, cosValue, -sinValue, 0}, {0, sinValue, cosValue, 0}, {0, 0, 0, 1}});
}

Matrix CreateYRotationMatrix(double angle)
{
    double cosValue = cos(angle);
    double sinValue = sin(angle);
    return Matrix({{cosValue, 0, sinValue, 0}, {0, 1, 0, 0}, {-sinValue, 0, cosValue, 0}, {0, 0, 0, 1}});
}

Matrix CreateZRotationMatrix(double angle)
{
    double cosValue = cos(angle);
    double sinValue = sin(angle);
    return Matrix({{cosValue, -sinValue, 0, 0}, {sinValue, cosValue, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
}

// Transfer matrices
Matrix CreateXTransferMatrix(double shift)
{
    return Matrix({{1, 0, 0, shift}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
}

Matrix CreateYTransferMatrix(double shift)
{
    return Matrix({{1, 0, 0, 0}, {0, 1, 0, shift}, {0, 0, 1, 0}, {0, 0, 0, 1}});
}

Matrix CreateZTransferMatrix(double shift)
{
    return Matrix({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, shift}, {0, 0, 0, 1}});
}

}
