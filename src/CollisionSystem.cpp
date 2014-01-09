#include "CollisionSystem.hpp"

CollisionSystem::CollisionSystem() :
    AbstractSystem("Collision") {
  
}

CollisionSystem::~CollisionSystem() {

}

void CollisionSystem::createMessages() {
    auto entityManager = EntityManager::getInstance();
    for (auto firstEntity : entityManager->getEntities()) {
	for (auto secondEntity : entityManager->getEntities()) {
	    if (firstEntity == secondEntity) continue;

	    //grab all of the collision components
	    auto firstCollList = firstEntity->getComponentsByFamily(
		enumComponentFamily::COLLISION);
	    for (auto firstComponent : firstCollList) {
		auto firstColl = static_cast<CollisionComponent*>
		    (firstComponent);
		
		auto secondCollList = secondEntity->getComponentsByFamily(
		    enumComponentFamily::COLLISION);
		
		for (auto secondComponent : secondCollList) {
		    auto secondColl = static_cast<CollisionComponent*>
			(secondComponent);
		    boolType chk = checkCollisions(firstEntity,
						   firstColl,
						   secondEntity,
						   secondColl);
		    
		} //END for (auto secondComponent : secondCollList) {
	    } //END for (auto firstComponent : firstCollList) {
	} //END for (auto secondEntity : entityManager ...
    } //END for (auto firstEntity : entityManager ...
}

void CollisionSystem::process() {

}

boolType CollisionSystem::checkCollisions(Entity* firstEntity, 
					  CollisionComponent* firstColl,
					  Entity* secondEntity,
					  CollisionComponent* secondColl){
    //get the physics relations
    auto firstPhys = firstColl->getPhysicsRelation();
    auto secondPhys = secondColl->getPhysicsRelation();
    
    //collision structures
    COL_circle first_circle, second_circle;


    //get the types for each component
    auto firstType = firstColl->getCollisionType();

    if (firstType == enumCollisionType::CIRCLE) {
	first_circle.center = firstPhys->getPosition();
	first_circle.center += firstColl->getOrigin();
	first_circle.radius = firstColl->getRadius();
    }
    
    auto secondType = secondColl->getCollisionType();

    if (secondType == enumCollisionType::CIRCLE) {
	second_circle.center = secondPhys->getPosition();
	second_circle.center += secondColl->getOrigin();
	second_circle.radius = secondColl->getRadius();
    }
    
    boolType bCollided = false;
    if (firstType == enumCollisionType::CIRCLE) {
	//handling circle to circle collisions
	if (secondType == enumCollisionType::CIRCLE) {
	    bCollided = check_circle_circle(first_circle, second_circle);
	}
    }

    return bCollided;
}
