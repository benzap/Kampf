#ifndef L_SDLASSETMANAGER__HPP
#define L_SDLASSETMANAGER__HPP
//DESCRIPTION
/*
  lua binding for the SDL asset manager, for loading assets to be used
  by the graphic components.
 */

//CLASSES

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "SDLAssetManager.hpp"
#include "LuaScript.hpp"
#include "l_SDLDrawable.hpp"

//DEFINITIONS
#define LUA_USERDATA_SDLASSETMANAGER "l_kf.sdlassetmanager"

//MACROS

//TYPEDEFS

//FUNCTIONS

void lua_pushSDL_AM(lua_State*, SDLAssetManager*);
SDLAssetManager* lua_toSDL_AM(lua_State*, int);
boolType lua_isSDL_AM(lua_State *L, int);

int luaopen_SDL_AM(lua_State *L);

//BEGIN


#endif //END L_SDLASSETMANAGER__HPP
