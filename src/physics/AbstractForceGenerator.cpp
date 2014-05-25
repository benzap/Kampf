#include "AbstractForceGenerator.hpp"

AbstractForceGenerator::AbstractForceGenerator(stringType generatorName) :
    generatorName(generatorName) {
    
}

stringType AbstractForceGenerator::getName() {
    return generatorName;
}

void AbstractForceGenerator::registerComponent(CollisionComponent* component) {
    this->componentList.push_back(component);
}

void AbstractForceGenerator::unregisterComponent(CollisionComponent* component) {
    auto containerIterator = std::find(componentList.begin(),
				       componentList.end(),
				       component);
    
    this->componentList.erase(containerIterator);
}

boolType AbstractForceGenerator:: hasRegisteredComponent(CollisionComponent* component) {
    auto bCheck = std::find(componentList.begin(),
			    componentList.end(),
			    component);
    
    if (bCheck != componentList.end()) {
	return true;
    }
    return false;
}

