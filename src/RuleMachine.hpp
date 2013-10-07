#ifndef RULEMACHINE__HPP
#define RULEMACHINE__HPP
//DESCRIPTION
/*
  the rulemachine handles passed in Rules. Rules apply to messages in
  the message queue.
 */

//INCLUDES
#include <functional>
#include <tuple>
#include "Messenger.hpp"
#include "Message.hpp"
//CLASSES
class RuleMachine;

//DEFINITIONS

//MACROS

//TYPEDEFS
typedef std::function<bool(Message)> RuleCondition;
typedef std::function<void(Message)> RuleFunction;
typedef std::pair<RuleCondition, RuleFunction> RuleTuple;

//FUNCTIONS

//BEGIN
class RuleMachine {
private:
  std::list<RuleTuple> ruleContainer;
public:
  RuleMachine();
  virtual ~RuleMachine();

  void process();
  void addRule(RuleCondition,
	       RuleFunction);
  
};

#endif //END RULEMACHINE__HPP
