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
    auto font = lua_to_sdlfont(L, 1);
    int fontSize = font->getFontSize();
    lua_pushinteger(L, fontSize);
    return 1;
}

static int l_SDLFont_getFontColor(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    FontColor fontColor = font->getFontColor();
    
    lua_newtable(L);
    lua_pushinteger(L, fontColor.r);
    lua_setfield(L, -2, "r");

    lua_pushinteger(L, fontColor.g);
    lua_setfield(L, -2, "g");

    lua_pushinteger(L, fontColor.b);
    lua_setfield(L, -2, "b");

    lua_pushinteger(L, fontColor.a);
    lua_setfield(L, -2, "a");

    return 1;
}

static int l_SDLFont_setFontColor(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    auto redColor = luaL_checkint(L, 2);
    auto greenColor = luaL_checkint(L, 3);
    auto blueColor = luaL_checkint(L, 4);
    auto alpha = luaL_optint(L, 5, 255);

    FontColor fontColor;
    fontColor.r = redColor;
    fontColor.g = greenColor;
    fontColor.b = blueColor;
    fontColor.a = alpha;

    font->setFontColor(fontColor);

    return 0;
}

static int l_SDLFont_getRenderType(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);

    enumFontRenderType renderType = font->getRenderType();
    switch(renderType) {
    case enumFontRenderType::SOLID:
	lua_pushstring(L, "SOLID");
	break;
    case enumFontRenderType::SHADED:
	lua_pushstring(L, "SHADED");
	break;
    case enumFontRenderType::BLENDED:
	lua_pushstring(L, "BLENDED");
	break;
    }

    return 1;
}

static int l_SDLFont_setRenderType(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    stringType renderType = luaL_checkstring(L, 2);
    
    if (renderType == "SOLID") {
	font->setRenderType(enumFontRenderType::SOLID);
    }
    else if (renderType == "SHADED") {
	font->setRenderType(enumFontRenderType::SHADED);
    }
    else if (renderType == "BLENDED") {
	font->setRenderType(enumFontRenderType::BLENDED);
    }
    else {
	std::cout << "Provided RenderType: " << renderType << std::cout;
	luaL_error(L, "Provided renderType is unknown: SOLID, SHADED, BLENDED");
    }
    return 0;
}

static int l_SDLFont_getStyle(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    FontStyle fontStyle = font->getStyle();
    
    lua_newtable(L);
    lua_pushboolean(L, (fontStyle.bBold) ? 1 : 0);
    lua_setfield(L, -2, "bold");

    lua_pushboolean(L, (fontStyle.bItalic) ? 1 : 0);
    lua_setfield(L, -2, "italic");    

    lua_pushboolean(L, (fontStyle.bUnderline) ? 1 : 0);
    lua_setfield(L, -2, "underline");

    lua_pushboolean(L, (fontStyle.bStrikethrough) ? 1 : 0);
    lua_setfield(L, -2, "strikethrough");

    return 0;
}

static int l_SDLFont_setStyle(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);

    FontStyle fontStyle = font->getStyle();

    if (lua_istable(L, 2)) {
	//bold
	lua_getfield(L, -1, "bold");
	if (!lua_isnil(L, -1)) fontStyle.bBold = lua_toboolean(L, -1);
	lua_pop(L, 1);
	
	//italic
	lua_getfield(L, -1, "italic");
	if (!lua_isnil(L, -1)) fontStyle.bItalic = lua_toboolean(L, -1);
	lua_pop(L, 1);

	//underline
	lua_getfield(L, -1, "underline");
	if (!lua_isnil(L, -1)) fontStyle.bUnderline = lua_toboolean(L, -1);
	lua_pop(L, 1);

	//strikethrough
	lua_getfield(L, -1, "strikethrough");
	if (!lua_isnil(L, -1)) fontStyle.bStrikethrough = lua_toboolean(L, -1);
	lua_pop(L, 1);

	font->setStyle(fontStyle);
    }
    else {
	luaL_error(L, "setStyle function takes a table as its second argument");
    }

    return 0;
}

static int l_SDLFont_getOutline(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    int outline = font->getOutline();
    lua_pushinteger(L, outline);
    
    return 1;
}

static int l_SDLFont_setOutline(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    int outline = luaL_checkint(L, 2);
    font->setOutline(outline);
    return 0;
}

static int l_SDLFont_getHinting(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    enumFontHintingType fontHinting = font->getHinting();
    switch(fontHinting) {
    case enumFontHintingType::NORMAL:
	lua_pushstring(L, "NORMAL");
	break;
    case enumFontHintingType::LIGHT:
	lua_pushstring(L, "LIGHT");
	break;
    case enumFontHintingType::MONO:
	lua_pushstring(L, "MONO");
	break;
    case enumFontHintingType::NONE:
	lua_pushstring(L, "NONE");
	break;
    }
    
    return 1;
}

static int l_SDLFont_setHinting(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    stringType fontHinting = luaL_checkstring(L, 2);

    if (fontHinting == "NORMAL") {
	font->setHinting(enumFontHintingType::NORMAL);
    }
    else if (fontHinting == "LIGHT") {
	font->setHinting(enumFontHintingType::LIGHT);
    }
    else if (fontHinting == "MONO") {
	font->setHinting(enumFontHintingType::MONO);
    }
    else if (fontHinting == "NONE") {
	font->setHinting(enumFontHintingType::NONE);
    }
    else {
	luaL_error(L, "Incorrect hinting provided: (NORMAL, LIGHT, MONO, NONE)");
    }
    
    return 0;
}

static int l_SDLFont_getKerning(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    boolType bKerning = font->getKerning();

    lua_pushboolean(L, (bKerning) ? 1 : 0);
    return 1;
}

static int l_SDLFont_setKerning(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    int bKerning = lua_toboolean(L, 2);
    
    font->setKerning((boolType) bKerning);
    return 0;
}

static int l_SDLFont_getMaxHeight(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    int maxHeight = font->getMaxHeight();

    lua_pushinteger(L, maxHeight);
    return 1;
}

static int l_SDLFont_getAscent(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    int fontAscent = font->getAscent();

    lua_pushinteger(L, fontAscent);
    return 1;
}

static int l_SDLFont_getDescent(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    int fontDescent = font->getDescent();

    lua_pushinteger(L, fontDescent);
    return 0;
}

static int l_SDLFont_getLineSkip(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    int lineSkip = font->getLineSkip();

    lua_pushinteger(L, lineSkip);
    return 1;
}

static int l_SDLFont_isMonospace(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    boolType isMonospace = font->isMonospace();
    
    lua_pushinteger(L, (isMonospace) ? 1 : 0);
    return 1;
}

static int l_SDLFont_getFamilyName(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    stringType familyName = font->getFamilyName();
    
    lua_pushstring(L, familyName.c_str());
    return 1;
}

static int l_SDLFont_getFamilyStyle(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    stringType familyStyle = font->getFamilyStyle();

    lua_pushstring(L, familyStyle.c_str());
    return 1;
}

static int l_SDLFont_hasGlyph(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    return 0;
}

static int l_SDLFont_getGlyph(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    luaL_error(L, "Not Implemented");
    return 0;
}

static int l_SDLFont_calculateTextSize(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    luaL_error(L, "Not Implemented");
    return 0;
}

static int l_SDLFont_clone(lua_State *L) {
    auto font = lua_to_sdlfont(L, 1);
    luaL_error(L, "Not Implemented");
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

    lua_pop(L, 1);

    luaL_register(L, KF_LUA_LIBNAME, l_SDL_Font_Registry);
  
    return 1;
}
