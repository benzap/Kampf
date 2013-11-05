#include "l_SDLDrawable.hpp"

void lua_push_sdldrawable(lua_State *L, SDLDrawable* sdlDrawable) {
  SDLDrawable** drawablePtr = static_cast<SDLDrawable**>
    (lua_newuserdata(L, sizeof(SDLDrawable*)));
  
  *drawablePtr = sdlDrawable;

  luaL_getmetatable(L, LUA_USERDATA_SDLDRAWABLE);
  lua_setmetatable(L, -2);
}

SDLDrawable* lua_to_sdldrawable(lua_State *L, int index) {
  SDLDrawable* drawablePtr = *static_cast<SDLDrawable**>
    (luaL_checkudata(L, index, LUA_USERDATA_SDLDRAWABLE));
  if (drawablePtr == NULL) {
    luaL_error(L, "Provided userdata is not of type 'SDLDrawable'");
  }
  return drawablePtr;
}

boolType lua_is_sdldrawable(lua_State *L, int index) {
  if (lua_isuserdata(L, 1)) {
    SDLDrawable* drawablePtr = *static_cast<SDLDrawable**>
      (luaL_checkudata(L, index, LUA_USERDATA_SDLDRAWABLE));
    if (drawablePtr != NULL) {
      return true;
    }
    return false;
  }
  else {
    return false;
  }
}

static int l_isSDLDrawable(lua_State *L) {
  if (lua_is_sdldrawable(L, 1)) {
    lua_pushboolean(L, 1);
  }
  else {
    lua_pushboolean(L, 0);
  }
  return 1;
}

static int l_SDLDrawable_getRect(lua_State *L) {
  auto sdlDrawable = lua_to_sdldrawable(L, 1);
  const SDL_Rect* rect = sdlDrawable->getRect();
  lua_newtable(L);
  lua_pushnumber(L, rect->x);
  lua_setfield(L, -2, "x");

  lua_pushnumber(L, rect->y);
  lua_setfield(L, -2, "y");

  lua_pushnumber(L, rect->w);
  lua_setfield(L, -2, "w");
  
  lua_pushnumber(L, rect->h);
  lua_setfield(L, -2, "h");

  return 1;
}

static int l_SDLDrawable_setRect(lua_State *L) {
  auto sdlDrawable = lua_to_sdldrawable(L, 1);
  //second argument is a table type
  luaL_checktype(L, 2, LUA_TTABLE);
  //expects a table with keys "w", "h", "x", "y"
  lua_getfield(L, 2, "w");
  floatType w = luaL_checknumber(L, -1);
  lua_getfield(L, 2, "h");
  floatType h = luaL_checknumber(L, -1);
  lua_getfield(L, 2, "x");
  floatType x = luaL_checknumber(L, -1);
  lua_getfield(L, 2, "y");
  floatType y = luaL_checknumber(L, -1);
  lua_pop(L, 4);

  sdlDrawable->setRect(x, y, w, h);
}

static int l_SDLDrawable_draw(lua_State *L) {
  auto sdlDrawable = lua_to_sdldrawable(L, 1);
  auto position = lua_tovector(L, 2);
  auto orientation = lua_toquaternion(L, 3);
  sdlDrawable->draw(*position, *orientation);
}

static const struct luaL_Reg l_SDL_Drawable_Registry [] = {
  {"isSDLDrawable", l_isSDLDrawable},
  {NULL, NULL}
};

static const struct luaL_Reg l_SDL_Drawable [] = {
  {"getRect", l_SDLDrawable_getRect},
  {"setRect", l_SDLDrawable_setRect},
  {"draw", l_SDLDrawable_draw},
  {NULL, NULL}
};

int luaopen_SDLDrawable(lua_State *L) {
  //SDLAssetManager
  luaL_newmetatable(L, LUA_USERDATA_SDLDRAWABLE);
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_register(L, NULL, l_SDL_Drawable);

  luaL_register(L, KF_LUA_LIBNAME, l_SDL_Drawable_Registry);
  
  return 1;
}
