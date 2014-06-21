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
    if (lua_isphysicsComponent(L, 1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static const struct luaL_Reg l_PhysicsComponent_Registry [] = {
    {"PhysicsComponent", l_PhysicsComponent_PhysicsComponent},
    {"isPhysicsComponent", l_PhysicsComponent_isPhysicsComponent},
    {NULL, NULL}
};

static int l_PhysicsComponent_gc(lua_State *L) {
    return 0;
}

static int l_PhysicsComponent_setPhysicsType(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    stringType strType = luaL_checkstring(L, 2);
    enumPhysicsType type;

    if (strType == "NONE") {
	type = enumPhysicsType::NONE;
    }
    else if (strType == "RIGID") {
	type = enumPhysicsType::RIGID;
    }
    else if (strType == "PARTICLE") {
	type = enumPhysicsType::PARTICLE;
    }
    else if (strType == "CUSTOM") {
	type = enumPhysicsType::CUSTOM;
    }
    else {
	stringType errorMsg = "Unknown Physics Type: " + strType;
	luaL_error(L, errorMsg.c_str());
	return 0;
    }
    component->setPhysicsType(type);
    return 0;
}

static int l_PhysicsComponent_getPhysicsType(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);

    auto type = component->getPhysicsType();
    stringType strType;
    switch(type) {
    case enumPhysicsType::NONE:
	strType = "NONE";
	break;
    case enumPhysicsType::RIGID:
	strType = "RIGID";
	break;
    case enumPhysicsType::PARTICLE:
	strType = "PARTICLE";
	break;
    case enumPhysicsType::CUSTOM:
	strType = "CUSTOM";
	break;
    default:
	strType = "UNKNOWN";
	break;
    }

    lua_pushstring(L, strType.c_str());

    return 1;
}


static int l_PhysicsComponent_setPosition(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    auto vector = lua_tovector(L, 2);
    component->setPosition(*vector);
    return 0;   
}

static int l_PhysicsComponent_getPosition(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    auto vector = new Vector3(component->getPosition());
    lua_pushvector(L, vector);
    return 1;
}

static int l_PhysicsComponent_setVelocity(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    auto vector = lua_tovector(L, 2);
    component->setVelocity(*vector);
    return 0;
}

static int l_PhysicsComponent_getVelocity(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    auto vector = new Vector3(component->getVelocity());
    lua_pushvector(L, vector);
    return 1;
}

static int l_PhysicsComponent_setAcceleration(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    auto vector = lua_tovector(L, 2);
    component->setAcceleration(*vector);
    return 0;
}

static int l_PhysicsComponent_getAcceleration(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    auto vector = new Vector3(component->getAcceleration());
    lua_pushvector(L, vector);
    return 1;
}

static int l_PhysicsComponent_setScale(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    auto vector = lua_tovector(L, 2);
    component->setScale(*vector);
    return 0;
}

static int l_PhysicsComponent_getScale(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    auto vector = new Vector3(component->getScale());
    lua_pushvector(L, vector);
    return 1;
}

static int l_PhysicsComponent_setOrientation(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    auto orientation = lua_toquaternion(L, 2);
    component->setOrientation(*orientation);
    return 0;
}

static int l_PhysicsComponent_getOrientation(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    auto orientation = new Quaternion(component->getOrientation());
    lua_pushquaternion(L, orientation);
    return 1;
}

static int l_PhysicsComponent_setDamping(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    floatType damping = luaL_checknumber(L, 2);
    component->setDamping(damping);
    return 0;
}

static int l_PhysicsComponent_getDamping(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    floatType damping = component->getDamping();
    lua_pushnumber(L, damping);
    return 1;
}

static int l_PhysicsComponent_setMass(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    floatType mass = luaL_checknumber(L, 2);
    component->setMass(mass);
    return 0;
}

static int l_PhysicsComponent_getMass(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    floatType mass = component->getMass();
    lua_pushnumber(L, mass);
    return 1;
}

static int l_PhysicsComponent_tostring(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    stringType msg = "Component:PHYSICS:";
    msg += component->getName();
    lua_pushstring(L, msg.c_str());
    return 1;
}

static int l_PhysicsComponent__setInverseMass(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    floatType value = luaL_checknumber(L, 2);
    component->setInverseMass(value);
    return 0;
}

static int l_PhysicsComponent_getInverseMass(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    floatType value = component->getInverseMass();
    lua_pushnumber(L, value);
    return 1;
}

static int l_PhysicsComponent_setElasticity(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    floatType value = luaL_checknumber(L, 2);

    component->setElasticity(value);

    return 0;
}

static int l_PhysicsComponent_getElasticity(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    floatType elasticity = component->getElasticity();

    lua_pushnumber(L, elasticity);

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

static int l_PhysicsComponent_addForce(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    auto vec = lua_tovector(L, 2);
    
    component->addForce(*vec);
    return 0;
}

static int l_PhysicsComponent_getForce(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    auto force = component->getForceAccumulator();

    lua_pushvector(L, new Vector3(force));

    return 1;
}

static int l_PhysicsComponent_setForce(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    auto vec = lua_tovector(L, 2);
    component->setForceAccumulator(*vec);
    
    return 0;
}

static int l_PhysicsComponent_clearForce(lua_State *L) {
    auto component = lua_tophysicsComponent(L, 1);
    component->clearForceAccumulator();
    return 0;
}

static const struct luaL_Reg l_PhysicsComponent [] = {
    {"__gc", l_PhysicsComponent_gc},
    {"__tostring", l_PhysicsComponent_tostring},
    {"setPhysicsType", l_PhysicsComponent_setPhysicsType},
    {"getPhysicsType", l_PhysicsComponent_getPhysicsType},
    {"setPosition", l_PhysicsComponent_setPosition},
    {"getPosition", l_PhysicsComponent_getPosition},
    {"setVelocity", l_PhysicsComponent_setVelocity},
    {"getVelocity", l_PhysicsComponent_getVelocity},
    {"setAcceleration", l_PhysicsComponent_setAcceleration},
    {"getAcceleration", l_PhysicsComponent_getAcceleration},
    {"setScale", l_PhysicsComponent_setScale},
    {"getScale", l_PhysicsComponent_getScale},
    {"setOrientation", l_PhysicsComponent_setOrientation},
    {"getOrientation", l_PhysicsComponent_getOrientation},
    {"setDamping", l_PhysicsComponent_setDamping},
    {"getDamping", l_PhysicsComponent_getDamping},
    {"setMass", l_PhysicsComponent_setMass},
    {"getMass", l_PhysicsComponent_getMass},
    {"setInverseMass", l_PhysicsComponent__setInverseMass},
    {"getInverseMass", l_PhysicsComponent_getInverseMass},
    {"setElasticity", l_PhysicsComponent_setElasticity},
    {"getElasticity", l_PhysicsComponent_getElasticity},
    {"getFamily", l_PhysicsComponent_getFamily},
    {"createChild", l_PhysicsComponent_createChild},
    {"addForce", l_PhysicsComponent_addForce},
    {"getForce", l_PhysicsComponent_getForce},
    {"setForce", l_PhysicsComponent_setForce},
    {"clearForce", l_PhysicsComponent_clearForce},
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

    lua_pop(L, 1);

    luaL_register(L, KF_LUA_LIBNAME, l_PhysicsComponent_Registry);
    return 1;
}
