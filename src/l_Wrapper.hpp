#ifndef L_WRAPPER__HPP
#define L_WRAPPER__HPP
//DESCRIPTION
/*
  General rule wrappers for typical lua functions
 */

//CLASSES
class Lua_FunctionWrapper;
class LuaWrap_VoidFunction;

//INCLUDES
#include "lua.hpp"
#include "l_Wrapper_Utils.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN

/*
  An Abstract Function wrapper used for passing lua functions
  into the c++ world
 */
class Lua_FunctionWrapper {
protected:
    //a reference to the current lua_state
    lua_State *L = nullptr;

    //a reference to our function within the lua state
    int luaFunctionRef = LUA_NOREF;
public:
    Lua_FunctionWrapper(lua_State *L, int index);
    virtual ~Lua_FunctionWrapper();

    //include your own operator() when wrapping the lua function
    //void operator() ();
    
};

/*
  A Lua function wrapper for functions of the form:
  
  void function(void)
 */
class LuaWrap_VoidFunction : public Lua_FunctionWrapper {
public:
    LuaWrap_VoidFunction(lua_State *L, int index) :
	Lua_FunctionWrapper(L, index) {}

    void operator () ();
    
};

#endif //END L_WRAPPER__HPP
