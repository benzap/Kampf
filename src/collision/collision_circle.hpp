#ifndef COLLISION_CIRCLE__HPP
#define COLLISION_CIRCLE__HPP
//DESCRIPTION
/*
  This file includes functions for dealing with the generation of
  circles bounds based on a given polygon.
 */

//CLASSES

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS
typedef struct COL_circle_struct {
    Vector3 center;
    floatType radius;
} COL_circle;


//FUNCTIONS
boolType check_circle_circle(COL_circle, COL_circle);

//BEGIN


#endif //END COLLISION_CIRCLE__HPP
