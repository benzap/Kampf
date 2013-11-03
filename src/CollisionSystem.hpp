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
#include "AbstractSystem.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class CollisionSystem : public AbstractSystem {
private:
  
public:
  CollisionSystem();
  virtual ~CollisionSystem();

  void createMessages();
  void process();
};

#endif //END COLLISIONSYSTEM__HPP
