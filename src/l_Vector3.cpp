#include "l_Vector3.hpp"
#include <sstream>

Vector3* lua_pushvector(lua_State *L, Vector3* vector = nullptr) {
  if (vector == nullptr) {
    vector = new Vector3();
  }

  Vector3** vectorPtr = static_cast<Vector3**>
    (lua_newuserdata(L, sizeof(Vector3)));
  
  *vectorPtr = vector;

  luaL_getmetatable(L, LUA_USERDATA_VECTOR);
  lua_setmetatable(L, -2);  

  return vector;
}

Vector3* lua_tovector(lua_State *L, int index) {
  Vector3* vector = *static_cast<Vector3**>
    (luaL_checkudata(L, index, LUA_USERDATA_VECTOR));
  if (vector == NULL) {
    luaL_error(L, "Provided userdata is not of type 'Vector3'");
  }
  return vector;
}

boolType lua_isvector(lua_State* L, int index) {
  if (lua_isuserdata(L, index)) {
      auto chk = lua_isUserdataType(L, index, LUA_USERDATA_VECTOR); 
      return chk;
  }
  return false;
}


static int l_Vector3_isVector3(lua_State *L) {
  boolType chk = lua_isvector(L, 1);
  lua_pushboolean(L, chk);

  return 1;
}

//initialization of our vector type
static int l_Vector3_Vector3(lua_State *L) {
  //get the number of arguments
  unsigned int numargs = lua_gettop(L);

  auto vector = lua_pushvector(L);
  if (numargs == 3) {
    vector->x = luaL_checknumber(L, 1);
    vector->y = luaL_checknumber(L, 2);
    vector->z = luaL_checknumber(L, 3);
  }
  else if (numargs != 3 && numargs != 0) {
    luaL_error(L, "LUA_ERROR: Vector3 takes 0 or 3 arguments [x,y,z], %d provided", numargs);
  }

  return 1;
}

static int l_Vector3_index(lua_State *L) {
  Vector3* vector = lua_tovector(L, 1);

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
      //get the metafields
      luaL_getmetatable(L, LUA_USERDATA_VECTOR);
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

static int l_Vector3_newindex(lua_State *L) {
  auto thisVector3 = lua_tovector(L, 1);
  floatType value = luaL_checknumber(L, 3);
  if (lua_isstring(L, 2)) {
    stringType sKey = lua_tostring(L, 2);
    if (sKey == "x") {
      thisVector3->x = value;
    }
    else if (sKey == "1") {
      thisVector3->x = value;
    }
    else if (sKey == "y") {
      thisVector3->y = value;
    }
    else if (sKey == "2") {
      thisVector3->y = value;
    }
    else if (sKey == "z") {
      thisVector3->z = value;
    }
    else if (sKey == "3") {
      thisVector3->z = value;
    }
    else {
      luaL_error(L, "LUA_ERROR: Index out of range --> %s",
		 sKey.c_str());
    }
  }
  else if (lua_isnumber(L, 2)) {
    int iKey = lua_tointeger(L, 2);
    if (iKey == 1) {
      (*thisVector3).x = value;
    }
    else if (iKey == 2) {
      (*thisVector3).y = value;
    }
    else if (iKey == 3) {
      (*thisVector3).z = value;
    }
    else {
      luaL_error(L, "LUA_ERROR: Index out of range --> %d",
		 iKey);
    }
  }
  else {
    luaL_error(L, "LUA_ERROR: Incorrect type for index");
  }     
}

static int l_Vector3_unm(lua_State *L) {
  Vector3* thisVector3 = lua_tovector(L, 1);

  Vector3* resultVector3Ptr = lua_pushvector(L);
  *resultVector3Ptr = -(*thisVector3);

  return 1;
}

static int l_Vector3_add(lua_State *L) {
  Vector3* vector = lua_tovector(L, 1);
  Vector3* result = lua_pushvector(L);

  if (lua_isuserdata(L, 2)) {
    Vector3 * rVector3 = lua_tovector(L, 2);
    *result = *vector + *rVector3;
  }
  else if (lua_isnumber(L, 2)) {
    auto scalarValue = lua_tonumber(L, 2);
    *result = *vector + scalarValue;
  }
  else {
    luaL_error(L, "LUA_ERROR: Incorrect type provided");
  }

  Vector3* resultVector3Ptr = lua_pushvector(L, result);

  return 1;
}

static int l_Vector3_sub(lua_State *L) {
  Vector3* vector = *static_cast<Vector3**>
    (luaL_checkudata(L, 1, LUA_USERDATA_VECTOR));

  Vector3* result = lua_pushvector(L);

  if (lua_isuserdata(L, 2)) {
    Vector3* rVector3 = lua_tovector(L, 2);
    *result = *vector + -(*rVector3);
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

static int l_Vector3_mul(lua_State *L) {
  Vector3* vector = lua_tovector(L, 1);
  float scalarResult;

  if (lua_isuserdata(L, 2)) {
    Vector3 * otherVector3 = *static_cast<Vector3**>
      (luaL_checkudata(L, 2, LUA_USERDATA_VECTOR));

    scalarResult = (*vector) * (*otherVector3);
    lua_pushnumber(L, scalarResult);
  }
  else if (lua_isnumber(L, 2)) {
    auto scalarValue = lua_tonumber(L, 2);

    Vector3* result = lua_pushvector(L);

    *result = (*vector) * scalarValue;
  }
  else {
    luaL_error(L, "LUA_ERROR: Incorrect type provided");
  }

  return 1;
}

static int l_Vector3_mod(lua_State *L) {
  Vector3* vector = lua_tovector(L, 1);
  Vector3* rVector3 = lua_tovector(L, 2);
  Vector3* result = lua_pushvector(L);

  *result = (*vector) % (*rVector3);

  return 1;
}

static int l_Vector3_eq(lua_State *L) {
  Vector3* vector = lua_tovector(L, 1);
  Vector3* rVector3 = lua_tovector(L, 2);

  if (*vector == *rVector3) {
    lua_pushboolean(L, true);
  }
  else {
    lua_pushboolean(L, false);
  }

  return 1;
}

static int l_Vector3_tostring(lua_State *L) {
  Vector3* vector = lua_tovector(L, 1);

  std::stringstream output (std::stringstream::in | std::stringstream::out);

  output << "V(";
  output << vector->x;
  output << ", ";
  output << vector->y;
  output << ", ";
  output << vector->z;
  output << ")";

  stringType ss = output.str();
  lua_pushstring(L, ss.c_str());

  return 1;
}

static int l_Vector3_unit(lua_State *L) {
  Vector3* vector = lua_tovector(L, 1);
  Vector3* result = lua_pushvector(L);

  *result = vector->unit();

  return 1;
}

static int l_Vector3_magnitude(lua_State *L) {
  Vector3* vector = lua_tovector(L, 1);
  
  floatType result = vector->magnitude();
  lua_pushnumber(L, result);

  return 1;
}

static int l_Vector3_magnitude_real(lua_State *L) {
  Vector3* vector = lua_tovector(L, 1);
  
  floatType result = vector->magnitude_real();
  lua_pushnumber(L, result);

  return 1;
}

static int l_Vector3_gc(lua_State *L) {
  Vector3* vector = lua_tovector(L, 1);
  delete vector;
  
  return 0;
}

static int l_Vector3_len(lua_State *L) {
  lua_pushnumber(L, 3);
  return 1;
}

static int l_Vector3_compProd(lua_State *L) {
  Vector3* thisVector3 = lua_tovector(L, 1);
  Vector3* rVector3 = lua_tovector(L, 2);

  Vector3* result = lua_pushvector(L);
  *result = thisVector3->comp_prod(*rVector3);

  return 1;
}

static const struct luaL_Reg l_Vector3_Registry [] = {
  {"Vector3", l_Vector3_Vector3},
  {"isVector3", l_Vector3_isVector3},
  {NULL, NULL}
};

static const struct luaL_Reg l_Vector3 [] = {
  {"__index", l_Vector3_index},
  {"__newindex", l_Vector3_newindex},
  {"__gc", l_Vector3_gc},
  {"__tostring", l_Vector3_tostring},
  {"__unm", l_Vector3_unm},
  {"__add", l_Vector3_add},
  {"__sub", l_Vector3_sub},
  {"__mul", l_Vector3_mul},
  {"__mod", l_Vector3_mod},
  {"__len", l_Vector3_len},
  {"__eq", l_Vector3_eq},
  {"compProd", l_Vector3_compProd},
  {"unit", l_Vector3_unit},
  {"magnitude", l_Vector3_magnitude},
  {"magnitude_real", l_Vector3_magnitude_real},
  {NULL, NULL}
};

int luaopen_vector(lua_State *L) {
  //Vector3
  luaL_newmetatable(L, LUA_USERDATA_VECTOR);
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_register(L, NULL, l_Vector3);

  luaL_register(L, KF_LUA_LIBNAME, l_Vector3_Registry);
  return 1;
}
