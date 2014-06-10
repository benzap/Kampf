#ifndef L_SDLFONT__HPP
#define L_SDLFONT__HPP
//DESCRIPTION
/*
  LuaBinding for the SDLFont type
 */

//CLASSES

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "LuaScript.hpp"

//DEFINITIONS
#define LUA_USERDATA_SDLFONT "l_kf.sdlfont"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
void lua_push_sdlfont(lua_State *L, SDLFont*);
SDLFont* lua_to_sdlfont(lua_State *L, int index);
boolType lua_is_sdlfont(lua_State *L, int index);

int luaopen_SDLFont(lua_State *L);

#endif //END L_SDLFONT__HPP
