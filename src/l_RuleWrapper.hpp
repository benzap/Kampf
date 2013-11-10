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

//DEFINITIONS
//location of the function references
#define FUNCTION_REF_TABLE "LUA_REGISTRYINDEX"

//MACROS

//TYPEDEFS

//FUNCTIONS

//pushes the value at the top of the stack into a table including
//references
int lua_getFunctionRef(lua_State *L);

//grabs the value at the given index / reference and pushes it to the
//top of the stack.
void lua_pushFunctionRef(lua_State *L, int ref);

//BEGIN
class RuleWrapper_condition {
private:
    lua_State *L = nullptr;
    int luaConditionRef = LUA_NOREF;
public:
    RuleWrapper_condition(lua_State *L, int index);
    virtual ~RuleWrapper_condition();

    boolType operator () (Message msg);

};

class RuleWrapper_function {
private:
    lua_State *L = nullptr;
    int luaFunctionRef = LUA_NOREF;
public:
    RuleWrapper_function(int index);
    virtual ~RuleWrapper_function();

    boolType operator () (Message msg);
};


#endif //END L_RULEWRAPPER__HPP
