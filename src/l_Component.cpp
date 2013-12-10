#include "l_Component.hpp"

Component* lua_pushcomponent(lua_State *L, Component* component) {
    return nullptr;
}

Component* lua_tocomponent(lua_State *L, int index) {
    Component* component = nullptr;
    if (lua_isabstractComponent(L, 1)) {
	component = *static_cast<AbstractComponent**>
	    (luaL_checkudata(L, index, LUA_USERDATA_ABSTRACTCOMPONENT));
    }
    else if (lua_iscollisionComponent(L, 1)) {
	component = *static_cast<AbstractComponent**>
	    (luaL_checkudata(L, index, LUA_USERDATA_COLLISIONCOMPONENT));
    }
    else {
	luaL_error(L, "ERROR: Userdata is not a component type");
    }
    return component;
}

//a general check on whether a userdata is a component
boolType lua_iscomponent(lua_State *L, int index) {
    if (lua_isuserdata(L, index)) {
	//check if it's an abstract component
	if (lua_isUserdata(L, 1, LUA_USERDATA_ABSTRACTCOMPONENT) ||
	    lua_isUserdata(L, 1, LUA_USERDATA_COLLISIONCOMPONENT)) {
	    return true;
	}
    }
    return false;
}

boolType lua_isUserdata(lua_State *L, int index,
			const char *tname) {
    int chk = lua_getmetatable(L, index);
    if (!chk) { return false; }
    lua_getfield(L, LUA_REGISTRYINDEX, tname);
    if (lua_equal(L, -1, -2)) {
	return true;
    }
    return false;
}

static int l_Component_isComponent(lua_State *L) {
    if (lua_iscomponent(L, 1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static const struct luaL_Reg l_Component_Registry [] = {
    {"isComponent", l_Component_isComponent},
    {NULL, NULL}
};

int luaopen_component(lua_State *L) {
    luaL_register(L, KF_LUA_LIBNAME, l_Component_Registry);
    return 1;
}
