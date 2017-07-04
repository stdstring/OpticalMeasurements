#pragma once

#include "Matrix.h"

namespace CalcApp
{

// Rotation matrices
Matrix CreateXRotationMatrix(double angle);
Matrix CreateYRotationMatrix(double angle);
Matrix CreateZRotationMatrix(double angle);

// Transfer matrices
Matrix CreateXTransferMatrix(double shift);
Matrix CreateYTransferMatrix(double shift);
Matrix CreateZTransferMatrix(double shift);

}
