#ifndef KF_QUATERNION__HPP
#define KF_QUATERNION__HPP
//DESCRIPTION
/*
  Quaternions are used for determining the orientation of an object.
 */

//INCLUDES
#include <cmath>
#include <cassert>
#include <iostream>
#include <initializer_list>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_Vector.hpp"

//CLASSES
class Quaternion;

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class Quaternion {
private:

public:
Vector v;
floatType w;

Quaternion(floatType i = 0,
           floatType j = 0,
           floatType k = 0,
           floatType w = 0);

Quaternion operator +(const Quaternion& o);
void operator +=(const Quaternion& o);

Quaternion operator+(const Vector& o);

Quaternion operator *(const Quaternion& o);
void operator *=(const Quaternion& o);

Quaternion operator *(const Vector& o);
Quaternion operator *(floatType f);

floatType& operator [] (integerType i);

//conditionals
//equality
bool operator ==(const Quaternion& o);


//the conjugate
Quaternion conj();

Quaternion operator - ();

floatType magnitude_real();
floatType magnitude();
floatType unit();

//printing out vectors
friend std::ostream& operator << (std::ostream& os,
				    Quaternion const & _this);

Quaternion product(const Quaternion& o);

Quaternion operator % (const Quaternion& o);
void operator %= (const Quaternion& o);

};
#endif //END KF_QUATERNION__HPP
