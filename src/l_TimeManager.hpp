#ifndef L_TIMEMANAGER__HPP
#define L_TIMEMANAGER__HPP
//DESCRIPTION
/*
  Lua binding for the time manager
 */

//CLASSES

//INCLUDES
#include "LuaScript.hpp"
#include "TimeManager.hpp"
#include "l_Utils.hpp"

//DEFINITIONS
#define LUA_USERDATA_TIMEMANAGER "l_kf.time_manager"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
TimeManager* lua_pushtimeManager(lua_State *L);
TimeManager* lua_totimeManager(lua_State *L, int index);
boolType lua_istimeManager(lua_State *L, int index);

int luaopen_timeManager(lua_State *L);

#endif //END L_TIMEMANAGER__HPP
