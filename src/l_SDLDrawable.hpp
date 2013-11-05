#ifndef L_SDLDRAWABLE__HPP
#define L_SDLDRAWABLE__HPP
//DESCRIPTION
/*
  lua binding for SDLDrawable. The drawable can be called standalone
  to draw on to the current renderable surface
 */

//CLASSES

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "SDLAssetManager.hpp"
#include "LuaScript.hpp"

//DEFINITIONS
#define LUA_USERDATA_SDLDRAWABLE "l_kf.sdldrawable"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
void lua_push_sdldrawable(lua_State *L, SDLDrawable*);
SDLDrawable* lua_to_sdldrawable(lua_State *L, int index);
boolType lua_is_sdldrawable(lua_State *L, int index);

int luaopen_SDLDrawable(lua_State *L);

#endif //END L_SDLDRAWABLE__HPP
