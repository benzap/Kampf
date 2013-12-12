#include "l_Component.hpp"

Component* lua_pushcomponent(lua_State *L, Component* component) {
    if (component->getFamily() == enumComponentFamily::ABSTRACT) {
	lua_pushabstractComponent(L, component);
    }
    else if (component->getFamily() == enumComponentFamily::COLLISION) {
	CollisionComponent* component_collision = static_cast<CollisionComponent*>
	    (component);
	lua_pushcollisionComponent(L, component_collision);
    }
    else if (component->getFamily() == enumComponentFamily::PHYSICS) {
	PhysicsComponent* component_physics = static_cast<PhysicsComponent*>
	    (component);
	lua_pushphysicsComponent(L, component_physics);
    }
    else if (component->getFamily() == enumComponentFamily::GRAPHICS) {
	GraphicsComponent* component_graphics = static_cast<GraphicsComponent*>
	    (component);
	lua_pushgraphicsComponent(L, component_graphics);
    }
    return component;
}

Component* lua_tocomponent(lua_State *L, int index) {
    Component* component = nullptr;
    if (lua_isabstractComponent(L, 1)) {
	component = *static_cast<AbstractComponent**>
	    (luaL_checkudata(L, index, LUA_USERDATA_ABSTRACTCOMPONENT));
    }
    else if (lua_iscollisionComponent(L, 1)) {
	component = *static_cast<AbstractComponent**>
	    (luaL_checkudata(L, index, LUA_USERDATA_COLLISIONCOMPONENT));
    }
    else if (lua_isphysicsComponent(L, 1)) {
	component = *static_cast<AbstractComponent**>
	    (luaL_checkudata(L, index, LUA_USERDATA_PHYSICSCOMPONENT));
    }
    else if (lua_isgraphicsComponent(L, 1)) {
	component = *static_cast<AbstractComponent**>
	    (luaL_checkudata(L, index,LUA_USERDATA_GRAPHICSCOMPONENT));
    }
    else {
	luaL_error(L, "ERROR: Userdata is not a component type");
    }
    return component;
}

//a general check on whether a userdata is a component
boolType lua_iscomponent(lua_State *L, int index) {
    if (lua_isuserdata(L, index)) {
	//check if it's an abstract component
	if (lua_isUserdataType(L, 1, LUA_USERDATA_ABSTRACTCOMPONENT) ||
	    lua_isUserdataType(L, 1, LUA_USERDATA_COLLISIONCOMPONENT)||
	    lua_isUserdataType(L, 1, LUA_USERDATA_PHYSICSCOMPONENT) ||
	    lua_isUserdataType(L, 1, LUA_USERDATA_GRAPHICSCOMPONENT)){
	    return true;
	}
    }
    return false;
}

static int l_Component_isComponent(lua_State *L) {
    if (lua_iscomponent(L, 1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static const struct luaL_Reg l_Component_Registry [] = {
    {"isComponent", l_Component_isComponent},
    {NULL, NULL}
};

int luaopen_component(lua_State *L) {
    luaL_register(L, KF_LUA_LIBNAME, l_Component_Registry);
    return 1;
}
