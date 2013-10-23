#include "kampf.hpp"

Kampf::Kampf(enumInitType initType,
	     enumWindowType windowType,
	     enumRenderType renderType) : 
  windowContext(nullptr),
  messenger(Messenger::getInstance()),
  ruleMachine(new RuleMachine()),
  lua(new LuaScript()) {

  //set the OS
#if defined(KF_WIN)
  lua->setGlobal("KF_OS", "WIN32");
#elif defined(KF_LINUX)
  lua->setGlobal("KF_OS", "LINUX");
#else
  lua->setGlobal("KF_OS", "UNKNOWN");
#endif

  //find out the filename of the current executable
  stringType executablePath = "none";

#if defined(KF_WIN)
  TCHAR szPath[MAX_PATH];
  if(!GetModuleFileName(NULL, szPath, MAX_PATH)) {
    std::cerr << "Warning: Could not get filename, setting to none" << std::endl;
  }
  else {
    executablePath = szPath;
  }
#elif defined(KF_LINUX)
  //not implemented, yet
  executablePath = "none";
#else
  //not implemented
  executablePath = "none";
#endif
  lua->setGlobal("KF_EXEC_PATH", executablePath);

  //execute our main script
  lua->loadScript(KF_INIT_FILE);

  //the intialization of the kampf configuration
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
    
    //add a quit function
    RuleCondition condQuit = [] (Message msg) {
      if (msg.getType() == enumMessageType::EVENT_QUIT) {
	return true;
      }
      return false;
    };
    
    RuleFunction funcQuit = [this] (Message msg) {
      this->bRunning = false;
    };

    this->ruleMachine->addRule(condQuit, funcQuit);

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

void Kampf::runMainLoop(Uint32 duration) {
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

    //only run the loop for the duration, ignore if it's -1
    if (duration > 0) {
      Uint32 numTicks = SDL_GetTicks();
      if (duration <= numTicks) {
	this->bRunning = false;
	break;
      }
    }
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
