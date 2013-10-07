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
  }
}

void EventSystem::process() {
  
}
