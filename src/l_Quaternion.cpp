#include "l_Vector.hpp"
#include <sstream>

Quaternion* lua_pushquaternion(lua_State *L, Quaternion* quat = nullptr) {
  if (quat == nullptr) {
    quat = new Quaternion();
  }

  Quaternion** quatPtr = static_cast<Quaternion**>
    (lua_newuserdata(L, sizeof(Quaternion)));

  *quatPtr = quat;

  luaL_getmetatable(L, LUA_USERDATA_QUATERNION);
  lua_setmetatable(L, -2);  

  return quat;
}

Quaternion* lua_toquaternion(lua_State *L, int index) {
  Quaternion* quat = *static_cast<Quaternion**>
    (luaL_checkudata(L, index, LUA_USERDATA_QUATERNION));
  return quat;
}

static int l_Quaternion_Quaternion(lua_State *L) {
  //get the number of arguments
  unsigned int numargs = lua_gettop(L);

  auto quat = lua_pushquaternion(L);
  if (numargs == 4) {
    quat->w = luaL_checknumber(L, 1);
    quat->v.x = luaL_checknumber(L, 2);
    quat->v.y = luaL_checknumber(L, 3);
    quat->v.z = luaL_checknumber(L, 4);
  }
  else if (numargs != 4 && numargs != 0) {
    luaL_error(L, "LUA_ERROR: Quaternion takes 0 or 4 arguments [w,x,y,z], %d provided", numargs);
  }

  return 1;
}

static int l_Quaternion_tostring(lua_State *L) {
  Quaternion* quat = lua_toquaternion(L, 1);

  std::stringstream output (std::stringstream::in | std::stringstream::out);

  output << "Q(";
  output << quat->w;
  output << ", ";
  output << quat->v.x;
  output << ", ";
  output << quat->v.y;
  output << ", ";
  output << quat->v.z;
  output << ")";

  stringType ss = output.str();
  lua_pushstring(L, ss.c_str());

  return 1;
}

static int l_Quaternion_gc(lua_State *L) {
  auto quat = lua_toquaternion(L, 1);
  delete quat;
  return 0;
}

static int l_Quaternion_add(lua_State *L) {
  Quaternion* quat = lua_toquaternion(L, 1);
  Quaternion* rValue = lua_toquaternion(L, 2);

  Quaternion* result = lua_pushquaternion(L);
  *result = *quat + *rValue;
  
  return 1;
}

static int l_Quaternion_index(lua_State *L) {
  Quaternion* quaternion = lua_toquaternion(L, 1);

  auto numargs = lua_gettop(L);
  if (numargs > 2) {
    luaL_error(L, "LUA_ERROR: Wrong number of arguments, %d provided",
	       numargs);
  }
  if (lua_isnumber(L, 2)) {
    integerType index = lua_tointeger(L, 2);
    lua_pop(L, 1);
    
    if (index < 1 || index > 4) {
      luaL_error(L, "LUA_ERROR: Index out of range --> %d", index);
    }

    switch(index) {
    case 1:
      lua_pushnumber(L, quaternion->w);
      break;
    case 2:
      lua_pushnumber(L, quaternion->v.x);
      break;
    case 3:
      lua_pushnumber(L, quaternion->v.y);
      break;
    case 4:
      lua_pushnumber(L, quaternion->v.z);
      break;
    }

    return 1;
  }
  else if (lua_isstring(L, 2)) {
    stringType sIndex = lua_tostring(L, 2);
    if (sIndex == "w") {
      lua_pushnumber(L, quaternion->w);
    }
    else if (sIndex == "x") {
      lua_pushnumber(L, quaternion->v.x);
    }
    else if (sIndex == "y") {
      lua_pushnumber(L, quaternion->v.y);
    }
    else if (sIndex == "z") {
      lua_pushnumber(L, quaternion->v.z);
    }
    else {
      //get the metafields
      luaL_getmetatable(L, LUA_USERDATA_QUATERNION);
      lua_getfield(L, -1, sIndex.c_str());
    }

    return 1;
  }
  else {
    luaL_error(L, "LUA_ERROR: Incorrect type");
    return 0;
  }
  return 0;
}

static int l_Quaternion_newindex(lua_State *L) {
  auto thisQuaternion = lua_toquaternion(L, 1);
  floatType value = luaL_checknumber(L, 3);
  if (lua_isstring(L,2)) {
    stringType sKey = lua_tostring(L, 2);
    if (sKey == "w") {
      thisQuaternion->w = value;
    }
    else if (sKey == "1") {
      thisQuaternion->w = value;
    }
    else if (sKey == "x") {
      thisQuaternion->v.x = value;
    }
    else if (sKey == "2") {
      thisQuaternion->v.x = value;
    }
    else if (sKey == "y") {
      thisQuaternion->v.y = value;
    }
    else if (sKey == "3") {
      thisQuaternion->v.y = value;
    }
    else if (sKey == "z") {
      thisQuaternion->v.z = value;
    }
    else if (sKey == "4") {
      thisQuaternion->v.z = value;
    }
    else {
      luaL_error(L, "LUA_ERROR: String Index out of range --> %s",
		 sKey.c_str());
    }
  }
  else if (lua_isnumber(L, 2)) {
    int iKey = lua_tointeger(L, 2);
    if (iKey == 1) {
      thisQuaternion->w = value;
    }
    else if (iKey == 2) {
      thisQuaternion->v.x = value;
    }
    else if (iKey == 3) {
      thisQuaternion->v.y = value;
    }
    else if (iKey == 4) {
      thisQuaternion->v.z = value;
    }
    else {
      luaL_error(L, "LUA_ERROR: Integer Index out of range --> %d",
		 iKey);
    }
  }
  else {
    luaL_error(L, "LUA_ERROR: Incorrect type for index");
  }     
}

static int l_Quaternion_eq(lua_State *L) {
  auto quat = lua_toquaternion(L, 1);
  auto rValue = lua_toquaternion(L, 2);

  boolType result = (*quat == *rValue);
  lua_pushboolean(L, result);
  
  return 1;
}


static const struct luaL_Reg l_Quaternion_Registry [] = {
  {"Quaternion", l_Quaternion_Quaternion},
  {NULL, NULL}
};

static const struct luaL_Reg l_Quaternion [] = {
  {"__index", l_Quaternion_index},
  {"__newindex", l_Quaternion_newindex},
  {"__tostring", l_Quaternion_tostring},
  {"__gc", l_Quaternion_gc},
  {"__add", l_Quaternion_add},
  {"__eq", l_Quaternion_eq},
  {NULL, NULL}
};

int luaopen_quaternion(lua_State *L) {
  //Quaternion
  luaL_newmetatable(L, LUA_USERDATA_QUATERNION);
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_register(L, NULL, l_Quaternion);

  luaL_register(L, KF_LUA_LIBNAME, l_Quaternion_Registry);
}
