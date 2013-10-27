#ifndef L_QUATERNION__HPP
#define L_QUATERNION__HPP
//DESCRIPTION
/*
  lua binding of KF_Quaternion
 */

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_Quaternion.hpp"
#include "LuaScript.hpp"


//CLASSES

//DEFINITIONS
#define LUA_USERDATA_QUATERNION "l_kf.quaternion"

//MACROS

//TYPEDEFS

//FUNCTIONS

Quaternion* lua_pushquaternion(lua_State*, Quaternion*);

Quaternion* lua_toquaternion(lua_State*, int);

int luaopen_quaternion(lua_State *L);

//BEGIN


#endif //END L_QUATERNION__HPP
