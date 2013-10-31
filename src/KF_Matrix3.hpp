#ifndef KF_MATRIX3__HPP
#define KF_MATRIX3__HPP
//DESCRIPTION
/*
  Used to represent 3 by 3 matrices
 */

//CLASSES
class Matrix3;

//INCLUDES
#include <cmath>
#include <cassert>
#include <iostream>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_Vector.hpp"
#include "KF_Quaternion.hpp"

//DEFINITIONS
#define M3_LENGTH 9
#define M3_WIDTH 3

//MACROS

//TYPEDEFS

//FUNCTIONS

//gets an index to provide for a matrix.
//NOTE: this is one-indexed

//BEGIN
class Matrix3 {
private:

public:
  floatType data[9];
  const static int length = 9;
  const static int width = 3;
  Matrix3();
  virtual ~Matrix3();

  void fill(floatType);
  void identity(floatType);
  Vector row(integerType);
  Vector col(integerType);
  floatType det();
  floatType get(int i, int j);
  floatType& operator [](integerType i);
  boolType operator ==(const Matrix3& o);
  Matrix3 operator +(const Matrix3& o);
  Matrix3 operator -(const Matrix3& o);
  Matrix3 operator *(const Matrix3& o);
  Matrix3 operator *(const floatType f);

  Matrix3 operator %(const Matrix3 o);
  Vector operator %(const Vector& o);
  

};

#endif //END KF_MATRIX3__HPP
