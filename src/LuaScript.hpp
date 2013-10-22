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
  floatType getGlobal(stringType);
  void setGlobal(stringType, integerType);
  integerType getGlobal(stringType, integerType);
  void setGlobal(stringType, stringType);
  stringType getGlobal(stringType, stringType);
  void setGlobal(stringType, floatArrayType);
  floatArrayType getGlobal(stringType, floatArrayType);
  void setGlobal(stringType, intArrayType);
  intArrayType getGlobal(stringType, intArrayType);

  //load script from the given file path
  boolType loadScript(stringType);

  //load string into the lua REPL
  boolType loadString(stringType, stringType name = "stdin");
  


};

#endif //END LUASCRIPT__HPP
