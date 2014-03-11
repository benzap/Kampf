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
    case enumMessageType::TIMER:
	return "TIMER";

    //Collisions
    case enumMessageType::COLLISION:
	return "COLLISION";
    default:
	return "NONE";
    }
    return "NONE";
}

void Message::setType(enumMessageType type) {
    this->type = type;
}

void Message::setTypeString(stringType typeString) {

    if (typeString == "COMMON") {
	this->setType(enumMessageType::EVENT_COMMON);
    }
    else if (typeString == "WINDOW") {
	this->setType(enumMessageType::EVENT_WINDOW);
    }
    else if (typeString == "KEYBOARD") {
	this->setType(enumMessageType::EVENT_KEYBOARD);
    }
    else if (typeString == "TEXT_EDIT") {
	this->setType(enumMessageType::EVENT_TEXT_EDIT);
    }
    else if (typeString == "TEXT_INPUT") {
	this->setType(enumMessageType::EVENT_TEXT_INPUT);
    }
    else if (typeString == "MOUSE_MOVE") {
	this->setType(enumMessageType::EVENT_MOUSE_MOVE);
    }
    else if (typeString == "MOUSE_BUTTON") {
	this->setType(enumMessageType::EVENT_MOUSE_BUTTON);
    }
    else if (typeString == "MOUSE_WHEEL") {
	this->setType(enumMessageType::EVENT_MOUSE_WHEEL);
    }
    else if (typeString == "JOYSTICK_AXIS") {
	this->setType(enumMessageType::EVENT_JOYSTICK_AXIS);
    }
    else if (typeString == "JOYSTICK_BALL") {
	this->setType(enumMessageType::EVENT_JOYSTICK_BALL);
    }
    else if (typeString == "JOYSTICK_HAT") {
	this->setType(enumMessageType::EVENT_JOYSTICK_HAT);
    }
    else if (typeString == "JOYSTICK_BUTTON") {
	this->setType(enumMessageType::EVENT_JOYSTICK_BUTTON);
    }
    else if (typeString == "JOYSTICK_DEVICE") {
	this->setType(enumMessageType::EVENT_JOYSTICK_DEVICE);
    }
    else if (typeString == "CONTROLLER_AXIS") {
	this->setType(enumMessageType::EVENT_CONTROLLER_AXIS);
    }
    else if (typeString == "CONTROLLER_BUTTON") {
	this->setType(enumMessageType::EVENT_CONTROLLER_BUTTON);
    }
    else if (typeString == "CONTROLLER_DEVICE") {
	this->setType(enumMessageType::EVENT_CONTROLLER_DEVICE);
    }
    else if (typeString == "QUIT") {
	this->setType(enumMessageType::EVENT_QUIT);
    }
    else if (typeString == "USER_CUSTOM") {
	this->setType(enumMessageType::EVENT_USER_CUSTOM);
    }
    else if (typeString == "OS") {
	this->setType(enumMessageType::EVENT_OS);
    }
    else if (typeString == "TOUCH_SINGLE") {
	this->setType(enumMessageType::EVENT_TOUCH_SINGLE);
    }
    else if (typeString == "TOUCH_MULTI") {
	this->setType(enumMessageType::EVENT_TOUCH_MULTI);
    }
    else if (typeString == "TOUCH_DOLLAR") {
	this->setType(enumMessageType::EVENT_TOUCH_DOLLAR);
    }
    else if (typeString == "DRAG_DROP") {
	this->setType(enumMessageType::EVENT_DRAG_DROP);
    }
    else if (typeString == "CUSTOM") {
	this->setType(enumMessageType::CUSTOM);
    }
    else if (typeString == "TIMER") {
	this->setType(enumMessageType::TIMER);
    }
    else if (typeString == "COLLISION") {
	this->setType(enumMessageType::COLLISION);
    }
    else {
	this->setType(enumMessageType::NONE);
    }    
    this->setType(enumMessageType::NONE);
}
