#include "l_Messenger.hpp"

void lua_registerMessenger(lua_State *L,
			     Messenger* messenger) {
    //push our messenger point into the registry index table
    lua_pushstring(L, LUA_REGISTRY_MESSENGER);
    lua_pushlightuserdata(L, (void *) messenger);
    lua_settable(L, LUA_REGISTRYINDEX);
}

boolType lua_hasMessenger(lua_State *L) {
    lua_pushstring(L, LUA_REGISTRY_MESSENGER);
    lua_gettable(L, LUA_REGISTRYINDEX);
    if (lua_islightuserdata(L, -1)) {
	Messenger* messenger = (Messenger *) lua_touserdata(L, -1);
	if (messenger != nullptr) {
	    return true;
	}
    }
    return false;
}

Messenger* lua_getMessenger(lua_State *L) {
    lua_pushstring(L, LUA_REGISTRY_MESSENGER);
    lua_gettable(L, LUA_REGISTRYINDEX);
    Messenger* messenger = (Messenger *) lua_touserdata(L, -1);
    return messenger;
}

void lua_pushmessenger(lua_State *L) {
    Messenger* messenger = nullptr;
    if (lua_hasMessenger(L)) {
	messenger = lua_getMessenger(L);
    }

    Messenger** rulePtr = static_cast<Messenger**>
	(lua_newuserdata(L, sizeof(Messenger*)));

    *rulePtr = messenger;

    luaL_getmetatable(L, LUA_USERDATA_MESSENGER);
    lua_setmetatable(L, -2);
}

boolType lua_ismessenger(lua_State *L, int index) {
    if (lua_isuserdata(L, 1)) {
	Messenger* messenger = *static_cast<Messenger**>
	    (luaL_checkudata(L, index, LUA_USERDATA_MESSENGER)); 
	if (messenger != NULL) {
	    return true;
	}
	return false;
    }
}

Messenger* lua_tomessenger(lua_State *L, int index) {
    Messenger* messenger = *static_cast<Messenger**>
	(luaL_checkudata(L, index, LUA_USERDATA_MESSENGER));
    if (messenger == NULL) {
	luaL_error(L, "Provided userdata is not of type 'Messenger'");
    }
    return messenger;
}

static int l_Messenger_ismessenger(lua_State *L) {
    if (lua_ismessenger(L, 1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

//appends the message to the messenger, and returns the Message
static int l_Messenger_appendMessage(lua_State *L) {
    auto message = lua_pushmessage(L);
    return 1;
}

static int l_Messenger_retrieveMessages(lua_State *L) {
    Messenger* messenger = nullptr;
    if (lua_hasMessenger(L)) {
	messenger = lua_getMessenger(L);
    }
    else {
	luaL_error(L, "Messenger has not been registered in lua");
    }
    auto messageVector = messenger->retrieveMessages();
    lua_newtable(L);
    int index = 1;
    for (auto msg : messageVector) {
	lua_pushmessage(L, &msg);
	lua_rawseti(L, -1, index++);
    }
    return 1;
}

static const struct luaL_Reg l_messenger_kampf [] = {
    {"isMessenger", l_Messenger_ismessenger},
    {NULL, NULL}
};
 
static const struct luaL_Reg l_messenger [] = {
    {"appendMessage", l_Messenger_appendMessage},
    {"retrieveMessages", l_Messenger_retrieveMessages},
    {NULL, NULL}
};

int luaopen_messenger(lua_State *L, Messenger* messenger) {
    //Messenger
    luaL_newmetatable(L, LUA_USERDATA_MESSENGER);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_messenger);

    lua_pop(L, 1);

    luaL_register(L, KF_LUA_LIBNAME, l_messenger_kampf);

    lua_registerMessenger(L, messenger);

    return 1;
}
