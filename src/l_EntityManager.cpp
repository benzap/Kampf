#include "l_EntityManager.hpp"

EntityManager* lua_pushentityManager(lua_State *L) {
    auto entityManager = EntityManager::getInstance();

    EntityManager ** entityManagerPtr = static_cast<EntityManager**>
	(lua_newuserdata(L, sizeof(EntityManager*)));

    *entityManagerPtr = entityManager;
    
    luaL_getmetatable(L, LUA_USERDATA_ENTITYMANAGER);
    lua_setmetatable(L, -2);

    return entityManager;
}

EntityManager* lua_toentityManager(lua_State *L, int index) {
    EntityManager* entityManager = *static_cast<EntityManager**>
	(luaL_checkudata(L, index, LUA_USERDATA_ENTITYMANAGER));
    if (entityManager == NULL) {
	luaL_error(L, "Provided userdata is not of type 'EntityManager'");
    }
    return entityManager;
}

boolType lua_isentityManager(lua_State *L, int index) {
    if (lua_isuserdata(L, index)) {
	auto chk = lua_isUserdataType(L, index, LUA_USERDATA_ENTITYMANAGER); 
	return chk;
    }
    return false;
}

static int l_EntityManager_EntityManager(lua_State* L) {
    lua_pushentityManager(L);

    return 1;
}

static int l_EntityManager_isEntityManager(lua_State* L) {
    auto chk = lua_isentityManager(L, 1);
    if (chk) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_EntityManager_addEntity(lua_State *L) {
    auto entityManager = lua_toentityManager(L, 1);
    auto entity = lua_toentity(L, 2);
    entityManager->addEntity(entity);

    return 0;
}

static int l_EntityManager_getEntityByID(lua_State *L) {
    auto entityManager = lua_toentityManager(L, 1);
    incrementType inc = luaL_checkint(L, 2);
    auto entity = entityManager->getEntityByID(inc);
    if (entity != nullptr) {
	lua_pushentity(L, const_cast<Entity*>(entity));
    }
    else {
	lua_pushnil(L);
    }
    return 1;
}

static int l_EntityManager_getEntities(lua_State *L) {
    auto entityManager = lua_toentityManager(L, 1);
    auto entityList = entityManager->getEntities();

    lua_createtable(L, entityList.size(), 0);
    int i = 0;
    for (auto entity : entityList) {
	lua_pushentity(L, entity);
	lua_rawseti(L, -2, i+1);
	i++;
    }

    return 1;
}


static const struct luaL_Reg l_EntityManager_registry [] = {
    {"EntityManager", l_EntityManager_EntityManager},
    {"isEntityManager", l_EntityManager_isEntityManager},
    {NULL, NULL}
};

static const struct luaL_Reg l_EntityManager [] = {
    {"addEntity", l_EntityManager_addEntity},
    {"getEntityByID", l_EntityManager_getEntityByID},
    {"getEntities", l_EntityManager_getEntities},
    {NULL, NULL}
};

int luaopen_entityManager(lua_State *L) {
    luaL_newmetatable(L, LUA_USERDATA_ENTITYMANAGER);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_EntityManager);

    luaL_register(L, KF_LUA_LIBNAME, l_EntityManager_registry);

    return 1;
}

