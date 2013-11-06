#ifndef L_MESSENGER__HPP
#define L_MESSENGER__HPP
//DESCRIPTION
/*
  Lua binding for messenger
 */

//CLASSES

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "LuaScript.hpp"
#include "kampf.hpp"
#include "Messenger.hpp"

//DEFINITIONS
#define LUA_REGISTRY_MESSENGER "l_kf.messenger"
#define LUA_USERDATA_MESSENGER "l_kf.messenger_ud"

//MACROS

//TYPEDEFS

//FUNCTIONS
void lua_registerMessenger(lua_State *L, Messenger* messenger);
boolType lua_hasMessenger(lua_State *L);
Messenger* lua_getMessenger(lua_State *L);

void lua_pushmessenger(lua_State *L);
boolType lua_ismessenger(lua_State *L, int index);
Messenger* lua_tomessenger(lua_State *L, int index);

int luaopen_messenger(lua_State *L, Messenger* messenger);

//BEGIN


#endif //END L_MESSENGER__HPP
