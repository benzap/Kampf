#ifndef MESSAGE__HPP
#define MESSAGE__HPP
//DESCRIPTION
/*!

  @file Message.hpp
  @brief represents a message used by the Messenger
  
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

//! Enumerable used to determine the type of message
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
    CUSTOM,
    //Timed events
    TIMER
};

//TYPEDEFS

//FUNCTIONS

//BEGIN
class Message {
private:

    //! the unique message id
    incrementType id;
    //! the message type
    enumMessageType type = enumMessageType::NONE;
public:
    //! used to store an entity
    AbstractEntity* firstEntity = nullptr;
    //! used to store a component
    AbstractComponent* firstComponent = nullptr;
    //! used to store a second entity
    AbstractEntity* secondEntity = nullptr;
    //! used to store a second component
    AbstractComponent* secondComponent = nullptr;

    //! a map container that stores any custom attributes
    std::map<stringType, CustomAttribute> customData;

    //! a void pointer for storing more custom data
    void* data = nullptr;

    //! Message constructor
    /*!
      @param id the unique id assigned to the message
      
      Messages are typically created through the Messenger
     */
    Message(incrementType id);
    virtual ~Message();

    //! get the ID of the current message
    incrementType getID();

    //! get the type of message
    enumMessageType getType();

    //! get the type of message in the form of a string
    stringType getTypeString();

    //! set the type of message
    void setType(enumMessageType);

    //! set the type of message in the form of a string
    void setTypeString(stringType typeString);
};

#endif //END MESSAGE__HPP
