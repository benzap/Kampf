#ifndef PHYSICSREGISTRY__HPP
#define PHYSICSREGISTRY__HPP
//DESCRIPTION
/*
  The physics registry is used to add certain physics functionality.
  - Add / Remove Force Generators
 */

//CLASSES
class PhysicsRegistry;

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
class PhysicsRegistry {
private:
    PhysicsRegistry() {}
    PhysicsRegistry(PhysicsRegistry const&);
    void operator=(PhysicsRegistry const&);
    
    std::vector<AbstractForceGenerator*> generatorContainer;
public:
    static PhysicsRegistry* getInstance() {
	static PhysicsRegistry _instance = PhysicsRegistry();
	return &_instance;
    }

    //Generator methods
    void addForceGenerator(AbstractForceGenerator* generator);
    void removeForceGenerator(AbstractForceGenerator* gen);
    void removeForceGenerator(stringType generatorName);
    AbstractForceGenerator* getForceGenerator(stringType generatorName);
    boolType hasForceGenerator(stringType generatorName);
    const std::vector<AbstractForceGenerator*>& getForceGeneratorContainer();
};

#endif //END PHYSICSREGISTRY__HPP
