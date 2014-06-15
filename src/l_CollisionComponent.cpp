#include "l_CollisionComponent.hpp"

CollisionComponent* lua_pushcollisionComponent(
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

CollisionComponent* lua_tocollisionComponent(lua_State *L, int index) {
    CollisionComponent* collisioncomponent = *static_cast<CollisionComponent**>
	(luaL_checkudata(L, index, LUA_USERDATA_COLLISIONCOMPONENT));
    if (collisioncomponent == NULL) {
	luaL_error(L, "Provided userdata is not of type 'CollisionComponent'");
    }
    return collisioncomponent;
}

boolType lua_iscollisionComponent(lua_State* L, int index) {
    if (lua_isuserdata(L, index)) {
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

    lua_pushcollisionComponent(L, component);
    return 1;
}

static int l_CollisionComponent_isCollisionComponent(lua_State *L) {
    if (lua_iscollisionComponent(L, 1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
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
    lua_pushcollisionComponent(L, childComponent_cast);
    return 1;
}

static int l_CollisionComponent_setPhysicsRelation(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    
    //get the physics component
    auto p_component = lua_tocomponent(L, 2);
    auto physicsComponent = static_cast<PhysicsComponent*>
	(p_component);
    collisionComponent->setPhysicsRelation(physicsComponent);
    return 0;
}

static int l_CollisionComponent_getPhysicsRelation(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);

    auto p_component = collisionComponent->getPhysicsRelation();
    if (p_component != nullptr) {
	lua_pushphysicsComponent(L, p_component);
    }
    else {
	lua_pushnil(L);
    }
    return 1;
}

static int l_CollisionComponent_setOffset(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    auto vector = lua_tovector(L, 2);
    collisionComponent->setOffset(*vector);
    return 0;
}

static int l_CollisionComponent_getOffset(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    auto vector = collisionComponent->getOffset();
    lua_pushvector(L, new Vector3(vector));
    return 1;
}

static int l_CollisionComponent_setOrigin(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    auto vector = lua_tovector(L, 2);
    collisionComponent->setOrigin(*vector);
    return 0;
}

static int l_CollisionComponent_getOrigin(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    auto vector = collisionComponent->getOrigin();
    lua_pushvector(L, new Vector3(vector));
    return 1;
}

static int l_CollisionComponent_setOrientation(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    auto quat = lua_toquaternion(L, 2);
    collisionComponent->setOrientation(*quat);
    return 0;
}

static int l_CollisionComponent_getOrientation(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    auto quat = collisionComponent->getOrientation();
    lua_pushquaternion(L, new Quaternion(quat));
    return 1;
}


static int l_CollisionComponent_setType(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    stringType typeString = luaL_checkstring(L, 2);
    collisionComponent->setCollisionTypeString(typeString);
    return 0;
}

static int l_CollisionComponent_getType(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);\
    auto typeString = collisionComponent->getCollisionTypeString();
    lua_pushstring(L, typeString.c_str());
    return 1;
}

static int l_CollisionComponent_setRadius(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    floatType floatValue = luaL_checknumber(L, 2);
    collisionComponent->setRadius(floatValue);
    return 0;
}

static int l_CollisionComponent_getRadius(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    floatType floatValue = collisionComponent->getRadius();
    lua_pushnumber(L, floatValue);
    return 1;
}

static int l_CollisionComponent_setWidth(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    floatType floatValue = luaL_checknumber(L, 2);
    collisionComponent->setWidth(floatValue);
    return 0;
}

static int l_CollisionComponent_getWidth(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    floatType floatValue = collisionComponent->getWidth();
    lua_pushnumber(L, floatValue);
    return 1;
}

static int l_CollisionComponent_setHeight(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    floatType floatValue = luaL_checknumber(L, 2);
    collisionComponent->setHeight(floatValue);
    return 0;
}

static int l_CollisionComponent_getHeight(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    floatType floatValue = collisionComponent->getHeight();
    lua_pushnumber(L, floatValue);
    return 1;
}

static int l_CollisionComponent_setVectorList(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);

    if (!lua_istable(L, 2)) {
	luaL_error(L, "2nd argument must be a table of kf.Vector3's");
    }

    integerType tableLength = lua_objlen(L, 2);
    std::vector<Vector3> vectorList;
    for (int i = 0; i < tableLength; i++) {
	lua_rawgeti(L, 2, i+1);
	auto vector = lua_tovector(L, -1);
	vectorList.push_back(*vector);
    }

    collisionComponent->setVectorList(vectorList);

    return 0;
}

static int l_CollisionComponent_getVectorList(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto collisionComponent = static_cast<CollisionComponent*>
	(component);
    auto vectorList = collisionComponent->getVectorList();
    lua_createtable(L, vectorList.size(), 0);
    for(int i = 0; i < vectorList.size(); i++) {
	auto vector = new Vector3(vectorList[i]);
	lua_pushvector(L, vector);
	lua_rawseti(L, -2, i+1);
    }
    
    return 1;
}


static const struct luaL_Reg l_CollisionComponent [] = {
    {"__gc", l_CollisionComponent_gc},
    {"__tostring", l_CollisionComponent_tostring},
    {"getFamily", l_CollisionComponent_getFamily},
    {"createChild", l_CollisionComponent_createChild},
    {"setPhysicsRelation", l_CollisionComponent_setPhysicsRelation},
    {"getPhysicsRelation", l_CollisionComponent_getPhysicsRelation},
    {"setOffset", l_CollisionComponent_setOffset},
    {"getOffset", l_CollisionComponent_getOffset},
    {"setOrigin", l_CollisionComponent_setOrigin},
    {"getOrigin", l_CollisionComponent_getOrigin},
    {"setOrientation", l_CollisionComponent_setOrientation},
    {"getOrientation", l_CollisionComponent_getOrientation},
    {"setType", l_CollisionComponent_setType},
    {"getType", l_CollisionComponent_getType},
    {"setRadius", l_CollisionComponent_setRadius},
    {"getRadius", l_CollisionComponent_getRadius},
    {"setWidth", l_CollisionComponent_setWidth},
    {"getWidth", l_CollisionComponent_getWidth},
    {"setHeight", l_CollisionComponent_setHeight},
    {"getHeight", l_CollisionComponent_getHeight},
    {"setVectorList", l_CollisionComponent_setVectorList},
    {"getVectorList", l_CollisionComponent_getVectorList},
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

    lua_pop(L, 1);

    luaL_register(L, KF_LUA_LIBNAME, l_CollisionComponent_Registry);
    return 1;
}
