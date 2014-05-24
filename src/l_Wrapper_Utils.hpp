#ifndef L_WRAPPER_UTILS__HPP
#define L_WRAPPER_UTILS__HPP
//DESCRIPTION
/*
  Includes a set of functions to make wrapping
  lua functions easier
 */

//CLASSES

//INCLUDES
#include <iostream>
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "lua.hpp"

//DEFINITIONS

//location of the function references
#define FUNCTION_REF_TABLE LUA_REGISTRYINDEX

//MACROS

//TYPEDEFS

//FUNCTIONS
//gets and creates a function reference within the table stored in
//FUNCTION_REF_TABLE
int lua_getFunctionRef(lua_State *L);

//grabs the value at the given index / reference and pushes it to the
//top of the stack.
void lua_pushFunctionRef(lua_State *L, int ref);

void lua_pcall_generateErrorMessage(lua_State *L, int chk);

//BEGIN


#endif //END L_WRAPPER_UTILS__HPP
