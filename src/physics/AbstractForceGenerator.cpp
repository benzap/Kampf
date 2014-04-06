#include "AbstractForceGenerator.hpp"

AbstractForceGenerator::AbstractForceGenerator(stringType generatorName) :
    generatorName(generatorName) {
    
}

stringType AbstractForceGenerator::getName() {
    return generatorName;
}

void AbstractForceGenerator::registerComponent(AbstractComponent* component) {
    this->componentList.push_back(component);
}

void AbstractForceGenerator::unregisterComponent(AbstractComponent* component) {
    auto containerIterator = std::find(componentList.begin(), componentList.end(), component);
    this->componentList.erase(containerIterator);
}

boolType AbstractForceGenerator:: hasRegisteredComponent(AbstractComponent* component) {
    auto bCheck = std::find(componentList.begin(), componentList.end(), component);
    if (bCheck != componentList.end()) {
	return true;
    }
    return false;
}

