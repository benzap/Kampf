#include "kampf.hpp"

Kampf::Kampf(enumInitType initType,
	     enumWindowType windowType,
	     enumRenderType renderType) : 
  windowContext(nullptr),
  messenger(Messenger::getInstance()),
  ruleMachine(new RuleMachine()) {
  if (initType == enumInitType::Basic || initType == enumInitType::Manual) {
    if (windowType == enumWindowType::SDL) {
      this->windowContext = new SDLRenderWindow();
      
      auto sdlContext = static_cast<SDLRenderWindow*> (this->windowContext);
      
      //TODO: grab from configuration file
      sdlContext->setWindowFlags(0);

      if (renderType == enumRenderType::SDL) {
	sdlContext->setRendererFlags(SDL_RENDERER_ACCELERATED);
      }
    }
  
    if (windowType == enumWindowType::SFML) {
      std::cerr << "Window Type SFML currently isn't supported" << std::endl;
    }
    
    //initialize our render window
    this->windowContext->initialize();
  }
  else if (initType == enumInitType::Server) {
    //do nothing and ignore other values
  }
  
  //add our systems
  
  //the SDL event system
  auto eventSystem = new EventSystem();
  this->addSystem(eventSystem);

  

}

Kampf::~Kampf() {
  delete windowContext;
  //delete messenger;
  delete ruleMachine;
}

void Kampf::runMainLoop() {
  auto messenger = this->getMessenger();
  auto rulemachine = this->getRuleMachine();

  this->bRunning = true;
  while(this->bRunning) {
    for (auto system : this->systemList) {
      system->createMessages();
    }

    for (auto system : this->systemList) {
      system->process();
    }

    //run the rule machine
    rulemachine->process();
    
    messenger->clearMessages();
  }
}
  
AbstractRenderWindow* Kampf::getRenderWindow() {
  return this->windowContext;
}

AbstractSystem* Kampf::getSystem(stringType systemType) {
  return nullptr;
}

void Kampf::addSystem(AbstractSystem* system) {
  this->systemList.push_back(system);
}

Messenger* Kampf::getMessenger() {
  return this->messenger;
}

RuleMachine* Kampf::getRuleMachine() {
  return this->ruleMachine;
}
