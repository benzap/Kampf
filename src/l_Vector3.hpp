#ifndef L_VECTOR__HPP
#define L_VECTOR__HPP
//DESCRIPTION
/*
  lua binding of KF_Vector3
 */

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_Vector3.hpp"
#include "LuaScript.hpp"

//CLASSES

//DEFINITIONS
#define LUA_USERDATA_VECTOR "l_kf.vector"

//MACROS

//TYPEDEFS

//FUNCTIONS

Vector3* lua_pushvector(lua_State*, Vector3*);

Vector3* lua_tovector(lua_State*, int);

int luaopen_vector (lua_State *L);
//BEGIN


#endif //END L_VECTOR__HPP
