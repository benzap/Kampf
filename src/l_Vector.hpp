#ifndef L_VECTOR__HPP
#define L_VECTOR__HPP
//DESCRIPTION
/*
  lua binding of KF_Vector
 */

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_Vector.hpp"
#include "LuaScript.hpp"

//CLASSES

//DEFINITIONS
#define LUA_USERDATA_VECTOR "l_kf.vector"

//MACROS

//TYPEDEFS

//FUNCTIONS

int luaopen_vector (lua_State *L);
//BEGIN


#endif //END L_VECTOR__HPP
