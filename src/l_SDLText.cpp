#include "l_SDLText.hpp"

void lua_push_sdltext(lua_State *L, SDLText* sdlText) {
    SDLText** textPtr = static_cast<SDLText**>
	(lua_newuserdata(L, sizeof(SDLText*)));
  
    *textPtr = sdlText;

    luaL_getmetatable(L, LUA_USERDATA_SDLTEXT);
    lua_setmetatable(L, -2);
}

SDLText* lua_to_sdltext(lua_State *L, int index) {
    SDLText* textPtr = *static_cast<SDLText**>
	(luaL_checkudata(L, index, LUA_USERDATA_SDLTEXT));
    if (textPtr == NULL) {
	luaL_error(L, "Provided userdata is not of type 'SDLText'");
    }
    return textPtr;
}

boolType lua_is_sdltext(lua_State *L, int index) {
    if (lua_isuserdata(L, 1)) {
	SDLText* textPtr = *static_cast<SDLText**>
	    (luaL_checkudata(L, index, LUA_USERDATA_SDLTEXT));
	if (textPtr != NULL) {
	    return true;
	}
	return false;
    }
    else {
	return false;
    }
}

static int l_isSDLText(lua_State *L) {
    if (lua_is_sdltext(L, 1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_SDLText_draw(lua_State *L) {
    auto sdlText = lua_to_sdltext(L, 1);
    return 0;
}

static int l_SDLText_redraw(lua_State *L) {
    auto sdlText = lua_to_sdltext(L, 1);
    sdlText->redraw();
}

static int l_SDLText_getSize(lua_State *L) {
    auto sdlText = lua_to_sdltext(L, 1);
    

    return 0;
}

static int l_SDLText_appendText(lua_State *L) {
    auto sdlText = lua_to_sdltext(L, 1);
    stringType text = luaL_checkstring(L, 2);
    stringType fontname = luaL_checkstring(L, 3);
    
    sdlText->appendText(text, fontname);

    return 0;
}

static int l_SDLText_clearText(lua_State *L) {
    auto sdlText = lua_to_sdltext(L, 1);
    sdlText->clearText();
    return 0;
}

static int l_SDLText_getTextLength(lua_State *L) {
    auto sdlText = lua_to_sdltext(L, 1);
    int length = sdlText->getTextLength();
    lua_pushinteger(L, length);
    
    return 1;
}

static int l_SDLText_getTextSequence(lua_State *L) {
    auto sdlText = lua_to_sdltext(L, 1);
    luaL_error(L, "Not Implemented");
    return 0;
}

static int l_SDLText_setDefaultFont(lua_State *L) {
    auto sdlText = lua_to_sdltext(L, 1);
    stringType fontname = luaL_checkstring(L, 2);
    
    sdlText->setDefaultFont(fontname);
    return 0;
}

static const struct luaL_Reg l_SDL_Text_Registry [] = {
    {"isSDLText", l_isSDLText},
    {NULL, NULL}
};

static const struct luaL_Reg l_SDL_Text [] = {
    {"draw", l_SDLText_draw},
    {"redraw", l_SDLText_redraw},
    {"getSize", l_SDLText_getSize},
    {"appendText", l_SDLText_appendText},
    {"clearText", l_SDLText_clearText},
    {"getTextLength", l_SDLText_getTextLength},
    {"getTextSequence", l_SDLText_getTextSequence},
    {"setDefaultFont", l_SDLText_setDefaultFont},
    {NULL, NULL}
};

int luaopen_SDLText(lua_State *L) {
    //SDLAssetManager
    luaL_newmetatable(L, LUA_USERDATA_SDLTEXT);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_SDL_Text);

    lua_pop(L, 1);

    luaL_register(L, KF_LUA_LIBNAME, l_SDL_Text_Registry);
  
    return 1;
}
