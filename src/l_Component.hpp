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
#include "l_Utils.hpp"
#include "l_AbstractComponent.hpp"
#include "l_CollisionComponent.hpp"
#include "l_PhysicsComponent.hpp"

//DEFINITIONS
#define LUA_USERDATA_ABSTRACTCOMPONENT "l_kf.abstract_component"
#define LUA_USERDATA_COLLISIONCOMPONENT "l_kf.collision_component"
#define LUA_USERDATA_PHYSICSCOMPONENT "l_kf.physics_component"
#define LUA_USERDATA_GRAPHICSCOMPONENT "l_kf.graphics_component"

//MACROS

//TYPEDEFS

//FUNCTIONS


//BEGIN

Component* lua_pushcomponent(lua_State *L, Component* component);
Component* lua_tocomponent(lua_State *L, int index);
boolType lua_iscomponent(lua_State *L, int index);

int luaopen_component(lua_State *L);

#endif //END L_COMPONENT__HPP
