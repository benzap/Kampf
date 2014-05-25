#ifndef L_PHYSICSREGISTRY__HPP
#define L_PHYSICSREGISTRY__HPP
//DESCRIPTION
/*
  Lua binding for the PhysicsRelation class
 */

//CLASSES

//INCLUDES

#if defined(KF_WIN)

#include "../KF_globals.hpp"
#include "../KF_utilities.hpp"
#include "../KF_math.hpp"
#include "../LuaScript.hpp"
#include "../l_Utils.hpp"

#else

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#include "LuaScript.hpp"
#include "l_Utils.hpp"

#endif

#include "PhysicsRegistry.hpp"

//DEFINITIONS
#define LUA_USERDATA_PHYSICSREGISTRY "l_kf.physics_registry"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
PhysicsRegistry* lua_pushphysicsregistry(lua_State *L);
PhysicsRegistry* lua_tophysicsregistry(lua_State *L, int index);
boolType lua_isphysicsregistry(lua_State *L, int index);

int luaopen_physicsregistry(lua_State *L);

#endif //END L_PHYSICSREGISTRY__HPP
