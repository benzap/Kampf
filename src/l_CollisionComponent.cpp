#include "l_CollisionComponent.hpp"

CollisionComponent* lua_pushcollisioncomponent(
    lua_State *L,
    CollisionComponent* collisioncomponent = nullptr) {
    if (collisioncomponent == nullptr) {
	std::cerr << "Warning: CollisionComponent - this will not work, nullptr" << std::endl;
	collisioncomponent = new CollisionComponent("");
    }

    CollisionComponent** collisioncomponentPtr = static_cast<CollisionComponent**>
	(lua_newuserdata(L, sizeof(CollisionComponent*)));
  
    //storing the address directly. Lua can be seen as a window,
    //looking in at the engine. This could be a good source for a lot
    //of problems.
    *collisioncomponentPtr = collisioncomponent;

    luaL_getmetatable(L, LUA_USERDATA_COLLISIONCOMPONENT);
    lua_setmetatable(L, -2);  

    return collisioncomponent;
}

CollisionComponent* lua_tocollisioncomponent(lua_State *L, int index) {
    CollisionComponent* collisioncomponent = *static_cast<CollisionComponent**>
	(luaL_checkudata(L, index, LUA_USERDATA_COLLISIONCOMPONENT));
    if (collisioncomponent == NULL) {
	luaL_error(L, "Provided userdata is not of type 'CollisionComponent'");
    }
    return collisioncomponent;
}

boolType lua_iscollisionComponent(lua_State* L, int index) {
    if (lua_isuserdata(L, 1)) {
	auto chk = lua_isUserdataType(L, index, LUA_USERDATA_COLLISIONCOMPONENT);
	return chk;
    }
    return false;
}

static int l_CollisionComponent_CollisionComponent(lua_State *L) {
    stringType componentName = luaL_checkstring(L, 1);
    boolType isParent = lua_toboolean(L, 2);

    auto component = new CollisionComponent(
	componentName,
	!isParent);

    lua_pushcollisioncomponent(L, component);
    return 1;
}

static int l_CollisionComponent_isCollisionComponent(lua_State *L) {
    return 0;
}

static const struct luaL_Reg l_CollisionComponent_Registry [] = {
    {"CollisionComponent", l_CollisionComponent_CollisionComponent},
    {"isCollisionComponent", l_CollisionComponent_isCollisionComponent},
    {NULL, NULL}
};

static int l_CollisionComponent_gc(lua_State *L) {
    return 0;
}

static int l_CollisionComponent_tostring(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    stringType msg = "Component:COLLISION:";
    msg += component->getName();
    lua_pushstring(L, msg.c_str());
    return 1;
}

static int l_CollisionComponent_getFamily(lua_State *L) {
    lua_pushstring(L, "COLLISION");
    return 1;
}

static int l_CollisionComponent_createChild(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    stringType childComponentName = luaL_checkstring(L, 2);
    auto childComponent = component->createChild(childComponentName);
    CollisionComponent* childComponent_cast = static_cast<CollisionComponent*>
	(childComponent);
    lua_pushcollisioncomponent(L, childComponent_cast);
    return 1;
}

static const struct luaL_Reg l_CollisionComponent [] = {
    {"__gc", l_CollisionComponent_gc},
    {"__tostring", l_CollisionComponent_tostring},
    {"getFamily", l_CollisionComponent_getFamily},
    {"createChild", l_CollisionComponent_createChild},
    {NULL, NULL}
};

int luaopen_collisionComponent(lua_State *L) {
    //CollisionComponent
    luaL_newmetatable(L, LUA_USERDATA_COLLISIONCOMPONENT);
    lua_pushvalue(L, -1);
    luaL_getmetatable(L, LUA_USERDATA_ABSTRACTCOMPONENT);
    lua_setmetatable(L, -2);  
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_CollisionComponent);

    luaL_register(L, KF_LUA_LIBNAME, l_CollisionComponent_Registry);
    return 1;
}
