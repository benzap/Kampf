#ifndef EVENTSYSTEM__HPP
#define EVENTSYSTEM__HPP
//DESCRIPTION
/*
  The event system is used to grab any input that a person performs
  within the system. This is probably the most important system.
  
  For now, the event system is hard-coded to use SDL events.
 */

//CLASSES
class EventSystem;

//INCLUDES
#include <SDL2/SDL.h>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "AbstractSystem.hpp"
#include "Messenger.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class EventSystem : public AbstractSystem {
private:
  
public:
  EventSystem();
  virtual ~EventSystem();

  void createMessages();
  void process();

};

#endif //END EVENTSYSTEM__HPP
