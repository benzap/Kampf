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

//CLASSES
class Kampf;


//DEFINITIONS

//MACROS

//TYPEDEFS
typedef std::vector<AbstractSystem*> systemContainerType;

//FUNCTIONS

//BEGIN
class Kampf {
 private:
  AbstractRenderWindow* windowContext;
  systemContainerType systemList;
  Messenger* messenger;
  RuleMachine* ruleMachine;
 public:
  Kampf();
  virtual ~Kampf();

  void runMainLoop();
  
  const AbstractRenderWindow* getRenderWindow();
  const AbstractSystem* getSystem(stringType systemType);
  const Messenger* getMessenger();
  const RuleMachine* getRuleMachine();

};

#endif //END KAMPF__HPP
