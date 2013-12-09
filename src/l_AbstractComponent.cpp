#include "l_AbstractComponent.hpp"

AbstractComponent* lua_pushabstractComponent(
    lua_State *L,
    AbstractComponent* abstractComponent = nullptr) {
    if (abstractComponent == nullptr) {
	std::cerr << "Warning: AbstractComponent - this will not work, nullptr" << std::endl;
	abstractComponent = new AbstractComponent("");
    }

    AbstractComponent** abstractComponentPtr = static_cast<AbstractComponent**>
	(lua_newuserdata(L, sizeof(AbstractComponent*)));
  
    //storing the address directly. Lua can be seen as a window,
    //looking in at the engine. This could be a good source for a lot
    //of problems.
    *abstractComponentPtr = abstractComponent;

    luaL_getmetatable(L, LUA_USERDATA_ABSTRACTCOMPONENT);
    lua_setmetatable(L, -2);  

    std::cout << "getname: " << abstractComponent->getName() << std::endl;

    return abstractComponent;
}

AbstractComponent* lua_toabstractComponent(lua_State *L, int index) {
    AbstractComponent* abstractComponent = *static_cast<AbstractComponent**>
	(luaL_checkudata(L, index, LUA_USERDATA_ABSTRACTCOMPONENT));
    if (abstractComponent == NULL) {
	luaL_error(L, "Provided userdata is not of type 'AbstractComponent'");
    }
    return abstractComponent;
}

boolType lua_isabstractComponent(lua_State* L, int index) {
    if (lua_isuserdata(L, 1)) {

	AbstractComponent* abstractComponent = *static_cast<AbstractComponent**>
	    (luaL_checkudata(L, index, LUA_USERDATA_ABSTRACTCOMPONENT));
	if (abstractComponent != NULL) {
	    return true;
	}
	return false;
    }
    return false;
}

static int l_AbstractComponent_AbstractComponent(lua_State *L) {
    stringType componentName = luaL_checkstring(L, 1);
    boolType isParent = lua_toboolean(L, 2);

    auto component = new AbstractComponent(
	componentName,
	enumComponentFamily::ABSTRACT,
	!isParent);

    lua_pushabstractComponent(L, component);
    return 1;
}

static int l_AbstractComponent_isAbstractComponent(lua_State *L) {
    if (lua_isabstractComponent(L, 1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_AbstractComponent_gc(lua_State *L) {
    return 0;
}

static int l_AbstractComponent_tostring(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);
    stringType msg = "Component:ABSTRACT:";
    msg += component->getName();
    lua_pushstring(L, msg.c_str());
    return 1;
}

static int l_AbstractComponent_getName(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);
    stringType compName = component->getName();
    lua_pushstring(L, compName.c_str());
    return 1;
}

static int l_AbstractComponent_setName(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);
    stringType compName = luaL_checkstring(L, 2);

    component->setName(compName);
    return 0;
}

static int l_AbstractComponent_getFamily(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);
    enumComponentFamily familyType = component->getFamily();

    if (familyType == enumComponentFamily::ABSTRACT) {
	lua_pushstring(L, "ABSTRACT");
    }
    else if (familyType == enumComponentFamily::COLLISION) {
	lua_pushstring(L, "COLLISION");
    }
    else if (familyType == enumComponentFamily::PHYSICS) {
	lua_pushstring(L, "PHYSICS");
    }
    else if (familyType == enumComponentFamily::GRAPHICS) {
	lua_pushstring(L, "GRAPHICS");
    }
    else if (familyType == enumComponentFamily::CUSTOM) {
	lua_pushstring(L, "CUSTOM");
    }
    else {
	lua_pushstring(L, "UNKNOWN");
    }
    return 1;
}

static int l_AbstractComponent_isParent(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);
    
    if (component->isParent()) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_AbstractComponent_isActive(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);
    
    if (component->isActive()) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_AbstractComponent_setActive(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);
    component->setActive();
    return 0;
}

static int l_AbstractComponent_setInactive(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);
    component->setInactive();
    return 0;
}

static int l_AbstractComponent_get(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);
    stringType keyname = luaL_checkstring(L, 2);

    if (component->hasCustomAttribute(keyname)) {
	auto customAttribute = component->get(keyname);
	lua_pushcustomAttribute(L, customAttribute);
    }
    else {
	lua_pushnil(L);
    }
    return 1;
}

static int l_AbstractComponent_set(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);
    stringType keyname = luaL_checkstring(L, 2);
    auto customAttribute = lua_tocustomAttribute(L, 3);
    
    component->set(keyname, *customAttribute);
    return 0;
}

static int l_AbstractComponent_has(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);
    stringType keyname = luaL_checkstring(L, 2);
    if (component->hasCustomAttribute(keyname)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_AbstractComponent_createChild(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);
    stringType childComponentName = luaL_checkstring(L, 2);
    auto childComponent = component->createChild(childComponentName);
    lua_pushabstractComponent(L, childComponent);
    return 1;
}

static int l_AbstractComponent_addChild(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);
    luaL_error(L, "Not Implemented");
    return 0;
}

static int l_AbstractComponent_hasChildren(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);

    if (component->hasChildren()) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_AbstractComponent_children(lua_State *L) {
    auto component = lua_toabstractComponent(L, 1);
    luaL_error(L, "Not Implemented");
    return 0;
}

static const struct luaL_Reg l_AbstractComponent_Registry [] = {
    {"AbstractComponent", l_AbstractComponent_AbstractComponent},
    {"isAbstractComponent", l_AbstractComponent_isAbstractComponent},
    {NULL, NULL}
};

static const struct luaL_Reg l_AbstractComponent [] = {
    {"__gc", l_AbstractComponent_gc},
    {"__tostring", l_AbstractComponent_tostring},
    {"getName", l_AbstractComponent_getName},
    {"setName", l_AbstractComponent_setName},
    {"getFamily", l_AbstractComponent_getFamily},
    {"isParent", l_AbstractComponent_isParent},
    {"isActive", l_AbstractComponent_isActive},
    {"setActive", l_AbstractComponent_setActive},
    {"setInactive", l_AbstractComponent_setInactive},
    {"get", l_AbstractComponent_get},
    {"set", l_AbstractComponent_set},
    {"has", l_AbstractComponent_has},
    {"createChild", l_AbstractComponent_createChild},
    {"addChild", l_AbstractComponent_addChild},
    {"hasChildren", l_AbstractComponent_hasChildren},
    {"children", l_AbstractComponent_children},
    {NULL, NULL}
};

int luaopen_abstractComponent(lua_State *L) {
    //AbstractComponent
    luaL_newmetatable(L, LUA_USERDATA_ABSTRACTCOMPONENT);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_AbstractComponent);

    luaL_register(L, KF_LUA_LIBNAME, l_AbstractComponent_Registry);
    return 1;
}
