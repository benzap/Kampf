#ifndef L_ENTITY__HPP
#define L_ENTITY__HPP
//DESCRIPTION
/*
  Lua binding to the Entity type
 */

//CLASSES

//INCLUDES
#include "LuaScript.hpp"
#include "Entities.hpp"
#include "l_Utils.hpp"
#include "l_Component.hpp"

//DEFINITIONS
#define LUA_USERDATA_ENTITY "l_kf.entity"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
Entity* lua_pushentity(lua_State *L, Entity* entity);
Entity* lua_toentity(lua_State *L, int index);
boolType lua_isentity(lua_State *L, int index);

int luaopen_entity(lua_State *L);


#endif //END L_ENTITY__HPP
