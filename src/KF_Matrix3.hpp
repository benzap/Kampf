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

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class Matrix3 {
private:

public:
  floatType data[9];

  Matrix3();
  virtual ~Matrix3();

  Matrix3 operator +(const Matrix3& o);

};

#endif //END KF_MATRIX3__HPP
