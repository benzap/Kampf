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
  while(SDL_PollEvent(&event)) {
    std::cout << "event polled" << std::endl;
  }
}

void EventSystem::process() {
  
}
