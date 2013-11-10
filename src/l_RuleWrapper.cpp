#include "l_RuleWrapper.hpp"

int lua_getFunctionRef(lua_State *L) {
    //pushes the top value on the stack and returns an integer
    //representing the reference to our pushed function.
    int reference = luaL_ref(L, FUNCTION_REF_TABLE);
    //TODO: error checking
    return reference;
}

void lua_pushFunctionRef(lua_State *L, int ref) {
    //push the value to the top of the stack
    //TODO: error checking
    lua_rawgeti(L, FUNCTION_REF_TABLE, ref);
}


RuleWrapper_condition::RuleWrapper_condition(lua_State *L, int index) :
    L(L) {
    //push the index to the top of the stack
    lua_pushvalue(L, index);
    //push and pop into reference;
    this->luaConditionRef = lua_getFunctionRef(L);
}

RuleWrapper_condition::~RuleWrapper_condition() {
    luaL_unref(L, FUNCTION_REF_TABLE, this->luaConditionRef);
}

boolType RuleWrapper_condition::operator () (Message msg) {
    
}


RuleWrapper_function::RuleWrapper_function(lua_State*L, int index) :
    L(L) {
    //push the index to the top of the stack
    lua_pushvalue(L, index);
    //push and pop into reference;
    this->luaFunctionRef = lua_getFunctionRef(L);
}

RuleWrapper_function::~RuleWrapper_function() {
    luaL_unref(L, FUNCTION_REF_TABLE, this->luaFunctionRef);
}

boolType RuleWrapper_function::operator () (Message msg) {
    
}

