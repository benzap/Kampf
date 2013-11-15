#include "RuleMachine.hpp"

RuleMachine::RuleMachine() {

}
  
RuleMachine::~RuleMachine() {

}

void RuleMachine::process() {
    auto messenger = Messenger::getInstance();
    for (auto pair : this->ruleContainer) {
	for (auto msg : messenger->retrieveMessages()) {
	    RuleCondition conditionFunction = pair.first;
	    if (conditionFunction(&msg)) {
		//expressing what I want, if the condition is true
		RuleFunction expressionFunction = pair.second;
		expressionFunction(&msg);
	    }
	}
    }
}

void RuleMachine::addRule(RuleCondition condition,
			  RuleFunction function) {
    auto ruleTuple = RuleTuple(condition, function);
    this->ruleContainer.push_back(ruleTuple);
}
