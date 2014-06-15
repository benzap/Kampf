#include "LuaForceGenerator.hpp"

void LuaWrap_GeneratorUpdateFunction::operator () (generatorContainerType collidables,
						   floatType timeDelta_ms) {
    //push our function onto the stack
    lua_pushFunctionRef(L, this->luaFunctionRef);

    //need to push our collidables onto the stack
    lua_createtable(L, collidables.size(), 0);
    for (int i = 0; i < collidables.size(); i++) {
	lua_pushcollisionComponent(L, collidables[i]);
	lua_rawseti(L, -2, i+1);
    }

    //pushing the time delta onto the stack
    lua_pushnumber(L, timeDelta_ms);
    
    //call the function,
    int numargs = 2, numresults = 0;
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
    this->genUpdateFunction(this->getRegisteredComponents(),
			    timeDelta_ms);
}

