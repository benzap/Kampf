#ifndef LUAFORCEGENERATOR__HPP
#define LUAFORCEGENERATOR__HPP
//DESCRIPTION
/*
  Lua binding for force generators. This will represent a force
  generator within lua
 */

//CLASSES
class LuaForceGenerator;
class LuaWrap_GeneratorUpdateFunction;

//INCLUDES
#include <functional>

#if defined(KF_WIN)

#include "../l_Wrapper.hpp"
#include "../l_Wrapper_Utils.hpp"

#else

#include "l_Wrapper.hpp"
#include "l_Wrapper_Utils.hpp"

#endif

#include "AbstractForceGenerator.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class LuaWrap_GeneratorUpdateFunction : public Lua_FunctionWrapper {
public:
    LuaWrap_GeneratorUpdateFunction(lua_State *L, int index) :
	Lua_FunctionWrapper(L, index) {}
    
    void operator () (floatType timeDelta_ms);
    
};

class LuaForceGenerator : public AbstractForceGenerator {
private:
    LuaWrap_GeneratorUpdateFunction genUpdateFunction;
public:
    LuaForceGenerator(stringType generatorName,
		      LuaWrap_GeneratorUpdateFunction func);
    virtual ~LuaForceGenerator();

    void update(floatType timeDelta_ms);
};

#endif //END LUAFORCEGENERATOR__HPP
