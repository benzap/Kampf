#include "l_PhysicsRegistry.hpp"

PhysicsRegistry* lua_pushphysicsregistry(lua_State *L) {
    auto physicsRegistry = PhysicsRegistry::getInstance();

    PhysicsRegistry ** physicsregistryPtr = static_cast<PhysicsRegistry**>
	(lua_newuserdata(L, sizeof(PhysicsRegistry*)));

    *physicsregistryPtr = physicsRegistry;
    
    luaL_getmetatable(L, LUA_USERDATA_PHYSICSREGISTRY);
    lua_setmetatable(L, -2);

    return physicsRegistry;
}

PhysicsRegistry* lua_tophysicsregistry(lua_State *L, int index) {
    PhysicsRegistry* physicsRegistry = *static_cast<PhysicsRegistry**>
	(luaL_checkudata(L, index, LUA_USERDATA_PHYSICSREGISTRY));
    if (physicsRegistry == NULL) {
	luaL_error(L, "Provided userdata is not of type 'PhysicsRegistry'");
    }
    return physicsRegistry;
}

boolType lua_isphysicsregistry(lua_State *L, int index) {
    if (lua_isuserdata(L, index)) {
	auto chk = lua_isUserdataType(L, index, LUA_USERDATA_PHYSICSREGISTRY); 
	return chk;
    }
    return false;
}

static int l_PhysicsRegistry_PhysicsRegistry(lua_State* L) {
    lua_pushphysicsregistry(L);

    return 1;
}

static int l_PhysicsRegistry_isPhysicsRegistry(lua_State* L) {
    auto chk = lua_isphysicsregistry(L, 1);
    if (chk) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_PhysicsRegistry_addForceGenerator(lua_State *L) {
    auto physicsRegistry = lua_tophysicsregistry(L, 1);
    auto luaGenerator = lua_toluaforcegenerator(L, 2);

    physicsRegistry->addForceGenerator(luaGenerator);

    return 0;
}

static int l_PhysicsRegistry_removeForceGenerator(lua_State *L) {
    auto physicsRegistry = lua_tophysicsregistry(L, 1);
    auto luaGenerator = lua_toAbstractForceGenerator(L, 2);
    
    physicsRegistry->removeForceGenerator(luaGenerator);

    return 0;
}

static int l_PhysicsRegistry_getForceGenerator(lua_State *L) {
    auto physicsRegistry = lua_tophysicsregistry(L, 1);
    auto generatorName = luaL_checkstring(L, 2);

    auto abstractGenerator = physicsRegistry->getForceGenerator(generatorName);

    lua_pushAbstractForceGenerator(L, abstractGenerator);

    return 1;
}

static int l_PhysicsRegistry_hasForceGenerator(lua_State *L) {
    auto physicsRegistry = lua_tophysicsregistry(L, 1);
    auto generatorName = luaL_checkstring(L, 2);

    if (physicsRegistry->hasForceGenerator(generatorName)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }

    return 1;
}


static const struct luaL_Reg l_PhysicsRegistry_registry [] = {
    {"PhysicsRegistry", l_PhysicsRegistry_PhysicsRegistry},
    {"isPhysicsRegistry", l_PhysicsRegistry_isPhysicsRegistry},
    {NULL, NULL}
};

static const struct luaL_Reg l_PhysicsRegistry [] = {
    {"addForceGenerator", l_PhysicsRegistry_addForceGenerator},
    {"removeForceGenerator", l_PhysicsRegistry_removeForceGenerator},
    {"getForceGenerator", l_PhysicsRegistry_getForceGenerator},
    {"hasForceGenerator", l_PhysicsRegistry_hasForceGenerator},
    {NULL, NULL}
};

int luaopen_physicsregistry(lua_State *L) {
    luaL_newmetatable(L, LUA_USERDATA_PHYSICSREGISTRY);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_PhysicsRegistry);

    luaL_register(L, KF_LUA_LIBNAME, l_PhysicsRegistry_registry);

    return 1;
}

