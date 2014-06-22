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

//ENUM
enum class enumPhysicsType {
    NONE,
	RIGID,
	PARTICLE,
	CUSTOM
	};

//FUNCTIONS
PhysicsComponent* createPhysicsComponent(
    stringType name, boolType bIsParent = true);


//BEGIN
class PhysicsComponent : public AbstractComponent {
private:
    enumPhysicsType physicsType = enumPhysicsType::NONE;
    
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

    
    Vector3 scale = Vector3(1,1,1);
    Quaternion orientation;

    floatType damping = 1;
    floatType inverseMass = 1;
    
    //related to the coefficient of restitution
    floatType elasticity = 1;

    Vector3 forceAccumulator = Vector3(0,0,0);

public:
    PhysicsComponent(stringType name,
		     bool bIsParent = true);

    virtual ~PhysicsComponent();

    virtual AbstractComponent* createChild(stringType name);

    void setPhysicsType(enumPhysicsType value);
    enumPhysicsType getPhysicsType() const;

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
    floatType getDamping() const;

    void setMass(floatType);
    floatType getMass() const;

    void setInverseMass(floatType);
    floatType getInverseMass() const;

    void setElasticity(floatType);
    floatType getElasticity() const;

    const Vector3& getForceAccumulator();
    void setForceAccumulator(Vector3);
    //adds force to force accumulator
    void addForce(const Vector3&);
    void clearForceAccumulator();
};

#endif //END PHYSICSCOMPONENT__HPP
