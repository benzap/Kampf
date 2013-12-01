#ifndef L_CUSTOMATTRIBUTE__HPP
#define L_CUSTOMATTRIBUTE__HPP
//DESCRIPTION
/*
  A lua wrapper for the custom attribute type. This binding tries to
  provide facilities for dealing with the custom attributes stored
  within some of the classes.
 */

//CLASSES

//INCLUDES
#include "LuaScript.hpp"
#include "CustomAttribute.hpp"

//DEFINITIONS

//MACROS
#define LUA_USERDATA_CUSTOMATTRIBUTE "l.kf_customAttribute"

//TYPEDEFS

//FUNCTIONS

//BEGIN
CustomAttribute* lua_pushcustomAttribute(lua_State *L, CustomAttribute* customAttribute = nullptr);
CustomAttribute* lua_tocustomAttribute(lua_State *L, int index);
boolType lua_iscustomAttribute(lua_State *L, int index);

int luaopen_customAttribute(lua_State *L);

#endif //END L_CUSTOMATTRIBUTE__HPP
