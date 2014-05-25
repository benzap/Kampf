#ifndef GRAVITYFORCEGENERATOR__HPP
#define GRAVITYFORCEGENERATOR__HPP
//DESCRIPTION
/*
  A force generator for gravity forces
 */

//CLASSES
class GravityForceGenerator;

//INCLUDES
#if defined(KF_WIN)

#include "../KF_globals.hpp"
#include "../KF_utilities.hpp"
#include "../KF_math.hpp"

#else

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"

#endif

#include "AbstractForceGenerator.hpp"


//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class GravityForceGenerator : public AbstractForceGenerator {
private:
    Vector3 gravity;
public:
    GravityForceGenerator(stringType generatorName);
    virtual ~GravityForceGenerator();

    const Vector3& getGravity();
    void setGravity(Vector3 value);
    
    void update(floatType timeDelta_ms);
};

#endif //END GRAVITYFORCEGENERATOR__HPP
