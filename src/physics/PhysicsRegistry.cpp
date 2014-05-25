#include "PhysicsRegistry.hpp"
#include <cassert>

void PhysicsRegistry::addForceGenerator(AbstractForceGenerator* generator) {
    this->generatorContainer.push_back(generator);
}

void PhysicsRegistry::removeForceGenerator(AbstractForceGenerator* gen) {
    auto genIter = std::find(this->generatorContainer.begin(),
			     this->generatorContainer.end(),
			     gen);
    this->generatorContainer.erase(genIter);
}

void PhysicsRegistry::removeForceGenerator(stringType generatorName) {
    auto genIter = std::find_if(this->generatorContainer.begin(),
				this->generatorContainer.end(),
				[&] (AbstractForceGenerator* aGenerator) {
				    if (aGenerator->getName() == generatorName) {
					return true;
				    }
				    return false;
				});
    
    this->generatorContainer.erase(genIter);
}

AbstractForceGenerator* PhysicsRegistry::getForceGenerator(stringType generatorName) {
    assert(this->hasForceGenerator(generatorName));
    
    auto genIter = std::find_if(this->generatorContainer.begin(),
			    this->generatorContainer.end(),
			    [&] (AbstractForceGenerator* aGenerator) {
				if (aGenerator->getName() == generatorName) {
				    return true;
				}
				return false;
			    });
    return *genIter;
}

boolType PhysicsRegistry::hasForceGenerator(stringType generatorName) {
    auto genIter = std::find_if(this->generatorContainer.begin(),
			    this->generatorContainer.end(),
			    [&] (AbstractForceGenerator* aGenerator) {
				if (aGenerator->getName() == generatorName) {
				    return true;
				}
				return false;
			    });
    if (genIter != this->generatorContainer.end()) {
	return true;
    }
    return false;
}

const std::vector<AbstractForceGenerator*>& PhysicsRegistry::getForceGeneratorContainer() {
    return this->generatorContainer;
}
