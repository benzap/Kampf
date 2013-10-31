#include "KF_Matrix3.hpp"

Matrix3::Matrix3() {
  for (int i = 0; i < 9; i++) {
    this->data[i] = 0;
  }
}

Matrix3::~Matrix3() {}

Matrix3 Matrix3::operator +(const Matrix3& o) {
  auto result = Matrix3();
  for (int i = 0; i < 9; i++) {
    result.data[i] = this->data[i] + o.data[0];
  }
  return result;
}
