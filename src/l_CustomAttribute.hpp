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

static int l_CustomAttribute_gc(lua_State *L);
static int l_CustomAttribute_tostring(lua_State *L);
static int l_CustomAttribute_type(lua_State *L);
static int l_CustomAttribute_get(lua_State *L);
static int l_CustomAttribute_set(lua_State *L);
static int l_CustomAttribute_getInteger(lua_State *L);
static int l_CustomAttribute_setInteger(lua_State *L);
static int l_CustomAttribute_getFloat(lua_State *L);
static int l_CustomAttribute_setFloat(lua_State *L);
static int l_CustomAttribute_getChar(lua_State *L);
static int l_CustomAttribute_setChar(lua_State *L);
static int l_CustomAttribute_getArray(lua_State *L);
static int l_CustomAttribute_setArray(lua_State *L);
static int l_CustomAttribute_getString(lua_State *L);
static int l_CustomAttribute_setString(lua_State *L);

//BEGIN
CustomAttribute* lua_pushcustomAttribute(lua_State *L, CustomAttribute* customAttribute = nullptr);
CustomAttribute* lua_tocustomAttribute(lua_State *L, int index);
boolType lua_iscustomAttribute(lua_State *L, int index);

int luaopen_customAttribute(lua_State *L);

#endif //END L_CUSTOMATTRIBUTE__HPP
