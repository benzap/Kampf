#include "PhysicsSystem.hpp"
#include <cassert>

PhysicsSystem::PhysicsSystem() :
    AbstractSystem("Physics") {
  
}

PhysicsSystem::~PhysicsSystem() {

}

void PhysicsSystem::createMessages() {

}

void PhysicsSystem::process() {
    auto entityManager = EntityManager::getInstance();

    //get the time delta
    this->currentTime = SDL_GetTicks();

    //change in delta in ms
    timeType timeDelta_ms = this->currentTime - this->previousTime;
    
    //no quantifiable time has passed
    if (timeDelta_ms <= 0) {
	return;
    }

    //the timeDelta should be expressed in seconds
    floatType timeDelta_sec = static_cast<floatType>(timeDelta_ms) / 1000.;

    //need to add the forces to our physics components
    //TODO:
    auto physicsRegistry = PhysicsRegistry::getInstance();
    for (auto gen : physicsRegistry->getForceGeneratorContainer()) {
	gen->update((floatType) timeDelta_ms);
    }
    
    for (auto entity : entityManager->getEntities()) {
	auto physicsComponentList = entity->getComponentsByFamily(enumComponentFamily::PHYSICS);
	for (auto component : physicsComponentList) {
	    auto physicsComponent = static_cast<PhysicsComponent*>(component);
	    //Return if our entity has infinite mass
	    if (physicsComponent->getInverseMass() == 0.) {
		return;
	    }
	    
	    auto position = physicsComponent->getPosition();
	    auto velocity = physicsComponent->getVelocity();

	    //change our position based on velocity
	    position += velocity * timeDelta_sec;

	    //reapply the new position to our physics component
	    physicsComponent->setPosition(position);

	    auto acceleration = physicsComponent->getAcceleration();
	    Vector3 forceAccum = physicsComponent->getForceAccumulator();
	    auto inverseMass = physicsComponent->getInverseMass();
	    
	    //Add our accumulated force to the acceleration
	    acceleration += forceAccum * inverseMass;

	    //change our velocity based on the current acceleration
	    velocity += acceleration * timeDelta_sec;
	    
	    //Impose drag based on our damping
	    auto damping = physicsComponent->getDamping();
	    velocity *= pow(damping, timeDelta_sec);

	    //reapply our new velocity to our physics component
	    physicsComponent->setVelocity(velocity);

	    //reapply our new acceleration to our physics component
	    physicsComponent->setAcceleration(acceleration);

	    //clear the accumulated force
	    physicsComponent->clearForceAccumulator();
	}
    }

    //set our previous time to current time for next iteration
    this->previousTime = this->currentTime;
}
