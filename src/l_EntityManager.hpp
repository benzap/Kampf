#ifndef L_ENTITYMANAGER__HPP
#define L_ENTITYMANAGER__HPP
//DESCRIPTION
/*
  Lua binding for the entity manager
 */

//CLASSES

//INCLUDES
#include "LuaScript.hpp"
#include "EntityManager.hpp"
#include "l_Utils.hpp"

//DEFINITIONS
#define LUA_USERDATA_ENTITYMANAGER "l_kf.entity_manager"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
EntityManager* lua_pushentityManager(lua_State *L);
EntityManager* lua_toentityManager(lua_State *L, int index);
boolType lua_isentityManager(lua_State *L, int index);

int luaopen_entityManager(lua_State *L);

#endif //END L_ENTITYMANAGER__HPP
