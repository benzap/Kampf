#ifndef L_SDLTEXT__HPP
#define L_SDLTEXT__HPP
//DESCRIPTION
/*
  Lua wrapper for the SDLText type
 */

//CLASSES

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "SDLAssetManager.hpp"
#include "LuaScript.hpp"
#include "SDLFont.hpp"
#include "l_SDLFont.hpp"

//DEFINITIONS
#define LUA_USERDATA_SDLTEXT "l_kf.sdltext"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
void lua_push_sdltext(lua_State *L, SDLText*);
SDLText* lua_to_sdltext(lua_State *L, int index);
boolType lua_is_sdltext(lua_State *L, int index);

int luaopen_SDLText(lua_State *L);

#endif //END L_SDLTEXT__HPP
