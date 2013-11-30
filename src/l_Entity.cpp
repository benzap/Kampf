#include "l_Entity.hpp"

Entity* lua_pushentity(lua_State *L, Entity* entity = nullptr) {
    if (entity == nullptr) {
	//a new entity is created with no name
	//TODO: give the entity a unique hash
	entity = new MainEntity("");
    }

    Entity ** entityPtr = static_cast<Entity**>
	(lua_newuserdata(L, sizeof(Entity*)));

    *entityPtr = entity;
    
    luaL_getmetatable(L, LUA_USERDATA_ENTITY);
    lua_setmetatable(L, -2);

    return entity;
}

Entity* lua_toentity(lua_State *L, int index) {
    Entity* entity = *static_cast<Entity**>
	(luaL_checkudata(L, index, LUA_USERDATA_ENTITY));
    if (entity == NULL) {
	luaL_error(L, "Provided userdata is not of type 'Entity'");
    }
    return entity;
}

boolType lua_isentity(lua_State *L, int index) {
    if (lua_isuserdata(L, 1)) {
	Entity* entity = *static_cast<Entity**>
	    (luaL_checkudata(L, index, LUA_USERDATA_ENTITY)); 
	if (entity != NULL) {
	    return true;
	}
	return false;
    }
    return false;
}

static int l_Entity_Entity(lua_State* L) {

}

static int l_Entity_isEntity(lua_State* L) {

}

static int l_Entity_getName(lua_State* L) {

}

static int l_Entity_setName(lua_State* L) {

}

static int l_Entity_getType(lua_State* L) {

}

static int l_Entity_getID(lua_State* L) {

}

static int l_Entity_getComponents(lua_State* L) {

}

static int l_Entity_getComponentsByFamily(lua_State* L) {

}

static int l_Entity_getComponentsByName(lua_State* L) {

}

static int l_Entity_addComponent(lua_State* L) {

}

static const struct luaL_Reg l_Entity_registry [] = {
    {"Entity", l_Entity_Entity},
    {"isEntity", l_Entity_isEntity},
    {NULL, NULL}
};

static const struct luaL_Reg l_Entity [] = {
    {"getName", l_Entity_getName},
    {"setName", l_Entity_setName},
    {"getType", l_Entity_getType},
    {"getID", l_Entity_getID},
    {"getComponents", l_Entity_getComponents},
    {"getComponentsByFamily", l_Entity_getComponentsByFamily},
    {"getComponentsByName", l_Entity_getComponentsByName},
    {"addComponent", l_Entity_addComponent},
    {NULL, NULL}
};

int luaopen_entity(lua_State *L) {
    luaL_newmetatable(L, LUA_USERDATA_ENTITY);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_Entity);

    luaL_register(L, KF_LUA_LIBNAME, l_Entity_registry);

    return 1;
}

