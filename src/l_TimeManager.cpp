#include "l_TimeManager.hpp"

TimeManager* lua_pushtimeManager(lua_State *L) {
    auto timeManager = TimeManager::getInstance();

    TimeManager ** timeManagerPtr = static_cast<TimeManager**>
	(lua_newuserdata(L, sizeof(TimeManager*)));

    *timeManagerPtr = timeManager;
    
    luaL_getmetatable(L, LUA_USERDATA_TIMEMANAGER);
    lua_setmetatable(L, -2);

    return timeManager;
}

TimeManager* lua_totimeManager(lua_State *L, int index) {
    TimeManager* timeManager = *static_cast<TimeManager**>
	(luaL_checkudata(L, index, LUA_USERDATA_TIMEMANAGER));
    if (timeManager == NULL) {
	luaL_error(L, "Provided userdata is not of type 'TimeManager'");
    }
    return timeManager;
}

boolType lua_istimeManager(lua_State *L, int index) {
    if (lua_isuserdata(L, index)) {
	auto chk = lua_isUserdataType(L, index, LUA_USERDATA_TIMEMANAGER); 
	return chk;
    }
    return false;
}

//lua functions
static int l_TimeManager_TimeManager(lua_State *L) {
    lua_pushtimeManager(L);
    
    return 1;
}

static int l_TimeManager_isTimeManager(lua_State *L) {
    auto chk = lua_istimeManager(L, 1);

    if (chk) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_TimeManager_appendTime(lua_State *L) {
    auto timeManager = lua_totimeManager(L, 1);

    //returns offset, or zero value
    auto timeOffset = luaL_optinteger(L, 2, 0);
    auto timeGuid = timeManager->appendTime(timeOffset);

    lua_pushstring(L, timeGuid.c_str());
    
    return 1;
}

static int l_TimeManager_extendTime(lua_State *L) {
    auto timeManager = lua_totimeManager(L, 1);

    auto timeGuid = luaL_checkstring(L, 2);
    auto timeOffset = luaL_checkint(L, 3);

    timeManager->extendTime(timeGuid, timeOffset);
    return 0;
}

static int l_TimeManager_hasTime(lua_State *L) {
    auto timeManager = lua_totimeManager(L, 1);
    auto timeGuid = luaL_checkstring(L, 2);
    
    if (timeManager->hasTime(timeGuid)) {
        lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    
    return 1;
}

static int l_TimeManager_removeTime(lua_State *L) {
    auto timeManager = lua_totimeManager(L, 1);
    auto timeGuid = luaL_checkstring(L, 2);

    if (timeManager->hasTime(timeGuid)) {	
	timeManager->removeTime(timeGuid);
    }
    else {
	luaL_error(L, "Provided timeGuid does not exist in the TimeManager");
    }

    return 0;
}

static int l_TimeManager_getTime(lua_State *L) {
    auto timeManager = lua_totimeManager(L, 1);
    auto timeGuid = luaL_checkstring(L, 2);

    timeType theTime = timeManager->getTime(timeGuid);
    lua_pushinteger(L, theTime);

    return 1;
}

	
//registrations
static const struct luaL_Reg l_TimeManager_registry [] = {
    {"TimeManager", l_TimeManager_TimeManager},
    {"isTimeManager", l_TimeManager_isTimeManager},
    {NULL, NULL}
};

static const struct luaL_Reg l_TimeManager [] = {
    {"appendTime", l_TimeManager_appendTime},
    {"extendTime", l_TimeManager_extendTime},
    {"hasTime", l_TimeManager_hasTime},
    {"removeTime", l_TimeManager_removeTime},
    {"getTime", l_TimeManager_getTime},
    {NULL, NULL}
};

int luaopen_timeManager(lua_State *L) {
    luaL_newmetatable(L, LUA_USERDATA_TIMEMANAGER);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_TimeManager);

    luaL_register(L, KF_LUA_LIBNAME, l_TimeManager_registry);

    return 1;
}

