#ifndef COLLISION_RECTANGLE__HPP
#define COLLISION_RECTANGLE__HPP
//DESCRIPTION
/*
  This file includes function for dealing with the generation of
  square bounds based on a given polygon
 */

//CLASSES

//INCLUDES
#if defined(KF_WIN)
#include "../KF_globals.hpp"
#include "../KF_utilities.hpp"
#include "../KF_math.hpp"
#else
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#endif

//DEFINITIONS

//MACROS

//TYPEDEFS
typedef struct COL_rect_struct {
    Vector3 min;
    Vector3 max;
} COL_rect;

//FUNCTIONS
boolType check_rect_rect(const COL_rect&, const COL_rect&);
Vector3 get_rect_rect_pt(const COL_rect&, const COL_rect&);


//BEGIN


#endif //END COLLISION_RECTANGLE__HPP
