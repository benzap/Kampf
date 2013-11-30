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
    lua_pushentity(L);

    return 1;
}

static int l_Entity_isEntity(lua_State* L) {
    auto chk = lua_isentity(L, 1);
    if (chk) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_Entity_getName(lua_State* L) {
    auto entity = lua_toentity(L, 1);
    auto name = entity->getName();
    lua_pushstring(L, name.c_str());
    return 1;
}

static int l_Entity_setName(lua_State* L) {
    auto entity = lua_toentity(L, 1);
    auto name = luaL_checkstring(L, 2);
    
    entity->setName(stringType(name));
    return 0;
}

static int l_Entity_getID(lua_State* L) {
    auto entity = lua_toentity(L, 1);
    auto ID = entity->getID();
    lua_pushnumber(L, ID);
    return 1;
}

static int l_Entity_getComponents(lua_State* L) {
    auto entity = lua_toentity(L, 1);
    auto componentList = entity->getComponentContainer();

    //pre-allocating space for our components
    //lua_newtable(L, componentList.size(), 0);

    //TODO: implement component types in lua
    lua_pushnil(L);
    return 1;
}

static int l_Entity_getComponentsByFamily(lua_State* L) {
    auto entity = lua_toentity(L, 1);
    auto familyString = stringType(luaL_checkstring(L, 2));
    
    partialComponentListType componentList;
    if (familyString == "abstract") {
	componentList = entity->getComponentsByFamily(
	    enumComponentFamily::ABSTRACT);
    }
    else if (familyString == "collision") {
	componentList = entity->getComponentsByFamily(
	    enumComponentFamily::COLLISION);
    }
    else if (familyString == "physics") {
	componentList = entity->getComponentsByFamily(
	    enumComponentFamily::PHYSICS);
    }
    else if (familyString == "graphics") {
	componentList = entity->getComponentsByFamily(
	    enumComponentFamily::GRAPHICS);
    }
    else if (familyString == "custom") {
	componentList = entity->getComponentsByFamily(
	    enumComponentFamily::CUSTOM);
    }
    else {
	luaL_error(L, "Incorrect family type");
    }
    
    //TODO: create component lua type
    //lua_createtable(L, componentList.size(), 0);
    lua_pushnil(L);
    return 1;
}

static int l_Entity_getComponentsByName(lua_State* L) {
    auto entity = lua_toentity(L, 1);
    stringType componentName = luaL_checkstring(L, 2);

    auto componentList = entity->getComponentsByName(componentName);
    
    //TODO: create lua component bindings
    //lua_createtable(L, componentList.size(), 0);
    lua_pushnil(L);
    return 1;
}

static int l_Entity_addComponent(lua_State* L) {
    auto entity = lua_toentity(L, 1);
    //TODO: implement lua component type
    //auto component = lua_tocomponent(L, 2);
				     
				     
}

static const struct luaL_Reg l_Entity_registry [] = {
    {"Entity", l_Entity_Entity},
    {"isEntity", l_Entity_isEntity},
    {NULL, NULL}
};

static const struct luaL_Reg l_Entity [] = {
    {"getName", l_Entity_getName},
    {"setName", l_Entity_setName},
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

