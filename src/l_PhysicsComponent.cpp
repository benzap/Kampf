#include "l_PhysicsComponent.hpp"

PhysicsComponent* lua_pushphysicsComponent(
    lua_State *L,
    PhysicsComponent* physicscomponent = nullptr) {
    if (physicscomponent == nullptr) {
	std::cerr << "Warning: PhysicsComponent - this will not work, nullptr" << std::endl;
	physicscomponent = new PhysicsComponent("");
    }

    PhysicsComponent** physicscomponentPtr = static_cast<PhysicsComponent**>
	(lua_newuserdata(L, sizeof(PhysicsComponent*)));
  
    //storing the address directly. Lua can be seen as a window,
    //looking in at the engine. This could be a good source for a lot
    //of problems.
    *physicscomponentPtr = physicscomponent;

    luaL_getmetatable(L, LUA_USERDATA_PHYSICSCOMPONENT);
    lua_setmetatable(L, -2);  

    return physicscomponent;
}

PhysicsComponent* lua_tophysicsComponent(lua_State *L, int index) {
    PhysicsComponent* physicscomponent = *static_cast<PhysicsComponent**>
	(luaL_checkudata(L, index, LUA_USERDATA_PHYSICSCOMPONENT));
    if (physicscomponent == NULL) {
	luaL_error(L, "Provided userdata is not of type 'PhysicsComponent'");
    }
    return physicscomponent;
}

boolType lua_isphysicsComponent(lua_State* L, int index) {
    if (lua_isuserdata(L, index)) {
	auto chk = lua_isUserdataType(L, index, LUA_USERDATA_PHYSICSCOMPONENT);
	return chk;
    }
    return false;
}

static int l_PhysicsComponent_PhysicsComponent(lua_State *L) {
    stringType componentName = luaL_checkstring(L, 1);
    boolType isParent = lua_toboolean(L, 2);

    auto component = new PhysicsComponent(
	componentName,
	!isParent);

    lua_pushphysicsComponent(L, component);
    return 1;
}

static int l_PhysicsComponent_isPhysicsComponent(lua_State *L) {
    return 0;
}

static const struct luaL_Reg l_PhysicsComponent_Registry [] = {
    {"PhysicsComponent", l_PhysicsComponent_PhysicsComponent},
    {"isPhysicsComponent", l_PhysicsComponent_isPhysicsComponent},
    {NULL, NULL}
};

static int l_PhysicsComponent_gc(lua_State *L) {
    return 0;
}

static int l_PhysicsComponent_tostring(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    stringType msg = "Component:PHYSICS:";
    msg += component->getName();
    lua_pushstring(L, msg.c_str());
    return 1;
}

static int l_PhysicsComponent_getFamily(lua_State *L) {
    lua_pushstring(L, "PHYSICS");
    return 1;
}

static int l_PhysicsComponent_createChild(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    stringType childComponentName = luaL_checkstring(L, 2);
    auto childComponent = component->createChild(childComponentName);
    PhysicsComponent* childComponent_cast = static_cast<PhysicsComponent*>
	(childComponent);
    lua_pushphysicsComponent(L, childComponent_cast);
    return 1;
}

static const struct luaL_Reg l_PhysicsComponent [] = {
    {"__gc", l_PhysicsComponent_gc},
    {"__tostring", l_PhysicsComponent_tostring},
    {"getFamily", l_PhysicsComponent_getFamily},
    {"createChild", l_PhysicsComponent_createChild},
    {NULL, NULL}
};

int luaopen_physicsComponent(lua_State *L) {
    //PhysicsComponent
    luaL_newmetatable(L, LUA_USERDATA_PHYSICSCOMPONENT);
    lua_pushvalue(L, -1);
    luaL_getmetatable(L, LUA_USERDATA_ABSTRACTCOMPONENT);
    lua_setmetatable(L, -2);  
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_PhysicsComponent);

    luaL_register(L, KF_LUA_LIBNAME, l_PhysicsComponent_Registry);
    return 1;
}
