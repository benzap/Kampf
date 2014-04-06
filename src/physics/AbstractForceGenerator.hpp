#ifndef ABSTRACTFORCEGENERATOR__HPP
#define ABSTRACTFORCEGENERATOR__HPP
//DESCRIPTION
/*
  Includes an abstract for force generators within the physics system.
  Force generators are containers which assign certain forces to
  registered physics components.
 */

//CLASSES
class AbstractForceGenerator;

//INCLUDES
#include <vector>
#include <algorithm>

#if defined(KF_WIN)

#include "../KF_globals.hpp"
#include "../KF_utilities.hpp"
#include "../KF_math.hpp"
#include "../AbstractComponent.hpp"

#else

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#include "AbstractComponent.hpp"

#endif

//DEFINITIONS

//MACROS

//TYPEDEFS
typedef std::vector<AbstractComponent*> generatorContainerType;

//FUNCTIONS

//BEGIN
class AbstractForceGenerator {
private:
    stringType generatorName;
    generatorContainerType componentList;

public:
    AbstractForceGenerator(stringType generatorName);
    virtual ~AbstractForceGenerator() {};

    stringType getName();

    void registerComponent(AbstractComponent*);
    void unregisterComponent(AbstractComponent*);
    boolType hasRegisteredComponent(AbstractComponent*);
    
    virtual void update() {}

};


#endif //END ABSTRACTFORCEGENERATOR__HPP
