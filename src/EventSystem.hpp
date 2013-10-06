#ifndef EVENTSYSTEM__HPP
#define EVENTSYSTEM__HPP
//DESCRIPTION
/*
  The event system is used to grab any input that a person performs
  within the system. This is probably the most important system.
 */

//INCLUDES
#include <SDL2/SDL.h>
#include "AbstractSystem.hpp"

//CLASSES
class EventSystem;
class Event;

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class EventSystem {
private:
  
public:
  EventSystem();
  virtual ~EventSystem();

  void createMessages();
  void process();

};

#endif //END EVENTSYSTEM__HPP
