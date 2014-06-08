#include "l_AbstractForceGenerator.hpp"

AbstractForceGenerator* lua_pushAbstractForceGenerator(
					     lua_State *L,
					     AbstractForceGenerator* forceGenerator) {

    AbstractForceGenerator** AbstractForceGeneratorPtr = static_cast<AbstractForceGenerator**>
	(lua_newuserdata(L, sizeof(AbstractForceGenerator*)));
  
    //storing the address directly. Lua can be seen as a window,
    //looking in at the engine. This could be a good source for a lot
    //of problems.
    *AbstractForceGeneratorPtr = forceGenerator;

    luaL_getmetatable(L, LUA_USERDATA_ABSTRACTFORCEGENERATOR);
    lua_setmetatable(L, -2);  

    return forceGenerator;
}

AbstractForceGenerator* lua_toAbstractForceGenerator(lua_State *L, int index) {
    AbstractForceGenerator* forceGenerator = *static_cast<AbstractForceGenerator**>
	(luaL_checkudata(L, index, LUA_USERDATA_ABSTRACTFORCEGENERATOR));
    if (forceGenerator == NULL) {
	luaL_error(L, "Provided userdata is not of type 'AbstractForceGenerator'");
    }
    return forceGenerator;
}

boolType lua_isAbstractForceGenerator(lua_State* L, int index) {
    if (lua_isuserdata(L, index)) {
	auto chk = lua_isUserdataType(L, index, LUA_USERDATA_ABSTRACTFORCEGENERATOR);
	return chk;
    }
    return false;
}

static int l_AbstractForceGenerator_isAbstractForceGenerator(lua_State *L) {
    if (lua_isAbstractForceGenerator(L, 1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_AbstractForceGenerator_gc(lua_State *L) {
    return 0;
}

static int l_AbstractForceGenerator_tostring(lua_State *L) {
    auto abstractGenerator = lua_toAbstractForceGenerator(L, 1);
    stringType generatorName = abstractGenerator->getName();
    stringType msg = "AbstractForceGenerator:" + generatorName;
    lua_pushstring(L, msg.c_str());
    return 1;
}

static int l_AbstractForceGenerator_getName(lua_State *L) {
    auto abstractGenerator = lua_toAbstractForceGenerator(L, 1);
    stringType generatorName = abstractGenerator->getName();
    lua_pushstring(L, generatorName.c_str());
    return 1;
}

static int l_AbstractForceGenerator_registerComponent(lua_State *L) {
    auto abstractGenerator = lua_toAbstractForceGenerator(L, 1);
    auto collisionComponent = lua_tocollisionComponent(L, 2);
    
    abstractGenerator->registerComponent(collisionComponent);

    return 0;
}

static int l_AbstractForceGenerator_unregisterComponent(lua_State *L) {
    auto abstractGenerator = lua_toAbstractForceGenerator(L, 1);
    auto collisionComponent = lua_tocollisionComponent(L, 2);
    
    abstractGenerator->unregisterComponent(collisionComponent);

    return 0;
}

static int l_AbstractForceGenerator_hasRegisteredComponent(lua_State *L) {
    auto abstractGenerator = lua_toAbstractForceGenerator(L, 1);
    auto collisionComponent = lua_tocollisionComponent(L, 2);

    if (abstractGenerator->hasRegisteredComponent(collisionComponent)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }

    return 1;
}

static int l_AbstractForceGenerator_getRegisteredComponents(lua_State *L) {
    auto abstractGenerator = lua_toAbstractForceGenerator(L, 1);
    auto componentList = abstractGenerator->getRegisteredComponents();

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

static const struct luaL_Reg l_AbstractForceGenerator_Registry [] = {
    {"isAbstractForceGenerator", l_AbstractForceGenerator_isAbstractForceGenerator},
    {NULL, NULL}
};

static const struct luaL_Reg l_AbstractForceGenerator [] = {
    {"__gc", l_AbstractForceGenerator_gc},
    {"__tostring", l_AbstractForceGenerator_tostring},
    {"getName", l_AbstractForceGenerator_getName},
    {"registerComponent", l_AbstractForceGenerator_registerComponent},
    {"unregisterComponent", l_AbstractForceGenerator_unregisterComponent},
    {"hasRegisteredComponent", l_AbstractForceGenerator_hasRegisteredComponent},
    {"getRegisteredComponents", l_AbstractForceGenerator_getRegisteredComponents},
    {NULL, NULL}
};

int luaopen_AbstractForceGenerator(lua_State *L) {
    //AbstractForceGenerator
    luaL_newmetatable(L, LUA_USERDATA_ABSTRACTFORCEGENERATOR);

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_AbstractForceGenerator);
    
    luaL_register(L, KF_LUA_LIBNAME, l_AbstractForceGenerator_Registry);
    return 1;
}

