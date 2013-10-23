#include "l_Vector.hpp"

//initialization of our vector type
static int l_Vector_Vector(lua_State *L) {
  //create a Vector
  Vector* vector = new Vector();

  //get the number of arguments
  unsigned int numargs = lua_gettop(L);

  if (numargs == 3) {
    vector->x = luaL_checknumber(L, 1);
    vector->y = luaL_checknumber(L, 2);
    vector->z = luaL_checknumber(L, 3);
  }
  else if (numargs != 3 && numargs != 0) {
    luaL_error(L, "LUA_ERROR: Vector takes 0 or 3 arguments [x,y,z], %d provided", numargs);
  }

  Vector** vectorPtr = static_cast<Vector**>
    (lua_newuserdata(L, sizeof(Vector)));
  
  *vectorPtr = vector;

  luaL_getmetatable(L, LUA_USERDATA_VECTOR);
  lua_setmetatable(L, -2);

  return 1;
}

static int l_Vector_index(lua_State *L) {
  Vector* vector = *static_cast<Vector**>
    (luaL_checkudata(L, 1, LUA_USERDATA_VECTOR));

  auto numargs = lua_gettop(L);
  if (numargs > 2) {
    luaL_error(L, "LUA_ERROR: Wrong number of arguments, %d provided",
	       numargs);
  }
  if (lua_isnumber(L, 2)) {
    integerType index = lua_tointeger(L, 2);
    lua_pop(L, 1);
    
    if (index <= 0 || index > 3) {
      luaL_error(L, "LUA_ERROR: Index out of range --> %d", index);
    }

    switch(index) {
    case 1:
      lua_pushnumber(L, vector->x);
      break;
    case 2:
      lua_pushnumber(L, vector->y);
      break;
    case 3:
      lua_pushnumber(L, vector->z);
      break;
    }

    return 1;
  }
  else if (lua_isstring(L, 2)) {
    stringType sIndex = lua_tostring(L, 2);
    
    

    if (sIndex == "x") {
      lua_pushnumber(L, vector->x);
    }
    else if (sIndex == "y") {
      lua_pushnumber(L, vector->y);
    }
    else if (sIndex == "z") {

      lua_pushnumber(L, vector->z);
    }
    else {
      luaL_error(L, "LUA_ERROR: Index out of range --> %s",
		 sIndex.c_str());
    }

    return 1;
  }
  else {
    luaL_error(L, "LUA_ERROR: Incorrect type");
    return 0;
  }
  return 0;
}

static int l_Vector_tostring(lua_State *L) {
  Vector* vector = *static_cast<Vector**>
    (luaL_checkudata(L, 1, LUA_USERDATA_VECTOR));

  std::string output = "";
  output += "V(";
  output += std::to_string(vector->x);
  output += ", ";
  output += std::to_string(vector->y);
  output += ", ";
  output += std::to_string(vector->z);
  output += ")";
  lua_pushstring(L, output.c_str());

  return 1;
}

static const struct luaL_Reg l_Vector_Registry [] = {
  {"Vector", l_Vector_Vector},
  {NULL, NULL}
};

static const struct luaL_Reg l_Vector [] = {
  {"__index", l_Vector_index},
  {"__tostring", l_Vector_tostring},
  {NULL, NULL}
};

int luaopen_vector(lua_State *L) {
  //Vector
  luaL_newmetatable(L, LUA_USERDATA_VECTOR);
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_register(L, NULL, l_Vector);

  luaL_register(L, KF_LUA_LIBNAME, l_Vector_Registry);
}
