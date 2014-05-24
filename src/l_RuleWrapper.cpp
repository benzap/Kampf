#include "l_RuleWrapper.hpp"

RuleWrapper_condition::RuleWrapper_condition(lua_State *L, int index) :
    L(L) {
    //push the index to the top of the stack
    lua_pushvalue(L, index);

    //push and pop into reference;
    this->luaConditionRef = lua_getFunctionRef(L);
}

RuleWrapper_condition::~RuleWrapper_condition() {
    //luaL_unref(L, FUNCTION_REF_TABLE, this->luaConditionRef);
}

boolType RuleWrapper_condition::operator () (Message* msg) {
    //push our function onto the stack
    lua_pushFunctionRef(L, this->luaConditionRef);
    //push the message onto the stack
    lua_pushmessage(L, msg);
    //call the function, the result is pushed onto the stack
    int chk = lua_pcall(L, 1, 1, 0);
    if (chk) {
	lua_pcall_generateErrorMessage(L, chk);
	
	return false;
    }
    else {
	//grab the boolean result
	boolType result = lua_toboolean(L, -1);
	lua_pop(L, 1);
	return result;
    }
}


RuleWrapper_function::RuleWrapper_function(lua_State*L, int index) :
    L(L) {
    //push the index to the top of the stack
    lua_pushvalue(L, index);

    //push and pop into reference;
    this->luaFunctionRef = lua_getFunctionRef(L);
}

RuleWrapper_function::~RuleWrapper_function() {
    //luaL_unref(L, FUNCTION_REF_TABLE, this->luaFunctionRef);
}

void RuleWrapper_function::operator () (Message* msg) {
    //push our function onto the stack
    lua_pushFunctionRef(L, this->luaFunctionRef);
    //push the message onto the stack
    lua_pushmessage(L, msg);

    //Call the function, we have one message argument
    int numargs = 1, numresults = 0;
    int chk = lua_pcall(L, numargs, numresults, 0);
    
    //check if we had any errors
    if (chk) {
	//generate an error message
	lua_pcall_generateErrorMessage(L, chk);
    }
}

