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

		    //boolean resembling if the two component were
		    //already known to be colliding
		    boolType bActiveCollision = this->hasCollision(firstColl, secondColl);

		    //If we collided, but it was already known
		    if (chk && bActiveCollision) {
			//do nothing...
		    }
		    //If we collided, but it wasn't known
		    else if (chk && !bActiveCollision) {
			//create a message with a collision designation
			auto messenger = Messenger::getInstance();
			auto msg = messenger->appendMessage();
			msg->setType(enumMessageType::COLLISION);
			msg->firstEntity = firstEntity;
			msg->firstComponent = firstColl;
			msg->secondEntity = secondEntity;
			msg->secondComponent = secondColl;
			
			//include boolean that it's a registered collision
			msg->customData["bRegistered"] = CustomAttribute(true);

			//add the new collision to our list of active collisions
			this->addCollision(firstColl, secondColl);
		    }
		    //We were an active collision, but it isn't an
		    //active collision anymore. So inform the
		    //listeners that it stopped colliding.
		    else if (!chk && bActiveCollision) {
			//create a message with a collision designation
			auto messenger = Messenger::getInstance();
			auto msg = messenger->appendMessage();
			msg->setType(enumMessageType::COLLISION);
			msg->firstEntity = firstEntity;
			msg->firstComponent = firstColl;
			msg->secondEntity = secondEntity;
			msg->secondComponent = secondColl;
			
			//include boolean that it's not registered anymore
			msg->customData["bRegistered"] = CustomAttribute(false);
		
			//remove the active collision from our container
			removeCollision(firstColl, secondColl);
		    }
		    //nothing happened
		    else {
			//
		    }
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
    COL_rect first_rect, second_rect;

    //get the types for each component
    auto firstType = firstColl->getCollisionType();

    //generate based on type

    //the circle is radiating out from the origin
    if (firstType == enumCollisionType::CIRCLE) {
	first_circle = gen_circle(firstColl, firstPhys);
    }

    //the rectangle is radiating out from the origin
    else if (firstType == enumCollisionType::AABB) {
	first_rect = gen_rect(firstColl, firstPhys);
    }
    
    auto secondType = secondColl->getCollisionType();

    if (secondType == enumCollisionType::CIRCLE) {
	second_circle = gen_circle(secondColl, secondPhys);
    }
    else if (secondType == enumCollisionType::AABB) {
	second_rect = gen_rect(secondColl, secondPhys);
    }

    boolType bCollided = false;
    if (firstType == enumCollisionType::CIRCLE) {
	//handling circle to circle collisions
	if (secondType == enumCollisionType::CIRCLE) {
	    bCollided = check_circle_circle(first_circle, second_circle);
	}
	else if (secondType == enumCollisionType::AABB) {
	    //do something
	}
    }
    else if (firstType == enumCollisionType::AABB) {
	if (secondType == enumCollisionType::CIRCLE) {
	    //do something
	}
	else if (secondType == enumCollisionType::AABB) {
	    bCollided = check_rect_rect(first_rect, second_rect);
	}
    }
    


    return bCollided;
}


bool CollisionSystem::hasCollision(CollisionComponent* firstComponent,
				   CollisionComponent* secondComponent) {
    //generate our tuple
    auto collisionTuple = activeCollisionTuple(firstComponent, secondComponent);
    if (collisionContainer.find(collisionTuple) != collisionContainer.end()) {
	return true;
    }
    return false;
}


void CollisionSystem::addCollision(CollisionComponent* firstComponent,
				   CollisionComponent* secondComponent) {
    auto collisionTuple = activeCollisionTuple(firstComponent, secondComponent);
    collisionContainer.insert(collisionTuple);
}


void CollisionSystem::removeCollision(CollisionComponent* firstComponent,
				      CollisionComponent* secondComponent) {
    auto collisionTuple = activeCollisionTuple(firstComponent, secondComponent);
    collisionContainer.erase(collisionTuple);
}

COL_circle CollisionSystem::gen_circle(CollisionComponent* collision, PhysicsComponent* physics) {
    COL_circle circle;
    circle.center = physics->getPosition();
    circle.center += collision->getOrigin();
    circle.center += collision->getOffset();
    circle.radius = collision->getRadius();

    return circle;
}

COL_rect CollisionSystem::gen_rect(CollisionComponent* collision, PhysicsComponent* physics) {
    COL_rect rectangle;
    
    Vector3 offset = collision->getOffset();
    Vector3 position = physics->getPosition();

    rectangle.min = position;
    rectangle.min += offset;

    Vector3 maxPoint = Vector3(position.x + collision->getWidth(),
			       position.y + collision->getHeight(),
			       0);
    
    rectangle.max = maxPoint + offset;

    return rectangle;
}
