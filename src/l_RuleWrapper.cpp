#include "l_RuleWrapper.hpp"

boolType RuleWrapper_condition::operator () (Message* msg) {
    //push our function onto the stack
    lua_pushFunctionRef(this->L, this->luaFunctionRef);
    //push the message onto the stack
    lua_pushmessage(this->L, msg);
    //call the function, the result is pushed onto the stack
    int chk = lua_pcall(L, 1, 1, 0);
    if (chk) {
	lua_pcall_generateErrorMessage(this->L, chk);
	
	return false;
    }
    else {
	//grab the boolean result
	boolType result = lua_toboolean(this->L, -1);
	lua_pop(L, 1);
	return result;
    }
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

