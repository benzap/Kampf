#ifndef LUASCRIPT__HPP
#define LUASCRIPT__HPP
//DESCRIPTION
/*
  Contains the lua scripting singleton, which will allow lua scripting
  within the engine at key points. This should speed up production.
 */

//INCLUDES
#include <iostream>
#include <fstream>
#include <streambuf>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"

#include "lua.hpp"


//CLASSES
class LuaScript;

//DEFINITIONS

//the name of the library to store all of our lua bindings
#define KF_LUA_LIBNAME "kf"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class LuaScript {
private:
  lua_State *L;
public:
  LuaScript();
  virtual ~LuaScript();

  lua_State* getState();

  void setGlobal(stringType, floatType);
  floatType getGlobal_float(stringType);
  void setGlobal(stringType, integerType);
  integerType getGlobal_int(stringType);
  void setGlobal(stringType, stringType);
  stringType getGlobal_string(stringType);
  void setGlobal(stringType, floatArrayType);
  floatArrayType getGlobal_floatArray(stringType);
  void setGlobal(stringType, intArrayType);
  intArrayType getGlobal_intArray(stringType);

  //load script from the given file path
  boolType loadScript(stringType);

  //load string into the lua REPL
  boolType loadString(stringType, stringType name = "stdin");
  


};

#endif //END LUASCRIPT__HPP
