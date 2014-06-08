#include "l_ForceGenerator.hpp"

LuaForceGenerator* lua_pushluaforcegenerator(
					     lua_State *L,
					     LuaForceGenerator* luaforcegenerator) {

    LuaForceGenerator** luaforcegeneratorPtr = static_cast<LuaForceGenerator**>
	(lua_newuserdata(L, sizeof(LuaForceGenerator*)));
  
    //storing the address directly. Lua can be seen as a window,
    //looking in at the engine. This could be a good source for a lot
    //of problems.
    *luaforcegeneratorPtr = luaforcegenerator;

    luaL_getmetatable(L, LUA_USERDATA_LUAFORCEGENERATOR);
    lua_setmetatable(L, -2);  

    return luaforcegenerator;
}

LuaForceGenerator* lua_toluaforcegenerator(lua_State *L, int index) {
    LuaForceGenerator* luaforcegenerator = *static_cast<LuaForceGenerator**>
	(luaL_checkudata(L, index, LUA_USERDATA_LUAFORCEGENERATOR));
    if (luaforcegenerator == NULL) {
	luaL_error(L, "Provided userdata is not of type 'LuaForceGenerator'");
    }
    return luaforcegenerator;
}

boolType lua_isluaforcegenerator(lua_State* L, int index) {
    if (lua_isuserdata(L, index)) {
	auto chk = lua_isUserdataType(L, index, LUA_USERDATA_LUAFORCEGENERATOR);
	return chk;
    }
    return false;
}

static int l_LuaForceGenerator_LuaForceGenerator(lua_State *L) {
    stringType generatorName = luaL_checkstring(L, 1);
    LuaWrap_GeneratorUpdateFunction func = LuaWrap_GeneratorUpdateFunction(L, 2);
    
    auto luaGenerator = new LuaForceGenerator(generatorName, func);
    lua_pushluaforcegenerator(L, luaGenerator);

    return 1;
}

static int l_LuaForceGenerator_isLuaForceGenerator(lua_State *L) {
    if (lua_isluaforcegenerator(L, 1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_LuaForceGenerator_gc(lua_State *L) {
    return 0;
}

static int l_LuaForceGenerator_tostring(lua_State *L) {
    auto luaGenerator = lua_toluaforcegenerator(L, 1);
    stringType generatorName = luaGenerator->getName();
    stringType msg = "LuaForceGenerator:" + generatorName;
    lua_pushstring(L, msg.c_str());
    return 1;
}

static int l_LuaForceGenerator_getName(lua_State *L) {
    auto luaGenerator = lua_toluaforcegenerator(L, 1);
    stringType generatorName = luaGenerator->getName();
    lua_pushstring(L, generatorName.c_str());
    return 1;
}

static int l_LuaForceGenerator_registerComponent(lua_State *L) {
    auto luaGenerator = lua_toluaforcegenerator(L, 1);
    auto collisionComponent = lua_tocollisionComponent(L, 2);
    
    luaGenerator->registerComponent(collisionComponent);

    return 0;
}

static int l_LuaForceGenerator_unregisterComponent(lua_State *L) {
    auto luaGenerator = lua_toluaforcegenerator(L, 1);
    auto collisionComponent = lua_tocollisionComponent(L, 2);
    
    luaGenerator->unregisterComponent(collisionComponent);

    return 0;
}

static int l_LuaForceGenerator_hasRegisteredComponent(lua_State *L) {
    auto luaGenerator = lua_toluaforcegenerator(L, 1);
    auto collisionComponent = lua_tocollisionComponent(L, 2);

    if (luaGenerator->hasRegisteredComponent(collisionComponent)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }

    return 1;
}

static int l_LuaForceGenerator_getRegisteredComponents(lua_State *L) {
    auto luaGenerator = lua_toluaforcegenerator(L, 1);
    auto componentList = luaGenerator->getRegisteredComponents();

    //pre-allocating space for our components
    lua_createtable(L, componentList.size(), 0);
    int i = 0;
    for (auto component : componentList) {
	lua_pushcomponent(L, component);
	lua_rawseti(L, -2, i+1);
	i++;
    }
    
    return 1;
}

static const struct luaL_Reg l_LuaForceGenerator_Registry [] = {
    {"ForceGenerator", l_LuaForceGenerator_LuaForceGenerator},
    {"isForceGenerator", l_LuaForceGenerator_isLuaForceGenerator},
    {NULL, NULL}
};

static const struct luaL_Reg l_LuaForceGenerator [] = {
    {"__gc", l_LuaForceGenerator_gc},
    {"__tostring", l_LuaForceGenerator_tostring},
    {"getName", l_LuaForceGenerator_getName},
    {"registerComponent", l_LuaForceGenerator_registerComponent},
    {"unregisterComponent", l_LuaForceGenerator_unregisterComponent},
    {"hasRegisteredComponent", l_LuaForceGenerator_hasRegisteredComponent},
    {"getRegisteredComponents", l_LuaForceGenerator_getRegisteredComponents},
    {NULL, NULL}
};

int luaopen_luaforcegenerator(lua_State *L) {
    //LuaForceGenerator
    luaL_newmetatable(L, LUA_USERDATA_LUAFORCEGENERATOR);

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_LuaForceGenerator);
    
    luaL_register(L, KF_LUA_LIBNAME, l_LuaForceGenerator_Registry);
    return 1;
}
