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

}

static int l_Vector_tostring(lua_State *L) {

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
