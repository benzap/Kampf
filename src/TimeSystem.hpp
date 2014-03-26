#ifndef TIMESYSTEM__HPP
#define TIMESYSTEM__HPP
//DESCRIPTION
/*
  This system handles any timers, and fires appropriate messages onto
  the messenger informing of any times that have surpassed the current
  tick time (expressed in milliseconds)
 */

//CLASSES
class TimeSystem;

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"

#include "AbstractSystem.hpp"
#include "TimeManager.hpp"
#include "Messenger.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class TimeSystem : public AbstractSystem {
private:

public:
    TimeSystem();
    virtual ~TimeSystem();

    void createMessages();
    void process();
};

#endif //END TIMESYSTEM__HPP
