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
PhysicsComponent* createPhysicsComponent(
    stringType name, boolType bIsParent = true);


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

    virtual AbstractComponent* createChild(stringType name);

    void setPosition(Vector3);
    const Vector3& getPosition();

    void setVelocity(Vector3);
    const Vector3& getVector();
    
    void setAcceleration(Vector3);
    const Vector3& getAcceleration();

    void setOrientation(Quaternion);
    const Quaternion& getOrientation();

    void setDamping(floatType);
    floatType getDamping();

    void setMass(floatType);
    floatType getMass();
};

#endif //END PHYSICSCOMPONENT__HPP
