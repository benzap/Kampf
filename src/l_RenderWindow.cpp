#include "l_RenderWindow.hpp"

void lua_registerRenderWindow(lua_State *L,
			      RenderWindow* renderwindow) {
    //push our renderwindow point into the registry index table
    lua_pushstring(L, LUA_REGISTRY_RENDERWINDOW);
    lua_pushlightuserdata(L, (void *) renderwindow);
    lua_settable(L, LUA_REGISTRYINDEX);
}

boolType lua_hasRenderWindow(lua_State *L) {
    lua_pushstring(L, LUA_REGISTRY_RENDERWINDOW);
    lua_gettable(L, LUA_REGISTRYINDEX);
    if (lua_islightuserdata(L, -1)) {
	RenderWindow* renderwindow = (RenderWindow *) lua_touserdata(L, -1);
	if (renderwindow != nullptr) {
	    return true;
	}
    }
    return false;
}

RenderWindow* lua_getRenderWindow(lua_State *L) {
    lua_pushstring(L, LUA_REGISTRY_RENDERWINDOW);
    lua_gettable(L, LUA_REGISTRYINDEX);
    RenderWindow* renderwindow = (RenderWindow *) lua_touserdata(L, -1);
    return renderwindow;
}

void lua_pushrenderwindow(lua_State *L) {
    RenderWindow* renderwindow = nullptr;
    if (lua_hasRenderWindow(L)) {
	renderwindow = lua_getRenderWindow(L);
    }

    RenderWindow** rulePtr = static_cast<RenderWindow**>
	(lua_newuserdata(L, sizeof(RenderWindow*)));

    *rulePtr = renderwindow;

    luaL_getmetatable(L, LUA_USERDATA_RENDERWINDOW);
    lua_setmetatable(L, -2);
}

boolType lua_isrenderwindow(lua_State *L, int index) {
    if (lua_isuserdata(L, 1)) {
	auto chk = lua_isUserdataType(L, 1, LUA_USERDATA_RENDERWINDOW);
	return chk;
    }
    return false;
}

RenderWindow* lua_torenderwindow(lua_State *L, int index) {
    RenderWindow* renderwindow = *static_cast<RenderWindow**>
	(luaL_checkudata(L, index, LUA_USERDATA_RENDERWINDOW));
    if (renderwindow == NULL) {
	luaL_error(L, "Provided userdata is not of type 'RenderWindow'");
    }
    return renderwindow;
}
 
//kf.isRenderWindow(obj)
// params - obj = obj to test if it's the rule machine
// return - boolean, true if it's a rule machine
static int l_RenderWindow_isrenderwindow(lua_State *L) {
    if (lua_isrenderwindow(L, 1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_RenderWindow_getWindowSize(lua_State *L) {
    auto renderWindow = lua_torenderwindow(L, 1);
    return 0;
}

static int l_RenderWindow_setWindowSize(lua_State *L) {
    auto renderWindow = lua_torenderwindow(L, 1);
    return 0;
}

static int l_RenderWindow_getViewport(lua_State *L) {
    auto renderWindow = lua_torenderwindow(L, 1);
    return 0;
}

static int l_RenderWindow_setViewport(lua_State *L) {
    auto renderWindow = lua_torenderwindow(L, 1);
    return 0;
}

static int l_RenderWindow_getResolution(lua_State *L) {
    auto renderWindow = lua_torenderwindow(L, 1);
    return 0;
}

static int l_RenderWindow_setResolution(lua_State *L) {
    auto renderWindow = lua_torenderwindow(L, 1);
    return 0;
}

//kf module registered functions
static const struct luaL_Reg l_renderwindow_kampf [] = {
    {"isRenderWindow", l_RenderWindow_isrenderwindow},
    {NULL, NULL}
};
 
//RenderWindow methods
static const struct luaL_Reg l_renderwindow [] = {
    {"getWindowSize", l_RenderWindow_getWindowSize},
    {"setWindowSize", l_RenderWindow_setWindowSize},
    {"getViewport", l_RenderWindow_getViewport},
    {"setViewport", l_RenderWindow_setViewport},
    {"getResolution", l_RenderWindow_getResolution},
    {"setResolution", l_RenderWindow_setResolution},
    {NULL, NULL}
};

//luaopen_registered functions
int luaopen_renderwindow(lua_State *L, RenderWindow* renderwindow) {
    //Rule Machine
    luaL_newmetatable(L, LUA_USERDATA_RENDERWINDOW);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_renderwindow);

    luaL_register(L, KF_LUA_LIBNAME, l_renderwindow_kampf);

    //LOL DERP
    lua_registerRenderWindow(L, renderwindow);

    return 1;
}
