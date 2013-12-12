#ifndef L_PHYSICSCOMPONENT__HPP
#define L_PHYSICSCOMPONENT__HPP
//DESCRIPTION
/*
  Lua binding of the physics component
 */

//CLASSES

//INCLUDES
#include "LuaScript.hpp"
#include "PhysicsComponent.hpp"
#include "l_Utils.hpp"
#include "l_Component.hpp"
#include "l_AbstractComponent.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS
PhysicsComponent* lua_pushphysicsComponent(
    lua_State*,
    PhysicsComponent*);
PhysicsComponent* lua_tophysicscomponent(lua_State*, int);
boolType lua_isphysicsComponent(lua_State*, int);

int luaopen_physicsComponent(lua_State *L);

//BEGIN


#endif //END L_PHYSICSCOMPONENT__HPP
