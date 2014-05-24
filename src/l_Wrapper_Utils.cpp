#include "l_Wrapper_Utils.hpp"
#include <cassert>

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

void lua_pcall_generateErrorMessage(lua_State *L, int chk) {
    assert(chk);
    
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
