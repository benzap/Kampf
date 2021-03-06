#ifndef LUASCRIPT__HPP
#define LUASCRIPT__HPP
//DESCRIPTION
/*
  Contains the lua scripting state machine, which will allow lua scripting
  within the engine at key points. This should speed up production...
*/
//CLASSES
class LuaScript;

//INCLUDES
#include <iostream>
#include <fstream>
#include <streambuf>
#include "lua.hpp"

#include "kampf.hpp"

//the kampf extensible libraries
#include "l_Wrapper.hpp"
#include "l_kampf.hpp"
#include "l_Vector3.hpp"
#include "l_Quaternion.hpp"
#include "l_SDLAssetManager.hpp"
#include "l_SDLDrawable.hpp"
#include "l_SDLText.hpp"
#include "l_SDLFontManager.hpp"
#include "l_SDLFont.hpp"
#include "l_Message.hpp"
#include "l_Messenger.hpp"
#include "l_RuleMachine.hpp"
#include "l_RenderWindow.hpp"
#include "l_Entity.hpp"
#include "l_EntityManager.hpp"
#include "l_CustomAttribute.hpp"
#include "l_AbstractComponent.hpp"
#include "l_CollisionComponent.hpp"
#include "l_PhysicsComponent.hpp"
#include "l_Component.hpp"
#include "l_TimeManager.hpp"

//from physics
#include "physics/l_AbstractForceGenerator.hpp"
#include "physics/l_ForceGenerator.hpp"
#include "physics/l_PhysicsRegistry.hpp"

//DEFINITIONS

//the name of the library to store all of our lua bindings
#define KF_LUA_LIBNAME "kf"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class LuaScript {
private:
    lua_State *L;
public:
    LuaScript(Kampf* kf = nullptr);
    virtual ~LuaScript();

    lua_State* getState();

    void setGlobal(stringType, floatType);
    floatType getGlobal_float(stringType);
    void setGlobal(stringType, integerType);
    integerType getGlobal_int(stringType);
    void setGlobal(stringType, stringType);
    stringType getGlobal_string(stringType);
    void setGlobal(stringType, floatArrayType);
    floatArrayType getGlobal_floatArray(stringType);
    void setGlobal(stringType, intArrayType);
    intArrayType getGlobal_intArray(stringType);

    //load script from the given file path
    boolType loadScript(stringType);

    //load string into the lua REPL
    boolType loadString(stringType, stringType name = "stdin");
  
    //run the interpreter
    void runInterpreter();

    //path functions
    void addPath(stringType);
    void clearPath();
};

#endif //END LUASCRIPT__HPP
