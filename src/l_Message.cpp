#include "l_Message.hpp"

Message* lua_pushmessage(lua_State *L, Message* message) { 
    if (message == nullptr) {
	message = Messenger::getInstance()->appendMessage();
    }

    Message ** messagePtr = static_cast<Message**>
	(lua_newuserdata(L, sizeof(Message*)));

    *messagePtr = message;
    
    luaL_getmetatable(L, LUA_USERDATA_MESSAGE);
    lua_setmetatable(L, -2);

    return message;
}

Message* lua_tomessage(lua_State *L, int index) {
    Message* message = *static_cast<Message**>
	(luaL_checkudata(L, index, LUA_USERDATA_MESSAGE));
    if (message == NULL) {
	luaL_error(L, "Provided userdata is not of type 'Message'");
    }
    return message;
}

boolType lua_ismessage(lua_State* L, int index) {
    if (lua_isuserdata(L, index)) {
	auto chk = lua_isUserdataType(L, index, LUA_USERDATA_MESSAGE);
	return chk;
    }
    return false;
}

// static int l_Message_Message(lua_State *L) {
//     auto message = lua_pushmessage(L);
    
//     return 1;
// }

static int l_Message_isMessage(lua_State *L) {
    if (lua_ismessage(L, -1)) {
	lua_pushboolean(L, 1);
    }
    else {
	lua_pushboolean(L, 0);
    }
    return 1;
}

static int l_Message_getID(lua_State *L) {
    auto message = lua_tomessage(L, 1);
    lua_pushnumber(L, message->getID());
    return 1;
}

static int l_Message_getType(lua_State *L) {
    auto message = lua_tomessage(L, 1);
    enumMessageType messageType = message->getType();
    lua_pushstring(L, message->getTypeString().c_str());

    return 1;
}

static int l_Message_setType(lua_State *L) {
    auto message = lua_tomessage(L, 1);
    stringType type = luaL_checkstring(L, 2);
    message->setTypeString(type);
    
    return 0;
}

static int l_Message_getFirstEntity(lua_State *L) {
    auto message = lua_tomessage(L, 1);
    if (message->firstEntity != nullptr) {
	lua_pushentity(L, message->firstEntity);
    }
    else {
	lua_pushnil(L);
    }
    
    return 1;
}

static int l_Message_setFirstEntity(lua_State *L) {
    auto message = lua_tomessage(L, 1);
    auto entity = lua_toentity(L, 2);
    message->firstEntity = entity;
    return 0;
}

static int l_Message_getFirstComponent(lua_State *L) {
    auto message = lua_tomessage(L, 1);
    if (message->firstComponent != nullptr) {
	lua_pushcomponent(L, message->firstComponent);
    }
    else {
	lua_pushnil(L);
    }
    return 1;
}

static int l_Message_setFirstComponent(lua_State *L) {
    auto message = lua_tomessage(L, 1);
    auto component  = lua_tocomponent(L, 2);
    message->firstComponent = component;
    return 0;
}

static int l_Message_getSecondEntity(lua_State *L) {
    auto message = lua_tomessage(L, 1);
    if (message->secondEntity != nullptr) {
	lua_pushentity(L, message->secondEntity);
    }
    else {
	lua_pushnil(L);
    }
    
    return 1;
}

static int l_Message_setSecondEntity(lua_State *L) {
    auto message = lua_tomessage(L, 1);
    auto entity = lua_toentity(L, 2);
    message->secondEntity = entity;
    return 0;
}

static int l_Message_getSecondComponent(lua_State *L) {
    auto message = lua_tomessage(L, 1);
    if (message->secondComponent != nullptr) {
	lua_pushcomponent(L, message->secondComponent);
    }
    else {
	lua_pushnil(L);
    }
    return 1;
}

static int l_Message_setSecondComponent(lua_State *L) {
    auto message = lua_tomessage(L, 1);
    auto component  = lua_tocomponent(L, 2);
    message->secondComponent = component;
    return 0;
}

static int l_Message_getCustomAttribute(lua_State *L) {
    auto message = lua_tomessage(L, 1);
    stringType keyname = luaL_checkstring(L, 2);
    //todo, check if attribute exists
    auto customAttribute = message->customData[keyname];
    lua_pushcustomAttribute(L, new CustomAttribute(customAttribute));
    return 1;
}

static int l_Message_setCustomAttribute(lua_State *L) {
    auto message = lua_tomessage(L, 1);
    stringType keyname = luaL_checkstring(L, 2);
    auto customAttribute = lua_tocustomAttribute(L, 3);
    message->customData[keyname] = customAttribute;
    return 0;
}

static const struct luaL_Reg l_Message_registry [] = {
    //{"Message", l_Message_Message},
    {"isMessage", l_Message_isMessage},
    {NULL, NULL}
};

static const struct luaL_Reg l_Message [] = {
    {"getID", l_Message_getID},
    {"getType", l_Message_getType},
    {"setType", l_Message_setType},
    {"getFirstEntity", l_Message_getFirstEntity},
    {"setFirstEntity", l_Message_setFirstEntity},
    {"getFirstComponent", l_Message_getFirstComponent},
    {"setFirstComponent", l_Message_setFirstComponent},
    {"getSecondEntity", l_Message_getSecondEntity},
    {"setSecondEntity", l_Message_setSecondEntity},
    {"getSecondComponent", l_Message_getSecondComponent},
    {"setSecondComponent", l_Message_setSecondComponent},
    {"getCustomAttribute", l_Message_getCustomAttribute},
    {"get", l_Message_getCustomAttribute},
    {"setCustomAttribute", l_Message_setCustomAttribute},
    {"set", l_Message_setCustomAttribute},
    {NULL, NULL}
};

int luaopen_message(lua_State *L) {
    luaL_newmetatable(L, LUA_USERDATA_MESSAGE);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, l_Message);

    luaL_register(L, KF_LUA_LIBNAME, l_Message_registry);

    return 1;
}
