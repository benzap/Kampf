#ifndef KAMPF__HPP
#define KAMPF__HPP
//DESCRIPTION
/*
  This is the one include required to include the kampf game engine
 */

//CLASSES
class Kampf;

//INCLUDES
#include <vector>

#if defined(KF_WIN)
#include <windows.h>
#include <Shlwapi.h>
#endif

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#include "Components.hpp"
#include "Entities.hpp"
#include "Managers.hpp"
#include "Systems.hpp"
#include "Messenger.hpp"
#include "RuleMachine.hpp"
#include "RenderWindows.hpp"
#include "Messenger.hpp"
#include "Message.hpp"
#include "LuaScript.hpp"

//DEFINITIONS
#define KF_LOOP_FOREVER -1

//this is the first and only lua file that is loaded at startup
#define KF_INIT_FILE "kampf.lua"

//ENUMS
enum class enumInitType {
  Server,
  Basic,
  Manual
};

enum class enumWindowType {
  SERVER,
  SDL,
  SFML
};

enum class enumRenderType {
  SERVER,
  SDL,
  OPENGL,
  DIRECTX
};

//MACROS

//TYPEDEFS
typedef std::vector<AbstractSystem*> systemContainerType;

//FUNCTIONS

//BEGIN
class Kampf {
 private:
  bool bRunning = false;
  AbstractRenderWindow* windowContext;
  systemContainerType systemList;
  Messenger* messenger;
  RuleMachine* ruleMachine;
  LuaScript * lua;
 public:
  Kampf(enumInitType initType = enumInitType::Basic,
	enumWindowType windowType = enumWindowType::SDL,
	enumRenderType renderType = enumRenderType::SDL);
  virtual ~Kampf();

  void runMainLoop(Uint32 duration = KF_LOOP_FOREVER);
  
  AbstractRenderWindow* getRenderWindow();
  AbstractSystem* getSystem(stringType systemType);
  void addSystem(AbstractSystem*);
  Messenger* getMessenger();
  RuleMachine* getRuleMachine();
  LuaScript* getLua();
};

#endif //END KAMPF__HPP
