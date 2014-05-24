#ifndef L_WRAPPER__HPP
#define L_WRAPPER__HPP
//DESCRIPTION
/*
  General rule wrappers for typical lua functions
 */

//CLASSES
class lua_FunctionWrapper;

//INCLUDES
#include "LuaScript.hpp"
#include "l_Wrapper_Utils.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class Lua_FunctionWrapper {
private:
    //a reference to the current lua_state
    lua_State *L = nullptr;

    //a reference to our function within the lua state
    int luaFunctionRef = LUA_NOREF;
public:
    Lua_FunctionWrapper(lua_State *L, int index);
    virtual ~Lua_FunctionWrapper();

    //include your own operator() when wrapping the lua function
    void operator() ();
    
};

#endif //END L_WRAPPER__HPP
