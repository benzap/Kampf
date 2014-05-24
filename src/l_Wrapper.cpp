#include "l_Wrapper.hpp"

Lua_FunctionWrapper::Lua_FunctionWrapper(lua_State *L, int index) :
    L(L) {
    //push the index to the top of the stack
    lua_pushvalue(L, index);

    //push and pop into reference;
    this->luaFunctionRef = lua_getFunctionRef(L);
}

Lua_FunctionWrapper::~Lua_FunctionWrapper() {
    //luaL_unref(L, FUNCTION_REF_TABLE, this->luaConditionRef);
}

void Lua_FunctionWrapper::operator () () {
    //push our function onto the stack
    lua_pushFunctionRef(L, this->luaFunctionRef);

    //call the function,
    int numargs = 0, numresults = 0;
    int chk = lua_pcall(L, numargs, numresults, 0);

    //check if we had any errors
    if (chk) {
	//generate an error message
	lua_pcall_generateErrorMessage(L, chk);
    }
}
