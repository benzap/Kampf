#ifndef L_UTILS__HPP
#define L_UTILS__HPP
//DESCRIPTION
/*
  The Lua Utilities library, with helper functions
 */

//CLASSES

//INCLUDES
#include <iostream>
#include <fstream>
#include <streambuf>
#include "lua.hpp"

#include "kampf.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS
boolType lua_isUserdataType(lua_State *L, int index, const char *tname);

//BEGIN


#endif //END L_UTILS__HPP
