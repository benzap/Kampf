#include "l_kampf.hpp"

void lua_registerKampf(lua_State* L, Kampf* kf) {
  //push our kampf pointer into the registry index table
  lua_pushstring(L, LUA_REGISTRY_KAMPF);
  lua_pushlightuserdata(L, (void *)kf);
  lua_settable(L, LUA_REGISTRYINDEX);
}

boolType lua_hasKampf(lua_State* L) {
  lua_pushstring(L, LUA_REGISTRY_KAMPF);
  lua_gettable(L, LUA_REGISTRYINDEX);
  if (lua_islightuserdata(L, -1)) {
    Kampf* kf = (Kampf *) lua_touserdata(L, -1);
    if (kf != nullptr) {
      return true;
    }
  }
  return false;
}

Kampf* lua_getKampf(lua_State* L) {
  lua_pushstring(L, LUA_REGISTRY_KAMPF);
  lua_gettable(L, LUA_REGISTRYINDEX);
  Kampf* kf = (Kampf *) lua_touserdata(L, -1);
  lua_pop(L, 1);
  return kf;
}

static int l_kampf_runMainLoop(lua_State *L) {
  //grab our kampf user data from the registry
  Kampf* kf = lua_getKampf(L);
  int duration = (Uint32) luaL_optint(L, 1, KF_LOOP_FOREVER);

  kf->runMainLoop(duration);
  return 0;
}

static int l_kampf_getMessenger(lua_State *L) {
  return 0;
}

static int l_kampf_getRuleMachine(lua_State *L) {
  return 0;
}

static int l_kampf_addSystem(lua_State *L) {
  return 0;
}

static const struct luaL_Reg l_kampf [] = {
  {"runMainLoop", l_kampf_runMainLoop},
  {"getMessenger", l_kampf_getMessenger},
  {"getRuleMachine", l_kampf_getRuleMachine},
  {"addSystem", l_kampf_addSystem},
  {NULL, NULL}
};

int luaopen_kampf(lua_State *L, Kampf* kf) {
  lua_registerKampf(L, kf);
  luaL_register(L, KF_LUA_LIBNAME, l_kampf);

  return 1;
}