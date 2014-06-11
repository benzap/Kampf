#include "l_GraphicsComponent.hpp"

GraphicsComponent* lua_pushgraphicsComponent(
					     lua_State *L,
					     GraphicsComponent* graphicsComponent = nullptr) {
    if (graphicsComponent == nullptr) {
	std::cerr << "Warning: GraphicsComponent - this will not work, nullptr" << std::endl;
	graphicsComponent = new GraphicsComponent("");
    }

    GraphicsComponent** graphicsComponentPtr = static_cast<GraphicsComponent**>
	(lua_newuserdata(L, sizeof(GraphicsComponent*)));
  
    //storing the address directly. Lua can be seen as a window,
    //looking in at the engine. This could be a good source for a lot
    //of problems.
    *graphicsComponentPtr = graphicsComponent;

    luaL_getmetatable(L, LUA_USERDATA_GRAPHICSCOMPONENT);
    lua_setmetatable(L, -2);  

    return graphicsComponent;
}

GraphicsComponent* lua_tographicsComponent(lua_State *L, int index) {
    GraphicsComponent* graphicsComponent = *static_cast<GraphicsComponent**>
	(luaL_checkudata(L, index, LUA_USERDATA_GRAPHICSCOMPONENT));
    if (graphicsComponent == NULL) {
	luaL_error(L, "Provided userdata is not of type 'GraphicsComponent'");
    }
    return graphicsComponent;
}

boolType lua_isgraphicsComponent(lua_State* L, int index) {
    if (lua_isuserdata(L, 1)) {
	auto chk = lua_isUserdataType(L, index, LUA_USERDATA_GRAPHICSCOMPONENT);
	return chk;
    }
    return false;
}

static int l_GraphicsComponent_GraphicsComponent(lua_State *L) {
    stringType componentName = luaL_checkstring(L, 1);
    boolType isParent = lua_toboolean(L, 2);

    auto component = new GraphicsComponent(
					   componentName,
					   !isParent);

    lua_pushgraphicsComponent(L, component);
    return 1;
}

static int l_GraphicsComponent_isGraphicsComponent(lua_State *L) {
    return 0;
}

static const struct luaL_Reg l_GraphicsComponent_Registry [] = {
    {"GraphicsComponent", l_GraphicsComponent_GraphicsComponent},
    {"isGraphicsComponent", l_GraphicsComponent_isGraphicsComponent},
    {NULL, NULL}
};

static int l_GraphicsComponent_gc(lua_State *L) {
    return 0;
}

static int l_GraphicsComponent_tostring(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    stringType msg = "Component:GRAPHICS:";
    msg += component->getName();
    lua_pushstring(L, msg.c_str());
    return 1;
}

static int l_GraphicsComponent_getDrawableKey(lua_State *L) {
    auto component = lua_tographicsComponent(L, 1);
    stringType key = component->getDrawableKey();
    lua_pushstring(L, key.c_str());
    return 1;
}

static int l_GraphicsComponent_setDrawableKey(lua_State *L) {
    auto component = lua_tographicsComponent(L, 1);
    stringType key = luaL_checkstring(L, 2);
    component->setDrawableKey(key);
    return 0;
}


static int l_GraphicsComponent_getFamily(lua_State *L) {
    lua_pushstring(L, "GRAPHICS");
    return 1;
}

static int l_GraphicsComponent_createChild(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    stringType childComponentName = luaL_checkstring(L, 2);
    auto childComponent = component->createChild(childComponentName);
    GraphicsComponent* childComponent_cast = static_cast<GraphicsComponent*>
	(childComponent);
    lua_pushgraphicsComponent(L, childComponent_cast);
    return 1;
}

static int l_GraphicsComponent_getType(lua_State *L) {
    auto component = lua_tographicsComponent(L, 1);
    stringType type = component->getType();
    lua_pushstring(L, type.c_str());
    return 1;
}

static int l_GraphicsComponent_setType(lua_State *L) {
    auto component = lua_tographicsComponent(L, 1);
    stringType value = luaL_checkstring(L, 2);
    component->setType(value);
    return 0;
}

static int l_GraphicsComponent_getIndex(lua_State *L) {
    auto component = lua_tographicsComponent(L, 1);
    int index = component->getIndex();
    lua_pushinteger(L, index);
    return 1;
}

static int l_GraphicsComponent_setIndex(lua_State *L) {
    auto component = lua_tographicsComponent(L, 1);
    int value = luaL_checkint(L, 2);
    component->setIndex(value);
    return 0;
}

static int l_GraphicsComponent_setPhysicsRelation(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto graphicsComponent = static_cast<GraphicsComponent*>
	(component);
    
    //get the physics component
    auto p_component = lua_tocomponent(L, 2);
    auto physicsComponent = static_cast<PhysicsComponent*>
	(p_component);
    graphicsComponent->setPhysicsRelation(physicsComponent);
    return 0;
}

static int l_GraphicsComponent_getPhysicsRelation(lua_State *L) {
    auto component = lua_tocomponent(L, 1);
    auto graphicsComponent = static_cast<GraphicsComponent*>
	(component);

    auto p_component = graphicsComponent->getPhysicsRelation();
    lua_pushphysicsComponent(L, p_component);
    return 1;
}


static const struct luaL_Reg l_GraphicsComponent [] = {
    {"__gc", l_GraphicsComponent_gc},
    {"__tostring", l_GraphicsComponent_tostring},
    {"getDrawableKey", l_GraphicsComponent_getDrawableKey},
    {"setDrawableKey", l_GraphicsComponent_setDrawableKey},
    {"getFamily", l_GraphicsComponent_getFamily},
    {"createChild", l_GraphicsComponent_createChild},
    {"getType", l_GraphicsComponent_getType},
    {"setType", l_GraphicsComponent_setType},
    {"getIndex", l_GraphicsComponent_getIndex},
    {"setIndex", l_GraphicsComponent_setIndex},
    {"setPhysicsRelation", l_GraphicsComponent_setPhysicsRelation},
    {"getPhyiscsRelation", l_GraphicsComponent_getPhysicsRelation},
    {NULL, NULL}
};

int luaopen_graphicsComponent(lua_State *L) {
    //GraphicsComponent
    luaL_newmetatable(L, LUA_USERDATA_GRAPHICSCOMPONENT);
    lua_pushvalue(L, -1);
    luaL_getmetatable(L, LUA_USERDATA_ABSTRACTCOMPONENT);
    lua_setmetatable(L, -2);  
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_GraphicsComponent);

    lua_pop(L, 1);

    luaL_register(L, KF_LUA_LIBNAME, l_GraphicsComponent_Registry);
    return 1;
}
