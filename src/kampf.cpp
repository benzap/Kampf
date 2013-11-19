#include "kampf.hpp"

#if defined(KF_WIN)
#include <windows.h>
#include <Shlwapi.h>
#endif

Kampf::Kampf(enumInitType initType,
	     enumWindowType windowType,
	     enumRenderType renderType) : 
    windowContext(nullptr),
    messenger(Messenger::getInstance()),
    ruleMachine(new RuleMachine()),
    lua(new LuaScript(this)) {
   
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
	} //END if (windowType == enumWindowType::SDL) {
  
	if (windowType == enumWindowType::SFML) {
	    std::cerr << "Window Type SFML currently isn't supported" << std::endl;
	} //END if (windowType == enumWindowType::SFML) {
    
	//stuff to do that we wouldn't do Manually
	if (initType != enumInitType::Manual) {

	    //add a quit function
	    RuleCondition condQuit = [] (Message* msg) {
		if (msg->getType() == enumMessageType::EVENT_QUIT) {
		    return true;
		}
		return false;
	    };
    
	    RuleFunction funcQuit = [this] (Message* msg) {
		this->bRunning = false;
	    };

	    this->ruleMachine->addRule(condQuit, funcQuit);

	    //initialize our render window
	    this->windowContext->initialize();

	    std::cout << "Initializing Window..." << std::endl;

	    //Adding the graphics system
	    auto graphicsSystem = new GraphicsSystem();
	    this->addSystem(graphicsSystem);
	}
    } //END if (initType == enumInitType::Basic || ...
    else if (initType == enumInitType::Server) {
	//do nothing and ignore other values
    }
  
    //add our systems relevant to all types
  
    //the SDL event system
    auto eventSystem = new EventSystem();
    this->addSystem(eventSystem);

    //run our Lua scripts starting with the init file, after
    //everything has been initialized.  since it's at the end, I
    //figured it would make more sense to do it outside of the
    //constructor when intializing the engine itself, so commented!
    //lua->loadScript(KF_INIT_FILE);
}

Kampf::~Kampf() {
    delete windowContext;
    //delete messenger;
    delete ruleMachine;
}

void Kampf::runMainLoop(int duration) {
    auto messenger = this->getMessenger();
    auto rulemachine = this->getRuleMachine();

    if (duration != KF_LOOP_FOREVER) {
	duration += SDL_GetTicks();
    }

    this->bRunning = true;
    while(this->bRunning) {
	//if our render context is live, clear the screen
	if (this->windowContext != nullptr) {
	    this->windowContext->clear();
	}
    
	//create all of the messages to be passed to the Messenger
	for (auto system : this->systemList) {
	    system->createMessages();
	}

	//have all of the systems process the messages, or simply process
	//relevant stuff
	for (auto system : this->systemList) {
	    system->process();
	}

	//have the rule machine check if any relevant messages are found
	//as well
	rulemachine->process();
    
	//clear out all of the messages for the next iteration
	messenger->clearMessages();

	//finished drawing stuff to the screen, update the screen
	if (this->windowContext != nullptr) {
	    this->windowContext->update();
	}

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

LuaScript* Kampf:: getLua() {
    return this->lua;
}
