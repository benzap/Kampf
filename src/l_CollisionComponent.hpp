#ifndef L_COLLISIONCOMPONENT__HPP
#define L_COLLISIONCOMPONENT__HPP
//DESCRIPTION
/*
  Lua binding of the collision component
 */

//CLASSES

//INCLUDES
#include "LuaScript.hpp"
#include "CollisionComponent.hpp"
#include "l_Utils.hpp"
#include "l_Component.hpp"
#include "l_AbstractComponent.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS
CollisionComponent* lua_pushcollisionComponent(
    lua_State*,
    CollisionComponent*);
CollisionComponent* lua_tocollisionComponent(lua_State*, int);
boolType lua_iscollisionComponent(lua_State*, int);

int luaopen_collisionComponent(lua_State *L);

//BEGIN


#endif //END L_COLLISIONCOMPONENT__HPP
