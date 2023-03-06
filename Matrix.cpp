#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <cmath>

#define NOT_ZERO 0.1

Matrix::Matrix(int rows, int cols)
{
  // create a 2D array with size of matrix, and initialize all elements to
  // zero.
  _mat = new float[rows * cols]{};
  _rows = rows;
  _cols = cols;
}

Matrix::Matrix():Matrix(0,0){}

Matrix::Matrix(const Matrix& m)
{
  _cols = m._cols;
  _rows = m._rows;

  for(int i=0; i<_rows; i++)
  {
    for(int j=0; j<_cols; j++)
    {
      _mat[i*_cols +j] = m._mat[i*_cols +j];
    }
  }
}


/*Return the number of rows*/
int Matrix::get_rows() const
{
  return _rows;
}


/*Return the number of columns*/
int Matrix::get_cols() const
{
  return _cols;
}

/*copy and swap operator*/
Matrix& Matrix::operator=(Matrix rhs)
{
  //todo: add a check here
//  if(this == &(rhs._mat))
//  {
//    return *this;
//  }

  std::swap(this->_rows, rhs._rows);
  std::swap(this->_cols, rhs._cols);
  std::swap(this->_mat, rhs._mat);
  return *this;
}


/*For i,j indexes, matrix(i,j) will return the element in the i,j index of
 * the matrix.
 * */
float& Matrix::operator()(int i,int j) const
{
  return _mat[i*_cols +j];
}

float& Matrix::operator()(int i,int j)
{
  return _mat[i*_cols +j];
}


/*
 * For i index, matrix[i] will return the i'th element.
 * */
float& Matrix::operator[](int i) const
{
  return _mat[i];
}

const Matrix& Matrix::operator+=(const Matrix& rhs) const
{
  if ((_rows != rhs._rows)||(_cols != rhs._cols))
  {
    throw std::domain_error("Dimension don't match");
  }
  for(int i=0; i<(_rows*_cols); i++)
  {
    (*this)[i] += rhs[i];
  }
  return *this;
}

Matrix Matrix::operator+(const Matrix& rhs) const
{
  //check the dimensions match:
  if((_rows != rhs._rows)||(_cols != rhs._cols))
  {
    throw std::domain_error("Dimension don't match");
  }
  Matrix result(_rows, _cols);
  for(int i=0; i< _rows * _cols; i++)
  {
    result[i] = (*this)[i] + rhs[i];
  }
  return result;
}

Matrix Matrix::operator*(const Matrix& rhs)
{
  if(_cols != rhs._rows)
  {
    throw std::domain_error("left  hand side matrix columns number don't "
                            "match the right hand "
                            "side matrix rows number.");
  }

  Matrix result(_rows, rhs._cols);
  float sum_single_line;
  for(int i=0; i<_rows; i++)
  {

    for(int j=0; j<_cols; j++)
    {
      sum_single_line = 0;
      for(int k=0; k<rhs._rows; k++)
      {
        sum_single_line += (*this)(i, k) * rhs(k, j);
      }
      result(i,j) = sum_single_line;
    }
  }
  return result;
}

Matrix operator*(Matrix& m, float& rhs)
{
  Matrix result(m._rows, m._cols);
  for(int i=0; i<m._rows*m._cols; i++)
  {
    result[i] = m[i] * rhs;
  }
  return result;
}

Matrix operator*(float& lhs, Matrix& m)
{
  Matrix result(m._rows, m._cols);
  for(int i=0; i<m._rows*m._cols; i++)
  {
    result[i] = lhs * m[i];
  }
  return result;
}


//output operator
std::ostream& operator<<(std::ostream& output, Matrix& m)
{
  for(int i=0; i<m._rows; i++)
  {
    for(int j=0; j<m._cols; j++)
    {
      if(m(i,j) > NOT_ZERO)
      {
        output << "**";
      }
      else
      {
        output << "  ";
      }
    }
    output << "\n";
  }
  return output;
}

//input operator
std::istream& operator>>(std::istream& input, Matrix& m)
{
  //read the matrix from the input stream into the array.
  input.read((char*)m._mat, m._rows * m._cols * sizeof(float));
  return input;
}

//transposes the matrix
void Matrix::transpose()
{
  // create a temporary Matrix object to store the transposed matrix
  Matrix temp(_cols, _rows);

  //copy the data from original matrix into the temporary matrix,
  // transposing the rows and columns.
  for(int i=0; i<_rows; i++)
  {
    for(int j=0; j<_cols; j++)
    {
      temp(j, i) = (*this)(i, j);
    }
  }
  // swap and copy the temporary matrix object into the current object
  *this = temp;

  //temp will be freed in the end of the scope
}

//transforms the matrix into a column vector
void Matrix::vectorize()
{
  //we can treat the matrix as a vector because it is a list, just need to
  // change the rows to the number of elements and change the columns to 1.
  _rows = _rows * _cols;
  _cols = 1;
}

//Prints matrix elements, no return value.
void Matrix::plain_print () const
{
  for(int i=0; i<_rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      std::cout << (*this)(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

//returns a new matrix which is the element-wise multiplication(Hadamard
// product) of this matrix and another matrix (rhs).
Matrix Matrix::dot(const Matrix& rhs) const
{
  Matrix result(_rows, _cols);

  for(int i=0; i<_rows*_cols; i++)
  {
    result[i] = (*this)[i] * rhs[i];
  }

  return result;
}

// returns the sum of the matrix.
float Matrix::sum() const
{
  float sum = 0;

  for(int i=0; i<_rows*_cols; i++)
  {
    sum += (*this)[i];
  }

  return sum;
}

// returns the frobenius norm of the given matrix
float Matrix::norm() const
{
  return ((float)std::sqrt(std::pow((*this).sum(), 2)));
}

//returns the brackets index of the largest number in the matrix.
int Matrix::argmax() const
{
  float max = 0;
  int index_of_max;

  for(int i=0; i<_rows*_cols; i++)
  {
    if(max <= (*this)[i])
    {
      max = (*this)[i];
      index_of_max = i;
    }
  }

  return index_of_max;

}