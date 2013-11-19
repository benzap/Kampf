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
    //luaL_unref(L, FUNCTION_REF_TABLE, this->luaConditionRef);
}

boolType RuleWrapper_condition::operator () (Message* msg) {
    //push our function onto the stack
    lua_pushFunctionRef(L, this->luaConditionRef);
    //push the message onto the stack
    lua_pushmessage(L, msg);
    //call the function, the result is pushed onto the stack
    //lua_call(L, 1, 1);
    
    

    int chk = lua_pcall(L, 1, 1, 0);
    if (chk) {
	if (chk == LUA_ERRRUN) {
	    stringType errString = lua_tostring(L, -1);
	    std::cout << "LUA_ERROR - Condition Function: " << errString << std::endl;
	}
	else if (chk == LUA_ERRMEM) {
	    std::cout << "LUA_ERROR - Condition Function: MEMORY ERROR" << std::endl;
	}
	else if (chk == LUA_ERRERR) {
	    std::cout << "LUA_ERROR - Condition Function: Error Handler Error" << std::endl;
	}
	
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
    //call the function, the result is pushed onto the stack
    //lua_call(L, 1, 1);

    int chk = lua_pcall(L, 1, 1, 0);
    boolType result = false;
    if (chk) {
	if (chk == LUA_ERRRUN) {
	    stringType errString = lua_tostring(L, -1);
	    std::cout << "LUA_ERROR - Expression Function: " << errString << std::endl;
	}
	else if (chk == LUA_ERRMEM) {
	    std::cout << "LUA_ERROR - Expression Function: MEMORY ERROR" << std::endl;
	}
	else if (chk == LUA_ERRERR) {
	    std::cout << "LUA_ERROR - Expression Function: Error Handler Error" << std::endl;
	}
	else {
	    std::cout << "LUA_ERROR - Expression Function: Unknown Error" << std::endl;
	}
    }
    else {
	//grab the boolean result
	result = lua_toboolean(L, -1);
	lua_pop(L, 1);
    }
    //return result;
}

