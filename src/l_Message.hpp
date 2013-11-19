#ifndef L_MESSAGE__HPP
#define L_MESSAGE__HPP
//DESCRIPTION
/*
  lua binding for the Message class
 */

//CLASSES
class Message;

//INCLUDES
#include "LuaScript.hpp"
#include "Message.hpp"
#include "Messenger.hpp"

//DEFINITIONS
#define LUA_USERDATA_MESSAGE "l_kf.message"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
Message* lua_pushmessage(lua_State *L, Message* message = nullptr);
Message* lua_tomessage(lua_State *L, int index);
boolType lua_ismessage(lua_State *L, int index);

int luaopen_message(lua_State *L);

#endif //END L_MESSAGE__HPP
