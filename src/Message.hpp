#ifndef MESSAGE__HPP
#define MESSAGE__HPP
//DESCRIPTION
/*
  This is used to store messages on events, collisions, or anything
  else for that matter.
*/

//CLASSES
class Message;

//INCLUDES
#include <map>

#include "Entities.hpp"
#include "Components.hpp"
#include "CustomAttribute.hpp"

//DEFINITIONS

//MACROS

//ENUMS
enum class enumMessageType {
NONE,
// for collisions between two entities with collision components.
COLLISION,

//events following SDL 
// http://wiki.libsdl.org/SDL_Event
  EVENT_COMMON,
  EVENT_WINDOW,
  EVENT_KEYBOARD,
  EVENT_TEXT_EDIT,
  EVENT_TEXT_INPUT,
  EVENT_MOUSE_MOVE,
  EVENT_MOUSE_BUTTON,
  EVENT_MOUSE_WHEEL,
  EVENT_JOYSTICK_AXIS,
  EVENT_JOYSTICK_BALL,
  EVENT_JOYSTICK_HAT,
  EVENT_JOYSTICK_BUTTON,
  EVENT_JOYSTICK_DEVICE,
  EVENT_CONTROLLER_AXIS,
  EVENT_CONTROLLER_BUTTON,
  EVENT_CONTROLLER_DEVICE,
  EVENT_QUIT,
  EVENT_USER_CUSTOM,
  EVENT_OS,
  EVENT_TOUCH_SINGLE,
  EVENT_TOUCH_MULTI,
  EVENT_TOUCH_DOLLAR,
  EVENT_DRAG_DROP,

//for custom events
  CUSTOM
  };

//TYPEDEFS

//FUNCTIONS


//BEGIN
class Message {
private:
    incrementType id;
    enumMessageType type = enumMessageType::NONE;
public:
    AbstractEntity* firstEntity = nullptr;
    AbstractComponent* firstComponent = nullptr;
    AbstractEntity* secondEntity = nullptr;
    AbstractComponent* secondComponent = nullptr;
    std::map<stringType, CustomAttribute> customData;
    void* data = nullptr;
    
    Message(incrementType id);
    virtual ~Message();
    
    incrementType getID();
    enumMessageType getType();
    stringType getTypeString();
    void setType(enumMessageType);
    void setTypeString(stringType typeString);
};

#endif //END MESSAGE__HPP
