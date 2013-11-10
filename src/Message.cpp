#include "Message.hpp"

Message::Message(incrementType id) : id(id) {
  
}

Message::~Message() {
  
}

incrementType Message::getID() {
  return this->id;
}

enumMessageType Message::getType() {
  return this->type;
}

stringType Message::getTypeString() {
    switch(this->type) {
    case enumMessageType::EVENT_COMMON:
	return "COMMON";
    case enumMessageType::EVENT_WINDOW:
	return "WINDOW";
    case enumMessageType::EVENT_KEYBOARD:
	return "KEYBOARD";
    case enumMessageType::EVENT_TEXT_EDIT:
	return "TEXT_EDIT";
    case enumMessageType::EVENT_TEXT_INPUT:
	return "TEXT_INPUT";
    case enumMessageType::EVENT_MOUSE_MOVE:
	return "MOUSE_MOVE";
    case enumMessageType::EVENT_MOUSE_BUTTON:
	return "MOUSE_BUTTON";
    case enumMessageType::EVENT_MOUSE_WHEEL:
	return "MOUSE_WHEEL";
    case enumMessageType::EVENT_JOYSTICK_AXIS:
	return "JOYSTICK_AXIS";
    case enumMessageType::EVENT_JOYSTICK_BALL:
	return "JOYSTICK_BALL";
    case enumMessageType::EVENT_JOYSTICK_HAT:
	return "JOYSTICK_HAT";
    case enumMessageType::EVENT_JOYSTICK_BUTTON:
	return "JOYSTICK_BUTTON";
    case enumMessageType::EVENT_JOYSTICK_DEVICE:
	return "JOYSTICK_DEVICE";
    case enumMessageType::EVENT_CONTROLLER_AXIS:
	return "CONTROLLER_AXIS";
    case enumMessageType::EVENT_CONTROLLER_BUTTON:
	return "CONTROLLER_BUTTON";
    case enumMessageType::EVENT_CONTROLLER_DEVICE:
	return "CONTROLLER_DEVICE";
    case enumMessageType::EVENT_QUIT:
	return "QUIT";
    case enumMessageType::EVENT_USER_CUSTOM:
	return "USER_CUSTOM";
    case enumMessageType::EVENT_OS:
	return "OS";
    case enumMessageType::EVENT_TOUCH_SINGLE:
	return "TOUCH_SINGLE";
    case enumMessageType::EVENT_TOUCH_MULTI:
	return "TOUCH_MULTI";
    case enumMessageType::EVENT_TOUCH_DOLLAR:
	return "TOUCH_DOLLAR";
    case enumMessageType::EVENT_DRAG_DROP:
	return "DRAG_DROP";
    case enumMessageType::CUSTOM:
	return "CUSTOM";
    default:
	return "NONE";
    }
    return "NONE";
}

void Message::setType(enumMessageType type) {
    this->type = type;
}

void Message::setTypeString(stringType typeString) {
    switch(typeString) {
    case "COMMON":
	this->setType(enumMessageType::EVENT_COMMON);
    case "WINDOW":
	this->setType(enumMessageType::EVENT_WINDOW);
    case "KEYBOARD":
	this->setType(enumMessageType::EVENT_KEYBOARD);
    case "TEXT_EDIT":
	this->setType(enumMessageType::EVENT_TEXT_EDIT);
    case "TEXT_INPUT":
	this->setType(enumMessageType::EVENT_TEXT_INPUT);
    case "MOUSE_MOVE":
	this->setType(enumMessageType::EVENT_MOUSE_MOVE);
    case "MOUSE_BUTTON":
	this->setType(enumMessageType::EVENT_MOUSE_BUTTON);
    case "MOUSE_WHEEL":
	this->setType(enumMessageType::EVENT_MOUSE_WHEEL);
    case "JOYSTICK_AXIS":
	this->setType(enumMessageType::EVENT_JOYSTICK_AXIS);
    case "JOYSTICK_BALL":
	this->setType(enumMessageType::EVENT_JOYSTICK_BALL);
    case "JOYSTICK_HAT":
	this->setType(enumMessageType::EVENT_JOYSTICK_HAT);
    case "JOYSTICK_BUTTON":
	this->setType(enumMessageType::EVENT_JOYSTICK_BUTTON);
    case "JOYSTICK_DEVICE":
	this->setType(enumMessageType::EVENT_JOYSTICK_DEVICE);
    case "CONTROLLER_AXIS":
	this->setType(enumMessageType::EVENT_CONTROLLER_AXIS);
    case "CONTROLLER_BUTTON":
	this->setType(enumMessageType::EVENT_CONTROLLER_BUTTON);
    case "CONTROLLER_DEVICE":
	this->setType(enumMessageType::EVENT_CONTROLLER_DEVICE);
    case "QUIT":
	this->setType(enumMessageType::EVENT_QUIT);
    case "USER_CUSTOM":
	this->setType(enumMessageType::EVENT_USER_CUSTOM);
    case "OS":
	this->setType(enumMessageType::EVENT_OS);
    case "TOUCH_SINGLE":
	this->setType(enumMessageType::EVENT_TOUCH_SINGLE);
    case "TOUCH_MULTI":
	this->setType(enumMessageType::EVENT_TOUCH_MULTI);
    case "TOUCH_DOLLAR":
	this->setType(enumMessageType::EVENT_TOUCH_DOLLAR);
    case "DRAG_DROP":
	this->setType(enumMessageType::EVENT_DRAG_DROP);
    case "CUSTOM":
	this->setType(enumMessageType::CUSTOM);
    default:
	this->setType(enumMessageType::NONE);
    }
    this->setType(enumMessageType::NONE);
}
