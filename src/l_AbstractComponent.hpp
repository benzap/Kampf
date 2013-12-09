#ifndef L_ABSTRACTCOMPONENT__HPP
#define L_ABSTRACTCOMPONENT__HPP
//DESCRIPTION
/*
  This is the lua binding for the AbstractComponent class
 */

//CLASSES

//INCLUDES
#include "LuaScript.hpp"
#include "AbstractComponent.hpp"
#include "l_CustomAttribute.hpp"

//DEFINITIONS
#define LUA_USERDATA_ABSTRACTCOMPONENT "l_kf.abstract_component"

//MACROS

//TYPEDEFS

//FUNCTIONS
AbstractComponent* lua_pushabstractComponent(
    lua_State*,
    AbstractComponent*);
AbstractComponent* lua_toabstractComponent(lua_State*, int);
boolType lua_isabstractComponent(lua_State*, int);

int luaopen_abstractComponent(lua_State *L);

//BEGIN


#endif //END L_ABSTRACTCOMPONENT__HPP
