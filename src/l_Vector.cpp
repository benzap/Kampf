#include "l_Vector.hpp"

Vector* lua_pushvector(lua_State *L, Vector* vector = nullptr) {
  if (vector == nullptr) {
    vector = new Vector();
  }

  Vector** vectorPtr = static_cast<Vector**>
    (lua_newuserdata(L, sizeof(Vector)));
  
  *vectorPtr = vector;

  luaL_getmetatable(L, LUA_USERDATA_VECTOR);
  lua_setmetatable(L, -2);  

  return vector;
}

Vector* lua_tovector(lua_State *L, int index) {
  Vector* vector = *static_cast<Vector**>
    (luaL_checkudata(L, index, LUA_USERDATA_VECTOR));
  return vector;
}

//initialization of our vector type
static int l_Vector_Vector(lua_State *L) {
  //get the number of arguments
  unsigned int numargs = lua_gettop(L);

  auto vector = lua_pushvector(L);
  if (numargs == 3) {
    vector->x = luaL_checknumber(L, 1);
    vector->y = luaL_checknumber(L, 2);
    vector->z = luaL_checknumber(L, 3);
  }
  else if (numargs != 3 && numargs != 0) {
    luaL_error(L, "LUA_ERROR: Vector takes 0 or 3 arguments [x,y,z], %d provided", numargs);
  }

  return 1;
}

static int l_Vector_index(lua_State *L) {
  Vector* vector = lua_tovector(L, 1);

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

static int l_Vector_unm(lua_State *L) {
  Vector* thisVector = lua_tovector(L, 1);

  Vector* resultVectorPtr = lua_pushvector(L);
  *resultVectorPtr = -(*thisVector);

  return 1;
}

static int l_Vector_add(lua_State *L) {
  Vector* vector = lua_tovector(L, 1);
  Vector* result = lua_pushvector(L);

  if (lua_isuserdata(L, 2)) {
    Vector * rVector = lua_tovector(L, 2);
    *result = *vector + *rVector;
  }
  else if (lua_isnumber(L, 2)) {
    auto scalarValue = lua_tonumber(L, 2);
    *result = *vector + scalarValue;
  }
  else {
    luaL_error(L, "LUA_ERROR: Incorrect type provided");
  }

  Vector* resultVectorPtr = lua_pushvector(L, result);

  return 1;
}

static int l_Vector_sub(lua_State *L) {
  Vector* vector = *static_cast<Vector**>
    (luaL_checkudata(L, 1, LUA_USERDATA_VECTOR));

  Vector* result = lua_pushvector(L);

  if (lua_isuserdata(L, 2)) {
    Vector* rVector = lua_tovector(L, 2);
    *result = *vector + -(*rVector);
  }
  else if (lua_isnumber(L, 2)) {
    auto scalarValue = lua_tonumber(L, 2);
    *result = *vector + -scalarValue;
  }
  else {
    luaL_error(L, "LUA_ERROR: Incorrect type provided");
  }

  return 1;
}

static int l_Vector_mul(lua_State *L) {
  Vector* vector = lua_tovector(L, 1);
  float scalarResult;

  if (lua_isuserdata(L, 2)) {
    Vector * otherVector = *static_cast<Vector**>
      (luaL_checkudata(L, 2, LUA_USERDATA_VECTOR));

    scalarResult = (*vector) * (*otherVector);
    lua_pushnumber(L, scalarResult);
  }
  else if (lua_isnumber(L, 2)) {
    auto scalarValue = lua_tonumber(L, 2);

    Vector* result = lua_pushvector(L);

    *result = (*vector) * scalarValue;
  }
  else {
    luaL_error(L, "LUA_ERROR: Incorrect type provided");
  }

  return 1;
}

static int l_Vector_mod(lua_State *L) {
  Vector* vector = lua_tovector(L, 1);
  Vector* rVector = lua_tovector(L, 2);
  Vector* result = lua_pushvector(L);

  *result = (*vector) % (*rVector);

  return 1;
}

static int l_Vector_tostring(lua_State *L) {
  Vector* vector = lua_tovector(L, 1);

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

static int l_Vector_gc(lua_State *L) {
  Vector* vector = lua_tovector(L, 1);
  delete vector;
  
  return 0;
}

static int l_Vector_len(lua_State *L) {
  lua_pushnumber(L, 3);
  return 1;
}

static int l_Vector_compProd(lua_State *L) {
  Vector* thisVector = lua_tovector(L, 1);
  Vector* rVector = lua_tovector(L, 2);

  Vector* result = lua_pushvector(L);
  *result = thisVector->comp_prod(*rVector);

  return 1;
}

static const struct luaL_Reg l_Vector_Registry [] = {
  {"Vector", l_Vector_Vector},
  {NULL, NULL}
};

static const struct luaL_Reg l_Vector [] = {
  {"__index", l_Vector_index},
  {"__gc", l_Vector_gc},
  {"__tostring", l_Vector_tostring},
  {"__unm", l_Vector_unm},
  {"__add", l_Vector_add},
  {"__sub", l_Vector_sub},
  {"__mul", l_Vector_mul},
  {"__mod", l_Vector_mod},
  {"__len", l_Vector_len},
  {"compProd", l_Vector_compProd},
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
