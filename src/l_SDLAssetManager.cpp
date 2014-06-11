#include "l_SDLAssetManager.hpp"

void lua_pushSDL_AM(lua_State* L, SDLAssetManager* sdlasset = nullptr) {
    if (sdlasset == nullptr) {
	sdlasset = SDLAssetManager::getInstance();
    }
    SDLAssetManager** assetPtr = static_cast<SDLAssetManager**>
	(lua_newuserdata(L, sizeof(SDLAssetManager*)));

    *assetPtr = sdlasset;

    luaL_getmetatable(L, LUA_USERDATA_SDLASSETMANAGER);
    lua_setmetatable(L, -2);  
}

SDLAssetManager* lua_toSDL_AM(lua_State* L, int index) {
    SDLAssetManager* assetPtr = *static_cast<SDLAssetManager**>
	(luaL_checkudata(L, index, LUA_USERDATA_SDLASSETMANAGER));
    if (assetPtr == NULL) {
	luaL_error(L, "Provided userdata is not of type 'SDLAssetManager'");
    }
    return SDLAssetManager::getInstance();
}

boolType lua_isSDL_AM(lua_State *L, int index) {
    if (lua_isuserdata(L, 1)) {
	SDLAssetManager* assetPtr = *static_cast<SDLAssetManager**>
	    (luaL_checkudata(L, index, LUA_USERDATA_SDLASSETMANAGER));
	if (assetPtr != NULL) {
	    return true;
	}
	return false;
    }
    else {
	return false;
    }
}

static int l_SDL_AM_SDL_AM(lua_State *L) {
    lua_pushSDL_AM(L);

    return 1;
}

static int l_SDL_AM_isSDL_AM(lua_State *L) {
    if (lua_isSDL_AM(L, 1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_SDL_AM_addBMP(lua_State *L) {
    auto sdlasset = lua_toSDL_AM(L, 1);
    stringType name = luaL_checkstring(L, 2);
    stringType filename = luaL_checkstring(L, 3);
    auto drawable = sdlasset->addBMP(name, filename);

    if (lua_istable(L, 4)) {
	lua_getfield(L, 4, "w");
	floatType w = luaL_checknumber(L, -1);
	lua_getfield(L, 4, "h");
	floatType h = luaL_checknumber(L, -1);
	lua_getfield(L, 4, "x");
	floatType x = luaL_checknumber(L, -1);
	lua_getfield(L, 4, "y");
	floatType y = luaL_checknumber(L, -1);
	lua_pop(L, 4);
	drawable->setRect(w,h,x,y);
    }
    lua_push_sdldrawable(L, drawable);

    return 1;
}

static int l_SDL_AM_addImage(lua_State *L) {
    auto sdlasset = lua_toSDL_AM(L, 1);
    stringType name = luaL_checkstring(L, 2);
    stringType filename = luaL_checkstring(L, 3);
    auto drawable = sdlasset->addImage(name, filename);

    if (lua_istable(L, 4)) {
	lua_getfield(L, 4, "w");
	floatType w = luaL_checknumber(L, -1);
	lua_getfield(L, 4, "h");
	floatType h = luaL_checknumber(L, -1);
	lua_getfield(L, 4, "x");
	floatType x = luaL_checknumber(L, -1);
	lua_getfield(L, 4, "y");
	floatType y = luaL_checknumber(L, -1);
	lua_pop(L, 4);
	drawable->setRect(w,h,x,y);
    }
    lua_push_sdldrawable(L, drawable);

    return 1;
}


static int l_SDL_AM_getDrawable(lua_State *L) {
    auto sdlasset = lua_toSDL_AM(L, 1);
    stringType name = luaL_checkstring(L, 2);
  
    auto drawable = sdlasset->getDrawable(name);
    lua_push_sdldrawable(L, drawable);

    return 1;
}

static int l_SDL_AM_deleteDrawable(lua_State *L) {
    auto sdlasset = lua_toSDL_AM(L, 1);
    stringType name = luaL_checkstring(L, 2);

    sdlasset->removeDrawable(name);
  
    return 0;
}

static int l_SDL_AM_hasDrawable(lua_State *L) {
    auto sdlasset = lua_toSDL_AM(L, 1);
    stringType name = luaL_checkstring(L, 2);
    if (sdlasset->hasDrawable(name)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_SDL_AM_copyDrawable(lua_State *L) {
    auto sdlasset = lua_toSDL_AM(L, 1);
    stringType srcName = luaL_checkstring(L, 2);
    stringType destName = luaL_checkstring(L, 3);

    auto drawable = sdlasset->copyDrawable(srcName, destName);
    lua_push_sdldrawable(L, drawable);
    
    return 1;
}

static int l_SDL_AM_addText(lua_State *L) {
    auto sdlasset = lua_toSDL_AM(L, 1);
    stringType textName = luaL_checkstring(L, 2);
    
    auto sdlText = sdlasset->addText(textName);

    lua_push_sdltext(L, sdlText);
    return 1;
}

static int l_SDL_AM_hasText(lua_State *L) {
    auto sdlasset = lua_toSDL_AM(L, 1);
    stringType textName = luaL_checkstring(L, 2);

    boolType exists = sdlasset->hasText(textName);
    
    if (exists) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }

    return 1;
}

static int l_SDL_AM_getText(lua_State *L) {
    auto sdlasset = lua_toSDL_AM(L, 1);
    stringType textName = luaL_checkstring(L, 2);

    auto sdlText = sdlasset->getText(textName);

    lua_push_sdltext(L, sdlText);
    return 1;
}

static int l_SDL_AM_removeText(lua_State *L) {
    auto sdlasset = lua_toSDL_AM(L, 1);
    stringType textName = luaL_checkstring(L, 2);

    sdlasset->removeText(textName);
    return 0;
}

static const struct luaL_Reg l_SDL_AM_Registry [] = {
    {"SDLAssetManager", l_SDL_AM_SDL_AM},
    {"isSDLAssetManager", l_SDL_AM_isSDL_AM},
    {NULL, NULL}
};

static const struct luaL_Reg l_SDL_AM [] = {
    {"addBMP", l_SDL_AM_addBMP},
    {"addImage", l_SDL_AM_addImage},
    {"getDrawable", l_SDL_AM_getDrawable},
    {"deleteDrawable", l_SDL_AM_deleteDrawable},
    {"hasDrawable", l_SDL_AM_hasDrawable},
    {"copyDrawable", l_SDL_AM_copyDrawable},
    {"addText", l_SDL_AM_addText},
    {"hasText", l_SDL_AM_hasText},
    {"getText", l_SDL_AM_getText},
    {"removeText", l_SDL_AM_removeText},
    {NULL, NULL}
};

int luaopen_SDL_AM(lua_State *L) {
    //SDLAssetManager
    luaL_newmetatable(L, LUA_USERDATA_SDLASSETMANAGER);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_SDL_AM);

    lua_pop(L, 1);

    luaL_register(L, KF_LUA_LIBNAME, l_SDL_AM_Registry);

    return 1;
}
