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
#include "l_Utils.hpp"

//DEFINITIONS

//defines the area within the LUAREGISTRY where the rulemachine
//lightuserdata will be stored
#define LUA_REGISTRY_RULEMACHINE "l_kf.rulemachine"
//defines the metadata name for the rulemachine
#define LUA_USERDATA_RULEMACHINE "l_kf.rulemachine_ud"

//MACROS

//TYPEDEFS

//FUNCTIONS

//places the rulemachine within the lua registry
void lua_registerRuleMachine(lua_State *L, RuleMachine* rulemachine);
//checks if the registry has a copy of the rulemachine
boolType lua_hasRuleMachine(lua_State *L);
//gets the rulemachine from the registry
RuleMachine* lua_getRuleMachine(lua_State *L);

//pushes a RuleMachine userdata onto the lua stack
void lua_pushrulemachine(lua_State *L);
//function to check at the given index, if it's a rulemachine userdata
boolType lua_isrulemachine(lua_State *L, int index);
//returns the rulemachine from the given index on the lua stack
RuleMachine* lua_torulemachine(lua_State *L, int index);

//register function
int luaopen_rulemachine(lua_State *L, RuleMachine* rulemachine);

//BEGIN


#endif //END L_RULEMACHINE__HPP
