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
#include "l_AbstractComponent.hpp"
#include "l_CollisionComponent.hpp"

//DEFINITIONS
#define LUA_USERDATA_ABSTRACTCOMPONENT "l_kf.abstract_component"
#define LUA_USERDATA_COLLISIONCOMPONENT "l_kf.collision_component"



//MACROS

//TYPEDEFS

//FUNCTIONS


//BEGIN

Component* lua_pushcomponent(lua_State *L, Component* component);
Component* lua_tocomponent(lua_State *L, int index);
boolType lua_iscomponent(lua_State *L, int index);

boolType lua_isUserdata(lua_State *L, int index, const char *tname);

int luaopen_component(lua_State *L);

#endif //END L_COMPONENT__HPP
