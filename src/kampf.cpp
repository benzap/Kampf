#include "kampf.hpp"

Kampf::Kampf(enumInitType initType,
	     enumWindowType windowType,
	     enumRenderType renderType) : 
  windowContext(nullptr),
  messenger(nullptr),
  ruleMachine(nullptr) {
  if (initType == enumInitType::Basic || initType == enumInitType::Manual) {
    if (windowType == enumWindowType::SDL) {
      this->windowContext = new SDLRenderWindow();
      
      auto sdlContext = static_cast<SDLRenderWindow*> (this->windowContext);
    
      if (renderType == enumRenderType::SDL) {
	//continue
      }
    }
  }
  else if (initType == enumInitType::Server) {
    //do nothing and ignore other values
  }
  
}

Kampf::~Kampf() {
  delete windowContext;
  delete messenger;
  delete ruleMachine;
}

void Kampf::runMainLoop() {
  this->bRunning = true;
  while(this->bRunning) {
    
  }
}
  
const AbstractRenderWindow* Kampf::getRenderWindow() {
  return this->windowContext;
}

const AbstractSystem* Kampf::getSystem(stringType systemType) {
  return nullptr;
}

const Messenger* Kampf::getMessenger() {
  return this->messenger;
}

const RuleMachine* Kampf::getRuleMachine() {
  return this->ruleMachine;
}
