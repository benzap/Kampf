#ifndef L_SDLFONTMANAGER__HPP
#define L_SDLFONTMANAGER__HPP
//DESCRIPTION
/*
  Lua binding for the SDLFontManager
 */

//CLASSES

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "SDLFontManager.hpp"
#include "LuaScript.hpp"
//#include "l_SDLFont.hpp"

//DEFINITIONS
#define LUA_USERDATA_SDLFONTMANAGER "l_kf.sdlfontmanager"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
void lua_pushSDL_FM(lua_State*, SDLFontManager*);
SDLFontManager* lua_toSDL_FM(lua_State*, int);
boolType lua_isSDL_FM(lua_State *L, int);

int luaopen_SDL_FM(lua_State *L);


#endif //END L_SDLFONTMANAGER__HPP
