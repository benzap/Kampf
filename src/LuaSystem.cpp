#include "LuaSystem.hpp"


LuaSystem::LuaSystem(stringType type,
		     LuaWrap_VoidFunction createMessages,
		     LuaWrap_VoidFunction process) :
    AbstractSystem(type),
    func_createMessages(createMessages),
    func_process(process) {
    
}
    
LuaSystem::~LuaSystem() {}

void LuaSystem::createMessages() {
    this->func_createMessages();
}

void LuaSystem::process() {
    this->func_process();
}
