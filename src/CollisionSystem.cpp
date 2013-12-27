#include "CollisionSystem.hpp"

CollisionSystem::CollisionSystem() :
    AbstractSystem("Collision") {
  
}

CollisionSystem::~CollisionSystem() {

}

void CollisionSystem::createMessages() {
    auto entityManager = EntityManager::getInstance();
    for (auto entity : entityManager->getEntities()) {    
	//grab all of the collision components
	auto collisionList = entity->getComponentsByFamily(
	    enumComponentFamily::COLLISION);
	for (auto component : collisionList) {
	    auto collisionComponent = static_cast<CollisionComponent*>
		(component);
	    
	}
    }
}

void CollisionSystem::process() {

}
