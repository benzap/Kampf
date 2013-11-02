#include "KF_Matrix3.hpp"

Matrix3::Matrix3() {
  for (int i = 0; i < this->length; i++) {
    this->data[i] = 0;
  }
}

Matrix3::Matrix3(std::initializer_list<floatType> l) {
  assert(l.size() <= this->length);
  int i = 0;
  for (auto value : l) {
    this->data[i++] = value;
  }
  for (; i < this->length; i++) {
    this->data[i] = 0;
  }
}

Matrix3::~Matrix3() {}

void Matrix3::fill(floatType f = 0) {
  for (int i = 0; i < this->length; i++) {
    this->data[i] = f;
  }
}

void Matrix3::identity(floatType f = 1) {
  this->fill(0);
  for (int i = 0; i < this->width; i++) {
    this->data[i*this->width + i] = f;
  }
}

Vector Matrix3::row(integerType rowIndex) {
  assert(rowIndex < this->width);
  auto result = Vector();
  for (int i = 0; i < this->width; i++) {
    result[i] = this->get(rowIndex, i);
  }
  return result;
}

Vector Matrix3::col(integerType colIndex) {
  assert(colIndex < this->width);
  auto result = Vector();
  for (int i = 0; i < this->width; i++) {
    result[i] = this->get(i, colIndex);
  }
  return result;
}

/*
  00 01 02
  10 11 12
  20 21 22
  
  00 *
  11 * 22 - 12 * 21
  01 *
  12 * 20 - 10 * 22
  02 *
  10 * 21 - 11 * 20
 */

floatType Matrix3::det() {
  floatType result = 0;
  result += this->get(0,0) * (this->get(1,1) * this->get(2,2) -
			      this->get(1,2) * this->get(2,1));

  result += this->get(0,1) * (this->get(1,2) * this->get(2,0) -
			      this->get(1,0) * this->get(2,2));
  
  result += this->get(0,2) * (this->get(1,0) * this->get(2,1) -
			      this->get(1,1) * this->get(2,0));
  return result;
}

floatType Matrix3::get(int i, int j) {
  return this->data[_I(i,j)];
}

void Matrix3::set(int i, int j, floatType val) {
  assert(i < this->width && j < this->width);
  this->data[_I(i,j)] = val;
}

void Matrix3::set(std::initializer_list<floatType> l) {
  int index = 0;
  for (auto value : l) {
    this->data[index++] = value;
  }
}

floatType& Matrix3::operator [](integerType i) {
  assert(i < this->length);
  return this->data[i];
}

boolType Matrix3::operator ==(const Matrix3& o) {
  for (integerType i = 0; i < this->length; i++) {
    if (this->data[i] != o.data[i]) {
      return false;
    }
  }
  return true;
}

Matrix3 Matrix3::operator +(const Matrix3& o) {
  auto result = Matrix3();
  for (int i = 0; i < this->length; i++) {
    result.data[i] = this->data[i] + o.data[i];
  }
  return result;
}

void Matrix3::operator +=(const Matrix3& o) {
  for (int i = 0; i < this->length; i++) {
    this->data[i] = o.data[i];
  }
}

Matrix3 Matrix3::operator -(const Matrix3& o) {
  auto result = Matrix3();
  for (int i = 0; i < this->length; i++) {
    result.data[i] = this->data[i] - o.data[i];
  }
  return result;
}

Matrix3 Matrix3::operator -() {
  for (int i = 0; i < this->length; i++) {
    this->data[i] = -(this->data[i]);
  } //END for (int i = 0; i < this->length; i++) {
}

void Matrix3::operator -=(const Matrix3& o) {
  for (int i = 0; i < length; i++) {
    this->data[i] -= o.data[i];
  } //END for (int i = 0; i < length; i++) {
}

Matrix3 Matrix3::operator *(const Matrix3& o) {
  auto result = Matrix3();
  for (int i = 0; i < this->length; i++) {
    result.data[i] = this->data[i] * o.data[i];
  }
  return result;
}

void Matrix3::operator *= (const Matrix3& o) {
  for (int i = 0; i < this->length; i++) {
    this->data[i] *= o.data[i];
  } //END for (int i = 0; i < this->length; i++) {
}

Matrix3 Matrix3::operator *(const floatType f) {
  auto result = Matrix3();
  for (int i = 0; i < this->length; i++) {
    result.data[i] = this->data[i] * f;
  }
  return result;
}

void Matrix3::operator *= (const floatType f) {
  for (int i = 0; i < this->length; i++) {
    this->data[i] *= f;
  } //END for (int i = 0; i < this->length; i++) {
}

Matrix3 Matrix3::operator %(Matrix3& o) {
  auto result = Matrix3();
  for (int i = 0; i < this->width; i++) {
    for (int j = 0; j < this->width; j++) {
      result.data[_I(i,j)] = this->row(i) * o.col(j);
    }
  }
  return result;
}

void Matrix3::operator %=(Matrix3& o) {
  auto result = Matrix3();
  for (int i = 0; i < this->width; i++) {
    for (int j = 0; j < this->width; j++) {
      result.data[_I(i,j)] = this->row(i) * o.col(j);
    }
  }
  *this = result;
}

Vector Matrix3::operator %(Vector& o) {
  
}



//printing out vectors
std::ostream& operator << (std::ostream& os,
			   Matrix3 const & _this) {
  os << "Mat3[" << std::endl;
  os << _this.data[0] << ", ";
  os << _this.data[1] << ", ";
  os << _this.data[2] << ",";
  os << std::endl;
  os << _this.data[3] << ", ";
  os << _this.data[4] << ", ";
  os << _this.data[5] << ",";
  os << std::endl;
  os << _this.data[6] << ", ";
  os << _this.data[7] << ", ";
  os << _this.data[8] << ",";
  os << std::endl;
  os << "]";

  return os;
}
