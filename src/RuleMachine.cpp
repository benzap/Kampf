#include "RuleMachine.hpp"

incrementType RuleMachine::RuleIncrement = 1;

RuleMachine::RuleMachine() {

}
  
RuleMachine::~RuleMachine() {

}

void RuleMachine::process() {
    auto messenger = Messenger::getInstance();
    for (auto ruleTuple : this->ruleContainer) {
	RuleCondition conditionFunction;
	RuleFunction expressionFunction;
	incrementType inc;
	std::tie(conditionFunction, expressionFunction, inc) = ruleTuple;

	for (auto msg : messenger->retrieveMessages()) {
	    if (conditionFunction(&msg)) {
		//expressing what I want, if the condition is true
		expressionFunction(&msg);
	    }
	}
    }
}

incrementType RuleMachine::addRule(RuleCondition condition,
			  RuleFunction function) {

    auto ruleTuple = RuleTuple(condition,
			       function,
			       RuleMachine::RuleIncrement);
    this->ruleContainer.push_back(ruleTuple);
    return RuleMachine::RuleIncrement++;
}

void RuleMachine::removeRule(incrementType inc) {
    std::remove_if(this->ruleContainer.begin(),
	this->ruleContainer.end(),
	[&] (RuleTuple& val) {
	    if (std::get<2>(val) == inc) {
		return true;
	    }
	    return false;
	});
}
