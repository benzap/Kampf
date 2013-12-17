#ifndef RULEMACHINE__HPP
#define RULEMACHINE__HPP
//DESCRIPTION
/*
  the rulemachine handles passed in Rules. Rules apply to messages in
  the message queue.
*/

//INCLUDES
#include <functional>
#include <algorithm>
#include <tuple>
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "Messenger.hpp"
#include "Message.hpp"
//CLASSES
class RuleMachine;

//DEFINITIONS

//MACROS

//TYPEDEFS
typedef std::function<boolType(Message*)> RuleCondition;
typedef std::function<void(Message*)> RuleFunction;
typedef std::tuple<RuleCondition, RuleFunction, incrementType> RuleTuple;

//FUNCTIONS

//BEGIN
class RuleMachine {
private:
    std::list<RuleTuple> ruleContainer;
public:
    static incrementType RuleIncrement;

    RuleMachine();
    virtual ~RuleMachine();
    
    void process();
    incrementType addRule(RuleCondition,
			  RuleFunction);

    void removeRule(incrementType);
  
};

#endif //END RULEMACHINE__HPP
