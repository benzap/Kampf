#ifndef KF_VECTOR__HPP
#define KF_VECTOR__HPP
//DESCRIPTION
/*
  Vector3 class for physics and collision stuff
*/

//CLASSES
class Vector3;

//INCLUDES
#include <cmath>
#include <cassert>
#include <iostream>
#include <initializer_list>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"

//DEFINITIONS
#define V_zero Vector3(0,0,0)
#define V_i Vector3(1,0,0)
#define V_j Vector3(0,1,0)
#define V_k Vector3(0,0,1)

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class Vector3 {
private:

public:
  floatType pad = 3;

  floatType x = 0;
  floatType y = 0;
  floatType z = 0;

  Vector3(floatType x = 0, floatType y = 0, floatType z = 0) :
    x(x), y(y), z(z) {};
    
  integerType length() { return 3; }

  //vector addition
  Vector3 operator +(const Vector3& o) {
    return Vector3(this->x + o.x,
		  this->y + o.y,
		  this->z + o.z);
  };


  void operator +=(const Vector3& o) {
    this->x += o.x;
    this->y += o.y;
    this->z += o.z;
  };
  
  //scalar addition
  Vector3 operator +(floatType f) {
    return Vector3(this->x + f,
		  this->y + f,
		  this->z + f);
  };

  void operator +=(floatType f) {
    this->x += f;
    this->y += f;
    this->z += f;
  };
  
  //scalar product (dot product)
  floatType operator *(const Vector3& o) {
    auto result = 0;
    result += this->x * o.x;
    result += this->y * o.y;
    result += this->z * o.z;

    return result;
  };

  //scalar multiplication
  Vector3 operator *(floatType f) {
    return Vector3(this->x * f,
		  this->y * f,
		  this->z * f);
  };

  //scalar products;
  void operator *=(floatType f) {
    this->x *= f;
    this->y *= f;
    this->z *= f;
  };

  // for the first 3 types, return x, y, z
  floatType& operator [] (integerType i) {
    assert(i <= 2);
    switch(i) {
    case 0:
      return this->x;
    case 1:
      return this->y;
    case 2:
      return this->z;
    }
    //TODO: fix this
    return this->x;
  };

  //equality
  bool operator ==(const Vector3& o) {
    if (this->x == o.x &&
	this->y == o.y &&
	this->z == o.z) {
      return true;
    }
    return false;
  }

  //negation
  Vector3 operator - () {
    return Vector3(-this->x, 
		  -this->y, 
		  -this->z);
  };

  //The component product of two vectors
  Vector3 comp_prod(const Vector3& o) {
    return Vector3(
		  this->x * o.x,
		  this->y * o.y,
		  this->z * o.z);
  };

  void comp_prod_update(const Vector3& o) {
    this->x *= o.x;
    this->y *= o.y;
    this->z *= o.z;
  };

  floatType magnitude_real() {
    floatType result = 0;
    result += this->x * this->x;
    result += this->y * this->y;
    result += this->z * this->z;
    return sqrt(result);
  };

  floatType magnitude() {
    floatType result = 0;
    result += this->x * this->x;
    result += this->y * this->y;
    result += this->z * this->z;
    return result;
  };

  //unit vector
  Vector3 unit() {
    auto unitVector3 = *this;
    unitVector3 *= 1 / this->magnitude_real();
    return unitVector3;
  };

  //printing to stream
  friend std::ostream& operator<<(std::ostream& os, Vector3 const & _this) {
    os << "vector(" << _this.x;
    os << ", " << _this.y;
    os << ", " << _this.z << ")";
    return os;
  };

  Vector3 cross(const Vector3& o) {
    floatType i = this->y * o.z - this->z * o.y;
    floatType j = this->z * o.x - this->x * o.z;
    floatType k = this->x * o.y - this->y * o.x;
    return Vector3(i, j, k);
  };

  Vector3 operator% (const Vector3& o) {
    return this->cross(o);
  };

  void operator %=(const Vector3& o) {
    floatType i = this->y * o.z - this->z * o.y;
    floatType j = this->z * o.x - this->x * o.z;
    floatType k = this->x * o.y - this->y * o.x;
    this->x = i;
    this->y = j;
    this->z = k;
  }

};

void makeOrthonormalBasis(Vector3 *a, Vector3 *b, Vector3 *c);


#endif //END KF_VECTOR__HPP
