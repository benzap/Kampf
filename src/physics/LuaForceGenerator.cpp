#include "LuaForceGenerator.hpp"

void LuaWrap_GeneratorUpdateFunction::operator () (floatType timeDelta_ms) {
    //push our function onto the stack
    lua_pushFunctionRef(L, this->luaFunctionRef);
    lua_pushnumber(L, timeDelta_ms);
    
    //call the function,
    int numargs = 1, numresults = 0;
    int chk = lua_pcall(L, numargs, numresults, 0);
    
    //check if we had any errors
    if (chk) {
	//generate an error message
	lua_pcall_generateErrorMessage(L, chk);
    }
}

LuaForceGenerator::LuaForceGenerator(stringType generatorName,
				     LuaWrap_GeneratorUpdateFunction func) :
    AbstractForceGenerator(generatorName),
    genUpdateFunction(func) {
    
    }

LuaForceGenerator::~LuaForceGenerator() {
    
}

void LuaForceGenerator::update(floatType timeDelta_ms) {
    this->genUpdateFunction(timeDelta_ms);
}
