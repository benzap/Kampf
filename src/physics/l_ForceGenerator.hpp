#ifndef L_FORCEGENERATOR__HPP
#define L_FORCEGENERATOR__HPP
//DESCRIPTION
/*
  This is the lua binding for force generators made within lua, and
  bridges the gap between LuaForceGenerator, which wraps a lua
  function, and the internal physics registry.
 */

//CLASSES

//INCLUDES

#if defined(KF_WIN)

#include "../KF_globals.hpp"
#include "../KF_utilities.hpp"
#include "../KF_math.hpp"
#include "../LuaScript.hpp"
#include "../l_Utils.hpp"
#include "../l_CollisionComponent.hpp"

#else

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#include "LuaScript.hpp"
#include "l_Utils.hpp"
#include "l_CollisionComponent.hpp"

#endif

#include "LuaForceGenerator.hpp"

//DEFINITIONS
#define LUA_USERDATA_LUAFORCEGENERATOR "l_kf.luaforcegenerator"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
LuaForceGenerator* lua_pushluaforcegenerator(lua_State*, LuaForceGenerator*);
LuaForceGenerator* lua_toluaforcegenerator(lua_State*, int);
boolType lua_isluaforcegenerator(lua_State*, int);

int luaopen_luaforcegenerator(lua_State *L);

#endif //END L_FORCEGENERATOR__HPP
