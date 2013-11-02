#ifndef PHYSICSCOMPONENT__HPP
#define PHYSICSCOMPONENT__HPP
//DESCRIPTION
/*
  component which holds information on the effects of physics on the object
 */

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"


#include "AbstractComponent.hpp"
//CLASSES
class PhysicsComponent;

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class PhysicsComponent : public AbstractComponent {
private:
  Vector3 position;
  Vector3 velocity;
  Vector3 acceleration;
  
  Quaternion orientation;

  floatType damping;
  floatType inverseMass;

public:
  PhysicsComponent(stringType name,
		   bool bIsParent = true);

  virtual ~PhysicsComponent();
};

#endif //END PHYSICSCOMPONENT__HPP
