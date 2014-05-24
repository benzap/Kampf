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

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class RuleWrapper_condition {
private:
    lua_State *L = nullptr;
    int luaConditionRef = LUA_NOREF;
public:
    RuleWrapper_condition(lua_State *L, int index);
    virtual ~RuleWrapper_condition();

    boolType operator () (Message* msg);

};

class RuleWrapper_function {
private:
    lua_State *L = nullptr;
    int luaFunctionRef = LUA_NOREF;
public:
    RuleWrapper_function(lua_State *L, int index);
    virtual ~RuleWrapper_function();

    void operator () (Message* msg);
};


#endif //END L_RULEWRAPPER__HPP
