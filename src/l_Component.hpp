#ifndef L_COMPONENT__HPP
#define L_COMPONENT__HPP
//DESCRIPTION
/*
  Lua binding to the Component type
 */

//CLASSES

//INCLUDES
#include "LuaScript.hpp"
#include "Components.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS


//BEGIN

Component* lua_pushcomponent(lua_State *L, Component* component);
Component* lua_tocomponent(lua_State *L, int index);
boolType lua_iscomponent(lua_State *L, int index);

int luaopen_component(lua_State *L);



#endif //END L_COMPONENT__HPP
