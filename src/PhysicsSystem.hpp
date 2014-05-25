#ifndef PHYSICSSYSTEM__HPP
#define PHYSICSSYSTEM__HPP
//DESCRIPTION
/*
  System used to deal with physics components and handle the per frame
  changes of entities. Interactions between entities is handled by the
  collision system.
*/

//INCLUDES
#include <vector>
#include <algorithm>

#include <SDL2/SDL.h>

#include "KF_math.hpp"
#include "AbstractSystem.hpp"
#include "EntityManager.hpp"
#include "physics/KF_physics.hpp"

//CLASSES
class PhysicsSystem;

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class PhysicsSystem : public AbstractSystem {
private:
    timeType previousTime = SDL_GetTicks();
    timeType currentTime = 0;

    std::vector<AbstractForceGenerator*> generatorContainer;
public:
    PhysicsSystem();
    virtual ~PhysicsSystem();

    //Generator methods
    void addForceGenerator(AbstractForceGenerator* generator);
    void removeForceGenerator(AbstractForceGenerator* gen);
    void removeForceGenerator(stringType generatorName);
    AbstractForceGenerator* getForceGenerator(stringType generatorName);
    boolType hasForceGenerator(stringType generatorName);
    const std::vector<AbstractForceGenerator*>& getForceGeneratorContainer();
    
    void createMessages();
    void process();
};

#endif //END PHYSICSSYSTEM__HPP
