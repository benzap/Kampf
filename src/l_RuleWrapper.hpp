#ifndef L_RULEWRAPPER__HPP
#define L_RULEWRAPPER__HPP
//DESCRIPTION
/*
  The rule wrapper is used to wrap lua functions to be used within the
  rulemachine.
 */

//CLASSES
class RuleWrapper_condition;
class RuleWrapper_function;

//INCLUDES
#include <functional>
#include "RuleMachine.hpp"
#include "LuaScript.hpp"
#include "l_Message.hpp"
#include "l_Wrapper_Utils.hpp"
#include "l_Wrapper.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class RuleWrapper_condition : public Lua_FunctionWrapper {
public:
    RuleWrapper_condition(lua_State *L, int index) :
	Lua_FunctionWrapper(L, index) {}
    
    boolType operator () (Message* msg);
};

class RuleWrapper_function : public Lua_FunctionWrapper {
public:
    RuleWrapper_function(lua_State *L, int index) :
	Lua_FunctionWrapper(L, index) {}

    void operator () (Message* msg);
};


#endif //END L_RULEWRAPPER__HPP
