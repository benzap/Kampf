#ifndef L_RULEMACHINE__HPP
#define L_RULEMACHINE__HPP
//DESCRIPTION
/*
  Lua binding for the RuleMachine class instance
 */

//CLASSES

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "LuaScript.hpp"
#include "kampf.hpp"
#include "RuleMachine.hpp"
#include "l_RuleWrapper.hpp"

//DEFINITIONS
#define LUA_REGISTRY_RULEMACHINE "l_kf.rulemachine"
#define LUA_USERDATA_RULEMACHINE "l_kf.rulemachine_ud"

//MACROS

//TYPEDEFS

//FUNCTIONS

void lua_registerRuleMachine(lua_State *L, RuleMachine* rulemachine);
boolType lua_hasRuleMachine(lua_State *L);
RuleMachine* lua_getRuleMachine(lua_State *L);

void lua_pushrulemachine(lua_State *L);
boolType lua_isrulemachine(lua_State *L, int index);
RuleMachine* lua_torulemachine(lua_State *L, int index);

int luaopen_rulemachine(lua_State *L, RuleMachine* rulemachine);

//BEGIN


#endif //END L_RULEMACHINE__HPP
