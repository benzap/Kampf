#include "KF_Quaternion.hpp"

Quaternion::Quaternion(floatType i, 
                       floatType j,
                       floatType k,
                       floatType w) : 
                       v(Vector(i,j,k)),
                       w(w) {

};

Quaternion Quaternion::operator +(const Quaternion& o) {
  Quaternion q;
  q.v += o.v;
  q.w += o.w;
  return q;
}

void Quaternion::operator +=(const Quaternion& o) {
  
}


Quaternion Quaternion::operator+(const Vector& o) {
  Quaternion q;

  return q;
}


Quaternion Quaternion::operator *(const Quaternion& o) {
  Quaternion q;

  return q;
}

void Quaternion::operator *=(const Quaternion& o) {

}


Quaternion Quaternion::operator *(const Vector& o) {
  Quaternion q;

  return q;
}

Quaternion Quaternion::operator *(floatType f) {
  Quaternion q;

  return q;
}


floatType& Quaternion::operator [] (integerType i) {

}

//conditionals
//equality
bool Quaternion::operator ==(const Quaternion& o) {
  if (this->v == o.v &&
      this->w == o.w) {
    return true;
  }
  return false;
}

//the conjugate
Quaternion Quaternion::conj() {
  Quaternion q;

  return q;
}


Quaternion Quaternion::operator - () {
  Quaternion q;

  return q;
}


floatType Quaternion::magnitude_real() {
  return 0;
}

floatType Quaternion::magnitude() {
  return 0;
}

floatType Quaternion::unit() {
  return 0;
}


//printing out vectors
std::ostream& operator << (std::ostream& os,
                           Quaternion const & _this) {

}

Quaternion Quaternion::product(const Quaternion& o) {
  Quaternion q;

  return q;
}


Quaternion Quaternion::operator % (const Quaternion& o) {
  Quaternion q;

  return q;
}

void Quaternion::operator %= (const Quaternion& o) {

}
