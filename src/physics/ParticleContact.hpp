#ifndef PARTICLECONTACT__HPP
#define PARTICLECONTACT__HPP
//DESCRIPTION
/*
  Includes information on a given contact between two particles, or
  between a particle in a wall.
 */

//CLASSES
class ParticleContact;

//INCLUDES
#include <vector>
#include <algorithm>

#if defined(KF_WIN)

#include "../KF_globals.hpp"
#include "../KF_utilities.hpp"
#include "../KF_math.hpp"
#include "../CollisionComponent.hpp"
#include "../PhysicsComponent.hpp"
#include "../Message.hpp"

#else

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#include "CollisionComponent.hpp"
#include "PhysicsComponent.hpp"
#include "Message.hpp"

#endif

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class ParticleContact {
private:
    CollisionComponent* firstCollision = nullptr;
    PhysicsComponent* firstPhysics = nullptr;

    CollisionComponent* secondCollision = nullptr;
    PhysicsComponent* secondPhysics = nullptr;

    floatType restitution = 1.0;
    floatType penetration = 0.0;
    
    Vector3 contactNormal;

    void resolveVelocity(timeType delta_ms);
    void resolveInterpenetration(timeType delta_ms);

public:
    ParticleContact(Message msg);
    virtual ~ParticleContact();

    void resolve(timeType delta_ms);
    floatType calculateSeparationVelocity() const;    
    floatType getPenetration() const;
};

#endif //END PARTICLECONTACT__HPP
