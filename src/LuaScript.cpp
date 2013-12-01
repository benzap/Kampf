#include "LuaScript.hpp"

LuaScript::LuaScript(Kampf* kf) {
  this->L = lua_open();

  //load all of our libraries
  // luaopen_base(this->L);
  // luaopen_table(this->L);
  // luaopen_io(this->L);
  // luaopen_string(this->L);
  // luaopen_math(this->L);

  //standard libs
  luaL_openlibs(L);

  //custom libraries extending kampf

  //kf vectors
  luaopen_vector(L);
  
  //kf quaternions
  luaopen_quaternion(L);

  //SDLAssetManager
  luaopen_SDL_AM(L);
  luaopen_SDLDrawable(L);

  //Entity-related
  luaopen_entity(L);
  luaopen_customAttribute(L);
  

  if (kf != nullptr) {
    luaopen_kampf(L, kf);
    luaopen_messenger(L, kf->getMessenger());
    luaopen_message(L);
    luaopen_rulemachine(L, kf->getRuleMachine());
  }

  //hard coding the packages path to the current directory
  this->clearPath();
  this->addPath("?.lua");
  this->addPath("./scripts/?.lua");
  this->addPath("../scripts/?.lua");
}

LuaScript::~LuaScript() {
  lua_close(this->L);
}

lua_State* LuaScript::getState() {
  return this->L;
}


void LuaScript::setGlobal(stringType name, floatType value) {
  lua_State *L = this->L;
  lua_pushnumber(L, value);
  lua_setglobal(L, name.c_str());
}

floatType LuaScript::getGlobal_float(stringType name) {
  floatType value;
  lua_getglobal(L, name.c_str());
  if(lua_isnumber(L, -1)) {
    value = lua_tonumber(L, -1);
    return value;
  }
  else {
    std::cerr << "LUA_ERROR: global float doesn't exist with name '" << name << "'";
    std::cerr << std::endl;
    return 0;
  }
}

void LuaScript::setGlobal(stringType name, integerType value) {
  lua_State *L = this->L;
  lua_pushnumber(L, value);
  lua_setglobal(L, name.c_str());
}

integerType LuaScript::getGlobal_int(stringType name) {
  integerType value = 0;
  lua_getglobal(L, name.c_str());
  if(lua_isnumber(L, -1)) {
    value = lua_tointeger(L, -1);
    return value;
  }
  else {
    std::cerr << "LUA_ERROR: global integer doesn't exist with name '" << name << "'";
    std::cerr << std::endl;
    return 0;
  }
}

void LuaScript::setGlobal(stringType name, stringType value) {
  lua_State *L = this->L;
  lua_pushstring(L, value.c_str());
  lua_setglobal(L, name.c_str());
}

stringType LuaScript::getGlobal_string(stringType name) {
  stringType value;
  lua_getglobal(L, name.c_str());
  if(lua_isstring(L, -1)) {
    value = lua_tostring(L, -1);
    return value;
  }
  else {
    std::cerr << "LUA_ERROR: global string doesn't exist with name '" << name << "'";
    std::cerr << std::endl;
    return 0;
  }
}

void LuaScript::setGlobal(stringType name, floatArrayType value) {
  lua_State *L = this->L;
  lua_newtable(L);
  unsigned int index = 1;
  for (auto i : value) {
    lua_pushnumber(L, i);
    lua_rawseti(L, -2, index++);
  }
  lua_setglobal(L, name.c_str());
}

floatArrayType LuaScript::getGlobal_floatArray(stringType name) {
  floatArrayType value;
  lua_getglobal(L, name.c_str());
  //find the length
  unsigned int length = lua_objlen(L, -1);

  //places all of the values into our floatarray
  for (int i = 1; i <= length; i++) {
    lua_rawgeti(L, -1, i);
    if (lua_isnumber(L, -1)) {
      value.push_back(lua_tonumber(L, -1));
    }
    else {
      std::cerr << "LUA_ERROR: global float array index at - " << i;
      std::cerr << " - cannot be converted to float for value '" << name << "'";
      std::cerr << std::endl;
    }
    lua_pop(L, 1);
  }
  lua_pop(L, 1);
  return value;
}

void LuaScript::setGlobal(stringType name, intArrayType value) {
  lua_newtable(L);
  unsigned int index = 1;
  for (auto i : value) {
    lua_pushinteger(L, i);
    lua_rawseti(L, -2, index++);
  }
  lua_setglobal(L, name.c_str());
}

intArrayType LuaScript::getGlobal_intArray(stringType name) {
  intArrayType value;
  lua_getglobal(L, name.c_str());
  //find the length
  unsigned int length = lua_objlen(L, -1);

  //places all of the values into our floatarray
  for (int i = 1; i <= length; i++) {
    lua_rawgeti(L, -1, i);
    if (lua_isnumber(L, -1)) {
      value.push_back(lua_tointeger(L, -1));
    }
    else {
      std::cerr << "LUA_ERROR: global integer array index at - " << i;
      std::cerr << " - cannot be converted to integer for value '" << name << "'";
      std::cerr << std::endl;
    }
    lua_pop(L, 1);
  }
  lua_pop(L, 1);
  return value;
}

boolType LuaScript::loadScript(stringType filePath) {
  std::ifstream scriptFile (filePath);
    
  if (scriptFile.is_open()) {
    stringType stringBuffer((std::istreambuf_iterator<char>(scriptFile)),
			     std::istreambuf_iterator<char>());
    scriptFile.close();
    return this->loadString(stringBuffer, filePath);
  }
  else {
    std::cerr << "LUA_ERROR: Failed to load script --> " << filePath << std::endl;
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

void LuaScript::runInterpreter() {
  std::cout << "Running Kampf Interpretor" << std::endl;
  stringType buffer;
  boolType bSuccess = true;

  //set a value within lua to determine loop
  this->setGlobal("_bLoop", 1);
  
  //functions to close the interpreter
  this->loadString("function quit() _bLoop = 0 end");
  this->loadString("function exit() _bLoop = 0 end");

  while (this->getGlobal_int("_bLoop")) {
    std::cout << "Kampf>> ";
    getline(std::cin, buffer);
    bSuccess = this->loadString(buffer);
  }
  std::cout << "Kampf Interpreter Exited" << std::endl;
}

void LuaScript::addPath(stringType pathString) {
    stringType luaString = "package.path = package.path .. ";
    luaString += "';";
    luaString += pathString;
    luaString += "'";
    this->loadString(luaString);
}

void LuaScript::clearPath() {
    this->loadString("package.path = '?.lua'");
}


