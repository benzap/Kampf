#ifndef COLLISIONSYSTEM__HPP
#define COLLISIONSYSTEM__HPP
//DESCRIPTION
/*
  The collision system performs computations on entities with
  collision components to work out if they have collided with anything
  else.
 */

//CLASSES
class CollisionSystem;

//INCLUDES
#include <unordered_set>
#include <tuple>

#include "AbstractSystem.hpp"
#include "EntityManager.hpp"
#include "CollisionComponent.hpp"
#include "Messenger.hpp"
#include "collision/KF_collision.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//Tuple representation of an active collision
typedef std::pair<CollisionComponent*, CollisionComponent*> activeCollisionTuple;

//CollisionTuple hash class
class CollisionHash {
public:
    std::size_t operator() (const activeCollisionTuple& tuple) const {
	auto hashValue = std::hash<CollisionComponent*>()(tuple.first) +
	    std::hash<stringType>()(tuple.first->getName()) +
	    std::hash<CollisionComponent*>()(tuple.second);
	return hashValue;
    }
};

//used to store a mapping of each of the currently active collisions
typedef std::unordered_set<activeCollisionTuple, CollisionHash> collisionContainerType;

//FUNCTIONS

//BEGIN
class CollisionSystem : public AbstractSystem {
private:
    collisionContainerType collisionContainer;

    //Checks if the two given components are currently colliding
    bool hasCollision(CollisionComponent* firstComponent, CollisionComponent* secondComponent);

    //Adds a new collision to the collision collection
    void addCollision(CollisionComponent* firstComponent, CollisionComponent* secondComponent);

    //Removes an active collision
    void removeCollision(CollisionComponent* firstComponent, CollisionComponent* secondComponent);

    COL_circle gen_circle(CollisionComponent*, PhysicsComponent*);
    COL_rect gen_rect(CollisionComponent*, PhysicsComponent*);

public:
    CollisionSystem();
    virtual ~CollisionSystem();
    
    void createMessages();
    void process();
    boolType checkCollisions(Entity* firstEntity,
			     CollisionComponent* firstColl,
			     Entity* secondEntity,
			     CollisionComponent* secondColl);
};

#endif //END COLLISIONSYSTEM__HPP
