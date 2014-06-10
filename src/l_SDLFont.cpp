#include "l_SDLFont.hpp"

void lua_push_sdlfont(lua_State *L, SDLFont* sdlFont) {
    SDLFont** fontPtr = static_cast<SDLFont**>
	(lua_newuserdata(L, sizeof(SDLFont*)));
  
    *fontPtr = sdlFont;

    luaL_getmetatable(L, LUA_USERDATA_SDLFONT);
    lua_setmetatable(L, -2);
}

SDLFont* lua_to_sdlfont(lua_State *L, int index) {
    SDLFont* fontPtr = *static_cast<SDLFont**>
	(luaL_checkudata(L, index, LUA_USERDATA_SDLFONT));
    if (fontPtr == NULL) {
	luaL_error(L, "Provided userdata is not of type 'SDLFont'");
    }
    return fontPtr;
}

boolType lua_is_sdlfont(lua_State *L, int index) {
    if (lua_isuserdata(L, 1)) {
	SDLFont* fontPtr = *static_cast<SDLFont**>
	    (luaL_checkudata(L, index, LUA_USERDATA_SDLFONT));
	if (fontPtr != NULL) {
	    return true;
	}
	return false;
    }
    else {
	return false;
    }
}

static int l_isSDLFont(lua_State *L) {
    if (lua_is_sdlfont(L, 1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_SDLFont_getFontSize(lua_State *L) {
    return 0;
}

static int l_SDLFont_getFontColor(lua_State *L) {
    return 0;
}

static int l_SDLFont_setFontColor(lua_State *L) {
    return 0;
}

static int l_SDLFont_getRenderType(lua_State *L) {
    return 0;
}

static int l_SDLFont_setRenderType(lua_State *L) {
    return 0;
}

static int l_SDLFont_getStyle(lua_State *L) {
    return 0;
}

static int l_SDLFont_setStyle(lua_State *L) {
    return 0;
}

static int l_SDLFont_getOutline(lua_State *L) {
    return 0;
}

static int l_SDLFont_setOutline(lua_State *L) {
    return 0;
}

static int l_SDLFont_getHinting(lua_State *L) {
    return 0;
}

static int l_SDLFont_setHinting(lua_State *L) {
    return 0;
}

static int l_SDLFont_getKerning(lua_State *L) {
    return 0;
}

static int l_SDLFont_setKerning(lua_State *L) {
    return 0;
}

static int l_SDLFont_getMaxHeight(lua_State *L) {
    return 0;
}

static int l_SDLFont_getAscent(lua_State *L) {
    return 0;
}

static int l_SDLFont_getDescent(lua_State *L) {
    return 0;
}

static int l_SDLFont_getLineSkip(lua_State *L) {
    return 0;
}

static int l_SDLFont_isMonospace(lua_State *L) {
    return 0;
}

static int l_SDLFont_getFamilyName(lua_State *L) {
    return 0;
}

static int l_SDLFont_getFamilyStyle(lua_State *L) {
    return 0;
}

static int l_SDLFont_hasGlyph(lua_State *L) {
    return 0;
}

static int l_SDLFont_getGlyph(lua_State *L) {
    return 0;
}

static int l_SDLFont_calculateTextSize(lua_State *L) {
    return 0;
}

static int l_SDLFont_clone(lua_State *L) {
    return 0;
}


static const struct luaL_Reg l_SDL_Font_Registry [] = {
    {"isSDLFont", l_isSDLFont},
    {NULL, NULL}
};

static const struct luaL_Reg l_SDL_Font [] = {
    {"getFontSize", l_SDLFont_getFontSize},
    {"getFontColor", l_SDLFont_getFontColor},
    {"setFontColor", l_SDLFont_setFontColor},
    {"getRenderType", l_SDLFont_getRenderType},
    {"setRenderType", l_SDLFont_setRenderType},
    {"getStyle", l_SDLFont_getStyle},
    {"setStyle", l_SDLFont_setStyle},
    {"getOutline", l_SDLFont_getOutline},
    {"setOutline", l_SDLFont_setOutline},
    {"getHinting", l_SDLFont_getHinting},
    {"setHinting", l_SDLFont_setHinting},
    {"getKerning", l_SDLFont_getKerning},
    {"setKerning", l_SDLFont_setKerning},
    {"getMaxHeight", l_SDLFont_getMaxHeight},
    {"getAscent", l_SDLFont_getAscent},
    {"getDescent", l_SDLFont_getDescent},
    {"getLineSkip", l_SDLFont_getLineSkip},
    {"isMonoSpace", l_SDLFont_isMonospace},
    {"getFamilyName", l_SDLFont_getFamilyName},
    {"getFamilyStyle", l_SDLFont_getFamilyStyle},
    {"hasGlyph", l_SDLFont_hasGlyph},
    {"getGlyph", l_SDLFont_getGlyph},
    {"calculateTextSize", l_SDLFont_calculateTextSize},
    {"clone", l_SDLFont_clone},
    {NULL, NULL}
};

int luaopen_SDLFont(lua_State *L) {
    //SDLAssetManager
    luaL_newmetatable(L, LUA_USERDATA_SDLFONT);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_SDL_Font);

    luaL_register(L, KF_LUA_LIBNAME, l_SDL_Font_Registry);
  
    return 1;
}
