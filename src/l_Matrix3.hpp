#ifndef L_MATRIX3__HPP
#define L_MATRIX3__HPP
//DESCRIPTION
/*
  Bin
 */

//CLASSES

//INCLUDES
#include "l_Vector.hpp"
#include "l_Quaternion.hpp"

//DEFINITIONS
#define LUA_USERDATA_MATRIX3 "l_kf.matrix3"

//MACROS

//TYPEDEFS

//FUNCTIONS

Matrix3 * lua_pushmatrix3(lua_State*, Matrix3*);

Matrix3 * lua_tomatrix3(lua_state*, int);

int luaopen_matrix3(lua_State *L);

//BEGIN


#endif //END L_MATRIX3__HPP
