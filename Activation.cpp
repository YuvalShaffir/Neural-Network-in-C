#include "Activation.h"
#include "Matrix.h"
#include <cmath>


// The rectified linear unit (ReLU), maps the input to the output by setting
// all negative values to zero and leaving all positive values unchanged.
Matrix relu(const Matrix& matrix)
{
  //create new matrix object
  int rows = matrix.get_rows();
  int cols = matrix.get_cols();
  Matrix result(rows, cols);

  //take only non-negative elements from the matrix
  for(int i=0; i<rows; i++)
  {
    for(int j=0; j<cols; i++)
    {
      result(i,j) = std::max(0, matrix(i,j));
    }
  }

  return result;
}

//The softmax function maps a vector of real values to a probability
// distribution.
Matrix softmax(const Matrix& matrix)
{
  //create new matrix object
  int rows = matrix.get_rows();
  int cols = matrix.get_cols();
  Matrix result(rows, cols);

  //exponent each element of the matrix
  for(int i=0; i<rows; i++)
  {
    for(int j=0; j<cols; i++)
    {
      result(i,j) = std::exp(matrix(i,j));
    }
  }

  //Normalize:
  result = result * (1/result.sum());

  return result;
}