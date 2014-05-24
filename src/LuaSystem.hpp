#ifndef L_LUASYSTEM__HPP
#define L_LUASYSTEM__HPP
//DESCRIPTION
/*
  This is a system which calls two lua functions for the corresponding
  process() and createMessage() methods in a typical system. This will
  allow you to write systems within lua, which should speed up
  development on key pieces of the engine. This will also allow for
  more interesting ideas.
 */

//CLASSES
class LuaSystem;

//INCLUDES
#include <functional>
#include "LuaScript.hpp"
#include "AbstractSystem.hpp"
#include "l_Wrapper.hpp"
#include "l_Wrapper_Utils.hpp"


//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class LuaSystem : public AbstractSystem {
private:

    //Lua wrapped functions that will be used with the abstract
    //system's createMessages(), and process() functions
    LuaWrap_VoidFunction func_createMessages;
    LuaWrap_VoidFunction func_process;
public:
    //pass in the type, and the two functions that
    //will be used for creating messages and processing
    LuaSystem(stringType type,
	      LuaWrap_VoidFunction createMessages,
	      LuaWrap_VoidFunction process);
    
    virtual ~LuaSystem();

    void createMessages();
    void process();
};

#endif //END L_LUASYSTEM__HPP
