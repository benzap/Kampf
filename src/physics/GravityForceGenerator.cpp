#include "GravityForceGenerator.hpp"

GravityForceGenerator::GravityForceGenerator(stringType generatorName) :
    AbstractForceGenerator(generatorName) {
    
}

GravityForceGenerator::~GravityForceGenerator() {}

const Vector3& GravityForceGenerator::getGravity() {
    return this->gravity;
}

void GravityForceGenerator::setGravity(Vector3 value) {
    this->gravity = value;
}

void GravityForceGenerator::update(floatType timeDelta_ms) {
    //iterate over the list of collision components
    for (auto collisionComponent : this->getRegisteredComponents()) {
	auto physicsComponent = collisionComponent->getPhysicsRelation();
	if (physicsComponent == nullptr) {
	    continue;
	}

	//don't calculate if it doesn't have a finite mass
	auto inverseMass = physicsComponent->getInverseMass();
	if (inverseMass <= 0) {
	    continue;
	}

	physicsComponent->addForce(this->gravity * inverseMass);
    }
}
