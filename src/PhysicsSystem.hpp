#ifndef PHYSICSSYSTEM__HPP
#define PHYSICSSYSTEM__HPP
//DESCRIPTION
/*
  System used to deal with physics components and handle the per frame
  changes of entities. Interactions between entities is handled by the
  collision system.
 */

//INCLUDES
#include "AbstractSystem.hpp"

//CLASSES
class PhysicsSystem;

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class PhysicsSystem : public AbstractSystem {
private:
  
public:
  PhysicsSystem();
  virtual ~PhysicsSystem();

  void createMessages();
  void process();
};

#endif //END PHYSICSSYSTEM__HPP
