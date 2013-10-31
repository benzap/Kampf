#ifndef KF_VECTOR__HPP
#define KF_VECTOR__HPP
//DESCRIPTION
/*
  Vector class for physics and collision stuff
*/

//CLASSES
class Vector;

//INCLUDES
#include <cmath>
#include <cassert>
#include <iostream>
#include <initializer_list>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"

//DEFINITIONS
#define V_zero Vector(0,0,0)
#define V_i Vector(1,0,0)
#define V_j Vector(0,1,0)
#define V_k Vector(0,0,1)

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class Vector {
private:

public:
  floatType pad = 3;

  floatType x = 0;
  floatType y = 0;
  floatType z = 0;

  Vector(floatType x = 0, floatType y = 0, floatType z = 0) :
    x(x), y(y), z(z) {};
    
  integerType length() { return 3; }

  //vector addition
  Vector operator +(const Vector& o) {
    return Vector(this->x + o.x,
		  this->y + o.y,
		  this->z + o.z);
  };


  void operator +=(const Vector& o) {
    this->x += o.x;
    this->y += o.y;
    this->z += o.z;
  };
  
  //scalar addition
  Vector operator +(floatType f) {
    return Vector(this->x + f,
		  this->y + f,
		  this->z + f);
  };

  void operator +=(floatType f) {
    this->x += f;
    this->y += f;
    this->z += f;
  };
  
  //scalar product (dot product)
  floatType operator *(const Vector& o) {
    auto result = 0;
    result += this->x * o.x;
    result += this->y * o.y;
    result += this->z * o.z;

    return result;
  };

  //scalar multiplication
  Vector operator *(floatType f) {
    return Vector(this->x * f,
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
  };

  //equality
  bool operator ==(const Vector& o) {
    if (this->x == o.x &&
	this->y == o.y &&
	this->z == o.z) {
      return true;
    }
    return false;
  }

  //negation
  Vector operator - () {
    return Vector(-this->x, 
		  -this->y, 
		  -this->z);
  };

  //The component product of two vectors
  Vector comp_prod(const Vector& o) {
    return Vector(
		  this->x * o.x,
		  this->y * o.y,
		  this->z * o.z);
  };

  void comp_prod_update(const Vector& o) {
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
  Vector unit() {
    auto unitVector = *this;
    unitVector *= 1 / this->magnitude_real();
    return unitVector;
  };

  //printing to stream
  friend std::ostream& operator<<(std::ostream& os, Vector const & _this) {
    os << "vector(" << _this.x;
    os << ", " << _this.y;
    os << ", " << _this.z << ")";
    return os;
  };

  Vector cross(const Vector& o) {
    floatType i = this->y * o.z - this->z * o.y;
    floatType j = this->z * o.x - this->x * o.z;
    floatType k = this->x * o.y - this->y * o.x;
    return Vector(i, j, k);
  };

  Vector operator% (const Vector& o) {
    return this->cross(o);
  };

  void operator %=(const Vector& o) {
    floatType i = this->y * o.z - this->z * o.y;
    floatType j = this->z * o.x - this->x * o.z;
    floatType k = this->x * o.y - this->y * o.x;
    this->x = i;
    this->y = j;
    this->z = k;
  }

};

void makeOrthonormalBasis(Vector *a, Vector *b, Vector *c);


#endif //END KF_VECTOR__HPP
