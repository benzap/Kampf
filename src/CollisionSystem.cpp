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
			floatType penetration = -1 * getSeparation(firstColl, secondColl);
			msg->customData["penetration"] = CustomAttribute(penetration);
			Vector3 contactNormal = getContactNormal(firstColl, secondColl);
			msg->customData["contactNormal"] = CustomAttribute(contactNormal);

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
			floatType penetration = -1 * getSeparation(firstColl, secondColl);
			msg->customData["penetration"] = CustomAttribute(penetration);
			Vector3 contactNormal = getContactNormal(firstColl, secondColl);
			msg->customData["contactNormal"] = CustomAttribute(contactNormal);

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
    
    //get the types for each component
    auto firstType = firstColl->getCollisionType();
    auto secondType = secondColl->getCollisionType();

    boolType bCollided = false;
    if (firstType == enumCollisionType::CIRCLE) {
	//handling circle to circle collisions
	if (secondType == enumCollisionType::CIRCLE) {
	    bCollided = check_circle_circle(gen_circle(firstColl, firstPhys),
					    gen_circle(secondColl, secondPhys));
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
	    bCollided = check_rect_rect(gen_rect(firstColl, firstPhys),
					gen_rect(secondColl, secondPhys));
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

floatType CollisionSystem::getSeparation(CollisionComponent* first,
					 CollisionComponent* second) {
    //get the physics relations
    auto firstPhys = first->getPhysicsRelation();
    auto secondPhys = second->getPhysicsRelation();
    
    //get the types for each component
    auto firstType = first->getCollisionType();
    auto secondType = second->getCollisionType();


    floatType separation = 0;
    if (firstType == enumCollisionType::CIRCLE) {
	//handling circle to circle collisions
	if (secondType == enumCollisionType::CIRCLE) {
	    separation = get_circle_circle_separation(gen_circle(first, firstPhys),
						      gen_circle(second, secondPhys));
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
	    //do something
	}
    }
    
    return separation;
}

Vector3 CollisionSystem::getContactNormal(CollisionComponent* first,
					  CollisionComponent* second) {
    //get the physics relations
    auto firstPhys = first->getPhysicsRelation();
    auto secondPhys = second->getPhysicsRelation();
    
    //get the types for each component
    auto firstType = first->getCollisionType();
    auto secondType = second->getCollisionType();

    Vector3 contactNormal = Vector3();
    if (firstType == enumCollisionType::CIRCLE) {
	//handling circle to circle collisions
	if (secondType == enumCollisionType::CIRCLE) {
	    contactNormal = get_circle_circle_contactNormal(gen_circle(first, firstPhys),
							    gen_circle(second, secondPhys));
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
	    //do something
	}
    }
    
    return contactNormal;
}
