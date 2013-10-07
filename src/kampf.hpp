#ifndef KAMPF__HPP
#define KAMPF__HPP
//DESCRIPTION
/*
  This is the one include required to include the kampf game engine
 */

//INCLUDES
#include <vector>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "Components.hpp"
#include "Entities.hpp"
#include "Managers.hpp"
#include "Systems.hpp"
#include "Messenger.hpp"
#include "RuleMachine.hpp"
#include "RenderWindows.hpp"
#include "Messenger.hpp"
#include "Message.hpp"

//CLASSES
class Kampf;

//DEFINITIONS

//ENUMS
enum class enumInitType {
  Server,
  Basic,
  Manual
};

enum class enumWindowType {
  SDL,
  SFML
};

enum class enumRenderType {
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

 public:
  Kampf(enumInitType initType = enumInitType::Basic,
	enumWindowType windowType = enumWindowType::SDL,
	enumRenderType renderType = enumRenderType::SDL);
  virtual ~Kampf();

  void runMainLoop();
  
  AbstractRenderWindow* getRenderWindow();
  AbstractSystem* getSystem(stringType systemType);
  void addSystem(AbstractSystem*);
  Messenger* getMessenger();
  RuleMachine* getRuleMachine();

};

#endif //END KAMPF__HPP
