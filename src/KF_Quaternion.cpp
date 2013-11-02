#include "KF_Quaternion.hpp"

Quaternion::Quaternion(floatType w,
		       floatType i, 
                       floatType j,
                       floatType k) : 
                       v(Vector3(i,j,k)),
                       w(w) {

};

Quaternion Quaternion::operator +(const Quaternion& o) {
  Quaternion q;
  q.w = this->w + o.w;
  q.v = this->v + o.v;
  return q;
}

void Quaternion::operator +=(const Quaternion& o) {
  this->w += o.w;
  this->v += o.v;
}


Quaternion Quaternion::operator +(const Vector3& o) {
  Quaternion q;
  q.w = this->w;
  q.v = this->v + o;
  return q;
}


floatType Quaternion::operator *(const Quaternion& o) {
  floatType result = this->w * o.w;
  result += this->v * o.v;
  return result;
}

floatType Quaternion::operator *(const Vector3& o) {
  Quaternion q = *this;
  
  return q.v * o;
}

Quaternion Quaternion::operator *(floatType f) {
  Quaternion q;
  q.w = this->w * f;
  q.v = this->v * f;
  return q;
}

void Quaternion::operator *=(floatType f) {
  this->w = this->w * f;
  this->v = this->v * f;
}


floatType& Quaternion::operator [] (integerType i) {
  assert(i <= 3);
  switch(i) {
  case 0:
    return this->w;
    
  case 1:
    return this->v.x;
    
  case 2:
    return this->v.y;
    
  case 3:
    return this->v.z;
  }
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
  q.w = this->w;
  q.v = -this->v;
  return q;
}

Quaternion Quaternion::inv() {
  Quaternion q = *this;
  return q.conj() * (1 / q.magnitude());
}

Quaternion Quaternion::operator - () {
  Quaternion q;
  q.w = -this->w;
  q.v = -this->v;
  return q;
}


floatType Quaternion::magnitude_real() {
  return sqrt(this->w * this->w + fabs(this->v * this->v));
}

floatType Quaternion::magnitude() {
  return this->w * this->w + fabs(this->v * this->v);
}

Quaternion Quaternion::unit() {
  Quaternion q = *this;
  q *= 1 / q.magnitude_real();
  return q;
}


//printing out vectors
std::ostream& operator << (std::ostream& os,
                           Quaternion const & _this) {
  os << "quat(" << _this.w;
  os << ", " << _this.v.x;
  os << ", " << _this.v.y;
  os << ", " << _this.v.z;
  os << ")";
  return os;
}

Quaternion Quaternion::product(const Quaternion& o) {
  Quaternion q;
  q.w = (this->w * o.w) - (this->v * o.v);

  q.v = o.v;
  q.v *= this->w;

  q.v += this->v * o.w;
  q.v += this->v % o.v;
  return q;
}


Quaternion Quaternion::operator % (const Quaternion& o) {
  Quaternion q = *this;
  return q.product(o);
}

void Quaternion::operator %= (const Quaternion& o) {
  *this = this->product(o);
}
