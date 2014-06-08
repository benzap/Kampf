#ifndef L_ABSTRACTFORCEGENERATOR__HPP
#define L_ABSTRACTFORCEGENERATOR__HPP
//DESCRIPTION
/*
  This is a general wrapper, so we can also grab force generators that
  have been developed in c++.
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

#include "AbstractForceGenerator.hpp"

//DEFINITIONS
#define LUA_USERDATA_ABSTRACTFORCEGENERATOR "l_kf.AbstractForceGenerator"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
AbstractForceGenerator* lua_pushAbstractForceGenerator(lua_State*, AbstractForceGenerator*);
AbstractForceGenerator* lua_toAbstractForceGenerator(lua_State*, int);
boolType lua_isAbstractForceGenerator(lua_State*, int);

int luaopen_AbstractForceGenerator(lua_State *L);

#endif //END L_ABSTRACTFORCEGENERATOR__HPP
