#ifndef COLLISIONCOMPONENT__HPP
#define COLLISIONCOMPONENT__HPP
//DESCRIPTION
/*
  Includes the collision component, which is used to resmbles an entities
  collision with another entity. Entities can consist of several
  collision components within a hierarchy, with deeper hierachies
  resembling more finely honed pieces to encompass the thing that we
  are checking against.
 */

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#include "AbstractComponent.hpp"

//CLASSES
class CollisionComponent;
//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class CollisionComponent : public AbstractComponent {
private:
  Vector position;
  //rotation
  Vector origin;
  
public:
  CollisionComponent(stringType name, 
		     bool bIsParent = true);
  
  virtual ~CollisionComponent();
};

#endif //END COLLISIONCOMPONENT__HPP
