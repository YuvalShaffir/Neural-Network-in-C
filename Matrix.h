#include <iostream>
#include <fstream>

#ifndef MATRIX_H
#define MATRIX_H

class Matrix {

public:
  /**
   * @struct dims
   * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
   */
  Matrix(int rows, int cols);

  Matrix();

  Matrix(const Matrix& m);

  Matrix& operator=(Matrix rhs);

  ~Matrix()
  {
    delete[] _mat;
  }


  int get_rows() const;

  int get_cols() const;

  void transpose();

  void vectorize();

  void plain_print() const;

  Matrix dot(const Matrix& rhs) const;

  float sum() const;

  float norm() const;

  int argmax() const;

  float& operator()(int i,int j) const;

  float& operator()(int i,int j);

  float& operator[](int i) const;

  const Matrix& operator+=(const Matrix& rhs) const;

  Matrix operator+(const Matrix& rhs) const;

  Matrix operator*(const Matrix& rhs);

  friend Matrix operator*(Matrix& m, float& rhs);

  friend Matrix operator*(float& lhs, Matrix& m);

  friend std::ostream& operator<<(std::ostream& output, Matrix& m);

  friend std::istream& operator>>(std::istream& input, Matrix& m);

  struct dims {
    int rows, cols;
  };


private:
  float *_mat;
  int _rows;
  int _cols;
};

#endif // MATRIX_H
