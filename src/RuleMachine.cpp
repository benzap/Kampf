#include "RuleMachine.hpp"

RuleMachine::RuleMachine() {
    std::cout << "Rulemachine constructed" << std::endl;
}
  
RuleMachine::~RuleMachine() {
    std::cout << "Rulemachine deconstructed" << std::endl;
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
    auto msg = Messenger::getInstance()->appendMessage();
    if (condition) {
	std::cout << "condition: " << condition(msg) << std::endl;
    }

    if (function) {
	std::cout << "function: running..." << std::endl;
	function(msg);
	std::cout << "function: ran..." << std::endl;
    }

    std::cout << "creating rule" << std::endl;
    auto ruleTuple = RuleTuple(condition, function);

    std::cout << "calling rule stuff" << std::endl;
    ruleTuple.first(msg);
    ruleTuple.second(msg);

    //checking initialization
    auto ruleContainer = this->ruleContainer;

    std::cout << "adding rule" << std::endl;
    this->ruleContainer.push_back(ruleTuple);
    std::cout << "rule added" << std::endl;
}
