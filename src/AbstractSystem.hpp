#ifndef ABSTRACTSYSTEM__HPP
#define ABSTRACTSYSTEM__HPP
//DESCRIPTION
/*
  This is the abstract class for systems, that is inherited for each
  included system.
*/

//CLASSES
class AbstractSystem;

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class AbstractSystem {
private:
    stringType type;

public:
    AbstractSystem(stringType type);
    virtual ~AbstractSystem();

    virtual void createMessages() = 0;
    virtual void process() = 0;
};


#endif //END ABSTRACTSYSTEM__HPP
