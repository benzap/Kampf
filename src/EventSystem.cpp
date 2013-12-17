#include "EventSystem.hpp"

#include <iostream>

EventSystem::EventSystem() : 
    AbstractSystem("event") {
  SDL_InitSubSystem(SDL_INIT_VIDEO);
}

EventSystem::~EventSystem() {

}

void EventSystem::createMessages() {
  SDL_Event event;
  auto messenger = Messenger::getInstance();
  Message* msg;
  while(SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_QUIT);
    }
    
    else if (event.type == SDL_APP_TERMINATING) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_QUIT);
    }

    else if (event.type == SDL_APP_LOWMEMORY) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_QUIT);
    }

    else if (event.type == SDL_APP_WILLENTERBACKGROUND) {
	
    }

    else if (event.type == SDL_APP_DIDENTERBACKGROUND) {

    }

    else if (event.type == SDL_APP_WILLENTERFOREGROUND) {

    }

    else if (event.type == SDL_APP_DIDENTERFOREGROUND) {

    }

    else if (event.type == SDL_WINDOWEVENT) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_WINDOW);
    }

    else if (event.type == SDL_SYSWMEVENT) {
	
    }

    else if (event.type == SDL_KEYDOWN) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_KEYBOARD);
	std::cout << "key: " << SDL_GetScancodeName(event.key.keysym.scancode);
	std::cout << std::endl;
    }

    else if (event.type == SDL_KEYUP) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_KEYBOARD);
	std::cout << "key: " << SDL_GetScancodeName(event.key.keysym.scancode);
	std::cout << std::endl;
    }

    else if (event.type == SDL_TEXTEDITING) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_TEXT_EDIT);
    }

    else if (event.type == SDL_TEXTINPUT) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_TEXT_INPUT);
    }

    else if (event.type == SDL_MOUSEMOTION) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_MOUSE_MOVE);
    }

    else if (event.type == SDL_MOUSEBUTTONDOWN) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_MOUSE_BUTTON);
    }

    else if (event.type == SDL_MOUSEBUTTONUP) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_MOUSE_BUTTON);
    }

    else if (event.type == SDL_MOUSEWHEEL) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_MOUSE_WHEEL);
    }

    else if (event.type == SDL_JOYAXISMOTION) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_JOYSTICK_AXIS);
    }

    else if (event.type == SDL_JOYBALLMOTION) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_JOYSTICK_BALL);
    }

    else if (event.type == SDL_JOYHATMOTION) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_JOYSTICK_HAT);
    }

    else if (event.type == SDL_JOYBUTTONDOWN) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_JOYSTICK_BUTTON);
    }

    else if (event.type == SDL_JOYBUTTONUP) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_JOYSTICK_BUTTON);
    }

    else if (event.type == SDL_JOYDEVICEADDED) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_JOYSTICK_DEVICE);
    }

    else if (event.type == SDL_JOYDEVICEREMOVED) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_JOYSTICK_DEVICE);
    }

    else if (event.type == SDL_CONTROLLERAXISMOTION) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_CONTROLLER_AXIS);
    }

    else if (event.type == SDL_CONTROLLERBUTTONDOWN) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_CONTROLLER_BUTTON);
    }

    else if (event.type == SDL_CONTROLLERBUTTONUP) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_CONTROLLER_BUTTON);
    }

    else if (event.type == SDL_CONTROLLERDEVICEADDED) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_CONTROLLER_DEVICE);
    }

    else if (event.type == SDL_CONTROLLERDEVICEREMOVED) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_CONTROLLER_DEVICE);
    }

    else if (event.type == SDL_CONTROLLERDEVICEREMAPPED) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_CONTROLLER_DEVICE);
    }

    else if (event.type == SDL_FINGERDOWN) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_TOUCH_SINGLE);
    }

    else if (event.type == SDL_FINGERUP) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_TOUCH_SINGLE);
    }

    else if (event.type == SDL_FINGERMOTION) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_TOUCH_SINGLE);
    }

    else if (event.type == SDL_DOLLARGESTURE) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_TOUCH_DOLLAR);
    }

    else if (event.type == SDL_CLIPBOARDUPDATE) {

    }

    else if (event.type == SDL_DROPFILE) {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::EVENT_TOUCH_SINGLE);
    }

    else if (event.type == SDL_LASTEVENT) {
	
    }

    else {
	msg = messenger->appendMessage();
	msg->setType(enumMessageType::NONE);
    }
  } //END while(...
}

void EventSystem::process() {
  
}
