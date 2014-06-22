#include "TimeSystem.hpp"

TimeSystem::TimeSystem() :
    AbstractSystem("Time") {
    
}

TimeSystem::~TimeSystem() {

}

void TimeSystem::createMessages() {
    auto timeManager = TimeManager::getInstance();
    auto messenger = Messenger::getInstance();
    
    for (auto& timeTuple : timeManager->getNewInactives()) {
	auto message = messenger->appendMessage();
	message->setType(enumMessageType::TIMER);
	auto timeGuidAttribute = CustomAttribute(timeTuple.second);
	message->customData["timeGuid"] = timeGuidAttribute;
    }
    timeManager->cleanActiveContainer();
}

void TimeSystem::process() {

}
