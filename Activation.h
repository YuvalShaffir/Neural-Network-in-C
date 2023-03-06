#include "Matrix.h"
#include <cmath>

#ifndef ACTIVATION_H
#define ACTIVATION_H

// The rectified linear unit (ReLU), maps the input to the output by setting
// all negative values to zero and leaving all positive values unchanged.
Matrix relu(const Matrix& matrix);

//The softmax function maps a vector of real values to a probability
// distribution.
Matrix softmax(const Matrix& matrix);

#endif //ACTIVATION_H