#ifndef L_GRAPHICSCOMPONENT__HPP
#define L_GRAPHICSCOMPONENT__HPP
//DESCRIPTION
/*
  Lua binding of the graphics component
 */

//CLASSES

//INCLUDES
#include "LuaScript.hpp"
#include "GraphicsComponent.hpp"
#include "l_Utils.hpp"
#include "l_Component.hpp"
#include "l_AbstractComponent.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
GraphicsComponent* lua_pushgraphicsComponent(
    lua_State*,
    GraphicsComponent*);
GraphicsComponent* lua_tographicsComponent(lua_State*, int);
boolType lua_isgraphicsComponent(lua_State*, int);

int luaopen_graphicsComponent(lua_State *L);

#endif //END L_GRAPHICSCOMPONENT__HPP
