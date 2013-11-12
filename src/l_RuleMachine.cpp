#include "l_RuleMachine.hpp"

void lua_registerRuleMachine(lua_State *L,
			     RuleMachine* rulemachine) {
    //push our rulemachine point into the registry index table
    lua_pushstring(L, LUA_REGISTRY_RULEMACHINE);
    lua_pushlightuserdata(L, (void *) rulemachine);
    lua_settable(L, LUA_REGISTRYINDEX);
}

boolType lua_hasRuleMachine(lua_State *L) {
    lua_pushstring(L, LUA_REGISTRY_RULEMACHINE);
    lua_gettable(L, LUA_REGISTRYINDEX);
    if (lua_islightuserdata(L, -1)) {
	RuleMachine* rulemachine = (RuleMachine *) lua_touserdata(L, -1);
	if (rulemachine != nullptr) {
	    return true;
	}
    }
    return false;
}

RuleMachine* lua_getRuleMachine(lua_State *L) {
    lua_pushstring(L, LUA_REGISTRY_RULEMACHINE);
    lua_gettable(L, LUA_REGISTRYINDEX);
    RuleMachine* rulemachine = (RuleMachine *) lua_touserdata(L, -1);
    return rulemachine;
}

void lua_pushrulemachine(lua_State *L) {
    RuleMachine* rulemachine = nullptr;
    if (lua_hasRuleMachine(L)) {
	rulemachine = lua_getRuleMachine(L);
    }

    RuleMachine** rulePtr = static_cast<RuleMachine**>
	(lua_newuserdata(L, sizeof(RuleMachine*)));

    *rulePtr = rulemachine;

    luaL_getmetatable(L, LUA_USERDATA_RULEMACHINE);
    lua_setmetatable(L, -2);
}

boolType lua_isrulemachine(lua_State *L, int index) {
    if (lua_isuserdata(L, 1)) {
	RuleMachine* rulemachine = *static_cast<RuleMachine**>
	    (luaL_checkudata(L, index, LUA_USERDATA_RULEMACHINE)); 
	if (rulemachine != NULL) {
	    return true;
	}
	return false;
    }
}

RuleMachine* lua_torulemachine(lua_State *L, int index) {
    RuleMachine* rulemachine = *static_cast<RuleMachine**>
	(luaL_checkudata(L, index, LUA_USERDATA_RULEMACHINE));
    if (rulemachine == NULL) {
	luaL_error(L, "Provided userdata is not of type 'Rulemachine'");
    }
    return rulemachine;
}
 
static int l_RuleMachine_isrulemachine(lua_State *L) {
    if (lua_isrulemachine(L, 1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_RuleMachine_addRule(lua_State *L) {
    auto wrapperCondition = RuleWrapper_condition(L, 1);
    auto wrapperFunction = RuleWrapper_function(L, 2);
    auto rulemachine = lua_getRuleMachine(L);
    rulemachine->addRule(wrapperCondition, wrapperFunction);
    return 0;
}

static const struct luaL_Reg l_rulemachine_kampf [] = {
    {"isRuleMachine", l_RuleMachine_isrulemachine},
    {NULL, NULL}
};
 
static const struct luaL_Reg l_rulemachine [] = {
    {"addRule", l_RuleMachine_addRule},
    {NULL, NULL}
};

int luaopen_rulemachine(lua_State *L, RuleMachine* rulemachine) {
    //Rule Machine
    luaL_newmetatable(L, LUA_USERDATA_RULEMACHINE);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_rulemachine);

    luaL_register(L, KF_LUA_LIBNAME, l_rulemachine_kampf);

    return 1;
}
