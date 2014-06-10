#include "l_SDLFontManager.hpp"

void lua_pushSDL_FM(lua_State* L, SDLFontManager* sdlfont = nullptr) {
  if (sdlfont == nullptr) {
    sdlfont = SDLFontManager::getInstance();
    }
  SDLFontManager** fontPtr = static_cast<SDLFontManager**>
    (lua_newuserdata(L, sizeof(SDLFontManager*)));

  *fontPtr = sdlfont;

  luaL_getmetatable(L, LUA_USERDATA_SDLFONTMANAGER);
  lua_setmetatable(L, -2);  
}

SDLFontManager* lua_toSDL_FM(lua_State* L, int index) {
  SDLFontManager* fontPtr = *static_cast<SDLFontManager**>
    (luaL_checkudata(L, index, LUA_USERDATA_SDLFONTMANAGER));
  if (fontPtr == NULL) {
    luaL_error(L, "Provided userdata is not of type 'SDLFontManager'");
  }
  return SDLFontManager::getInstance();
}

boolType lua_isSDL_FM(lua_State *L, int index) {
  if (lua_isuserdata(L, 1)) {
    SDLFontManager* fontPtr = *static_cast<SDLFontManager**>
      (luaL_checkudata(L, index, LUA_USERDATA_SDLFONTMANAGER));
    if (fontPtr != NULL) {
      return true;
    }
    return false;
  }
  else {
    return false;
  }
}

static int l_SDL_FM_SDL_FM(lua_State *L) {
  lua_pushSDL_FM(L);

  return 1;
}

static int l_SDL_FM_isSDL_FM(lua_State *L) {
  if (lua_isSDL_FM(L, 1)) {
    lua_pushboolean(L, 1);
  }
  else {
    lua_pushboolean(L, 0);
  }
  return 1;
}

static int l_SDL_FM_addFont(lua_State *L) {
  auto sdlfont = lua_toSDL_FM(L, 1);
  stringType name = luaL_checkstring(L, 2);
  stringType filename = luaL_checkstring(L, 3);
  int pointSize = luaL_checkint(L, 4);
  auto font = sdlfont->addFont(name, filename, pointSize);

  lua_push_sdlfont(L, font);

  return 1;
}


static int l_SDL_FM_getFont(lua_State *L) {
  auto sdlfont = lua_toSDL_FM(L, 1);
  stringType name = luaL_checkstring(L, 2);
  
  auto font = sdlfont->getFont(name);
  lua_push_sdlfont(L, font);

  return 1;
}

static int l_SDL_FM_deleteFont(lua_State *L) {
  auto sdlfont = lua_toSDL_FM(L, 1);
  stringType name = luaL_checkstring(L, 2);

  sdlfont->removeFont(name);
  
  return 0;
}

static int l_SDL_FM_hasFont(lua_State *L) {
  auto sdlfont = lua_toSDL_FM(L, 1);
  stringType name = luaL_checkstring(L, 2);
  if (sdlfont->hasFont(name)) {
    lua_pushboolean(L, 1);
  }
  else {
    lua_pushboolean(L, 0);
  }
  return 1;
}

static int l_SDL_FM_copyFont(lua_State *L) {
    auto sdlfont = lua_toSDL_FM(L, 1);
    stringType srcName = luaL_checkstring(L, 2);
    stringType destName = luaL_checkstring(L, 3);

    auto font = sdlfont->copyFont(srcName, destName);
    lua_push_sdlfont(L, font);
    
    return 1;
}

static const struct luaL_Reg l_SDL_FM_Registry [] = {
  {"SDLFontManager", l_SDL_FM_SDL_FM},
  {"isSDLFontManager", l_SDL_FM_isSDL_FM},
  {NULL, NULL}
};

static const struct luaL_Reg l_SDL_FM [] = {
  {"addFont", l_SDL_FM_addFont},
  {"getFont", l_SDL_FM_getFont},
  {"deleteFont", l_SDL_FM_deleteFont},
  {"hasFont", l_SDL_FM_hasFont},
  {"copyFont", l_SDL_FM_copyFont},

  {NULL, NULL}
};

int luaopen_SDL_FM(lua_State *L) {
  //SDLFontManager
  luaL_newmetatable(L, LUA_USERDATA_SDLFONTMANAGER);
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_register(L, NULL, l_SDL_FM);

  luaL_register(L, KF_LUA_LIBNAME, l_SDL_FM_Registry);

  return 1;
}
