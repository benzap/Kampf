#ifndef COLLISIONSYSTEM__HPP
#define COLLISIONSYSTEM__HPP
//DESCRIPTION
/*
  The collision system performs computations on entities with
  collision components to work out if they have collided with anything
  else.
 */

//INCLUDES
#include "AbstractSystem.hpp"

//CLASSES
class CollisionSystem;

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class CollisionSystem {
private:
  
public:
  CollisionSystem();
  virtual ~CollisionSystem();

  void createMessages();
  void process();
};

#endif //END COLLISIONSYSTEM__HPP
