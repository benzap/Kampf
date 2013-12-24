#ifndef L_RENDERWINDOW__HPP
#define L_RENDERWINDOW__HPP
//DESCRIPTION
/*
  lua binding to the render window
 */

//CLASSES

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "LuaScript.hpp"
#include "kampf.hpp"
#include "AbstractRenderWindow.hpp"
#include "l_Utils.hpp"

//DEFINITIONS
#define LUA_REGISTRY_RENDERWINDOW "l_kf.renderWindow"
#define LUA_USERDATA_RENDERWINDOW "l_kf.renderWindow_ud"

//MACROS

//TYPEDEFS

//FUNCTIONS

//places the renderwindow within the lua registry
void lua_registerRenderWindow(lua_State *L, RenderWindow* renderwindow);
//checks if the registry has a copy of the renderwindow
boolType lua_hasRenderWindow(lua_State *L);
//gets the renderwindow from the registry
RenderWindow* lua_getRenderWindow(lua_State *L);

//pushes a RenderWindow userdata onto the lua stack
void lua_pushrenderwindow(lua_State *L);
//function to check at the given index, if it's a renderwindow userdata
boolType lua_isrenderwindow(lua_State *L, int index);
//returns the renderwindow from the given index on the lua stack
RenderWindow* lua_torenderwindow(lua_State *L, int index);

//register function
int luaopen_renderwindow(lua_State *L, RenderWindow* renderwindow);

//BEGIN


#endif //END L_RENDERWINDOW__HPP
