#include "LuaScript.hpp"

LuaScript::LuaScript() {
  this->L = lua_open();

  //load all of our libraries
  // luaopen_base(this->L);
  // luaopen_table(this->L);
  // luaopen_io(this->L);
  // luaopen_string(this->L);
  // luaopen_math(this->L);
  luaL_openlibs(L);


  //custom libraries
  
  //! none so far
}

LuaScript::~LuaScript() {
  lua_close(this->L);
}

lua_State* LuaScript::getState() {
  return this->L;
}


void LuaScript::setGlobal(stringType, floatType) {

}

floatType LuaScript::getGlobal(stringType) {

}

void LuaScript::setGlobal(stringType, integerType) {

}

integerType LuaScript::getGlobal(stringType, integerType) {

}

void LuaScript::setGlobal(stringType, stringType) {

}

stringType LuaScript::getGlobal(stringType, stringType) {

}

void LuaScript::setGlobal(stringType, floatArrayType) {

}

floatArrayType LuaScript::getGlobal(stringType, floatArrayType) {

}

void LuaScript::setGlobal(stringType, intArrayType) {

}

intArrayType LuaScript::getGlobal(stringType, intArrayType) {

}

boolType LuaScript::loadScript(stringType filePath) {
  std::ifstream scriptFile (filePath);
    
  if (scriptFile.is_open()) {
    stringType stringBuffer((std::istreambuf_iterator<char>(scriptFile)),
			     std::istreambuf_iterator<char>());
    return this->loadString(stringBuffer, filePath);
  }
  else {
    std::cerr << "Failed to load script: " << filePath << std::endl;
    return false;
  }
  
}

boolType LuaScript::loadString(stringType theString, stringType name) {
  int error;
  
  error = luaL_loadbuffer(this->L, theString.c_str(), theString.size(), name.c_str()) ||
    lua_pcall(L, 0, 0, 0);
  
  if (error) {
    auto errorMessage = stringType(lua_tostring(L, -1));
    std::cerr << "LUA_ERROR: " << errorMessage << std::endl;
    lua_pop(L, 1);
    return false;
  }
  return true;
}
