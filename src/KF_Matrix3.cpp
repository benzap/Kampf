#include "KF_Matrix3.hpp"

Matrix3::Matrix3() {
  for (int i = 0; i < this->length; i++) {
    this->data[i] = 0;
  }
}

Matrix3::~Matrix3() {}

void Matrix3::fill(floatType f) {
  for (int i = 0; i < this->length; i++) {
    this->data[i] = f;
  }
}

void Matrix3::identity(floatType f) {
  this->fill(0);
  for (int i = 0; i < this->width; i++) {
    this->data[i*this->width] = f;
  }
}

Vector Matrix3::row(integerType rowIndex) {
  assert(rowIndex < this->width);
  auto result = Vector();
  for (int i = rowIndex*this->width; i < rowIndex*this->width + this->width; i++) {
    result[i] = this->data[i];
  }
  return result;
}

Vector Matrix3::col(integerType colIndex) {
  assert(colIndex < this->width);
  auto result = Vector();
  for (int i = 0; i < this->width; i++) {
    result[i] = this->data[i*this->width+colIndex];
  }
}

floatType Matrix3::det() {
  floatType result;
  result += this->get(1,1) * this->get(2,2);
  result -= this->get(1,2) * this->get(2,1);

  result -= this->get(1,0) * this->get(2,2);
  result += this->get(2,0) * this->get(1,2);

  result += this->get(1,0) * this->get(2,1);
  result -= this->get(1,2) * this->get(2,0);
  
  return result;
}

floatType Matrix3::get(int i, int j) {
  return i + Matrix3::width * j;
}

floatType& Matrix3::operator [](integerType i) {
  assert(i < this->length);
  return this->data[i];
}

boolType Matrix3::operator ==(const Matrix3& o) {
  for (integerType i; i < this->length; i++) {
    if (this->data[i] != o.data[i]) {
      return false;
    }
  }
  return true;
}

Matrix3 Matrix3::operator +(const Matrix3& o) {
  auto result = Matrix3();
  for (int i = 0; i < this->length; i++) {
    result.data[i] = this->data[i] + o.data[0];
  }
  return result;
}

Matrix3 Matrix3::operator -(const Matrix3& o) {
  
}

Matrix3 Matrix3::operator *(const Matrix3& o) {

}

Matrix3 Matrix3::operator *(const floatType f) {

}


Matrix3 Matrix3::operator %(const Matrix3 o) {

}

Vector Matrix3::operator %(const Vector& o) {

}
