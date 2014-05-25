#ifndef PHYSICSCOMPONENT__HPP
#define PHYSICSCOMPONENT__HPP
//DESCRIPTION
/*
  component which holds information on the effects of physics on the object
*/

//CLASSES
class PhysicsComponent;

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"


#include "AbstractComponent.hpp"

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

    
    Vector3 scale = Vector3(1,1,1);
    Quaternion orientation;

    floatType damping = 1;
    floatType inverseMass = 1;

    Vector3 forceAccumulator = Vector3(0,0,0);

public:
    PhysicsComponent(stringType name,
		     bool bIsParent = true);

    virtual ~PhysicsComponent();

    virtual AbstractComponent* createChild(stringType name);

    void setPosition(Vector3);
    const Vector3& getPosition();

    void setVelocity(Vector3);
    const Vector3& getVelocity();
    
    void setAcceleration(Vector3);
    const Vector3& getAcceleration();

    void setScale(Vector3);
    const Vector3& getScale();

    void setOrientation(Quaternion);
    const Quaternion& getOrientation();

    void setDamping(floatType);
    floatType getDamping();

    void setMass(floatType);
    floatType getMass();

    void setInverseMass(floatType);
    floatType getInverseMass();

    const Vector3& getForceAccumulator();
    void setForceAccumulator(Vector3);
    //adds force to force accumulator
    void addForce(const Vector3&);
    void clearForceAccumulator();
};

#endif //END PHYSICSCOMPONENT__HPP
