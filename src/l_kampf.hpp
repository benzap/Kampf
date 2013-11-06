#ifndef L_KAMPF__HPP
#define L_KAMPF__HPP
//DESCRIPTION
/*
  Lua wrapper for the entry to kampf engine
 */

//CLASSES

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "LuaScript.hpp"
#include "kampf.hpp"

//DEFINITIONS
#define LUA_REGISTRY_KAMPF "l_kf.kampf"

//MACROS

//TYPEDEFS

//FUNCTIONS
void lua_registerKampf(lua_State* L, Kampf*);
boolType lua_hasKampf(lua_State* L);
Kampf* lua_getKampf(lua_State* L);
int luaopen_kampf(lua_State *L, Kampf*);

//BEGIN


#endif //END L_KAMPF__HPP
