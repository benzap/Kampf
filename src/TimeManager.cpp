#include <cassert>
#include "TimeManager.hpp"

//Define Statics
timeTuple TimeManager::nullTime = timeTuple(0, "0000-00000-000000");
guidType TimeManager::kUseLastGuid = "";
guidType TimeManager::ticker_lastId = kUseLastGuid;


void TimeManager::cleanActiveContainer() {

}

const timeContainerType& TimeManager::getActiveContainer() {
    return activeTimeContainer;
}

const timeContainerType& TimeManager::getInactiveContainer() {
    return inActiveTimeContainer;
}

guidType TimeManager::appendTime(int offset) {
    auto timeGuid = generateGUID();
    auto timeValue = SDL_GetTicks();
    auto timePair = timeTuple(timeValue, timeGuid);

    //if the offset is greater than zero, we add to active container
    if (offset > 0) {
	activeTimeContainer.insert(timePair);
    }
    else {
	inActiveTimeContainer.insert(timePair);
    }
    
    return timeGuid;
}
    
void TimeManager::extendTime(guidType timeGuid, timeType duration) {
    
}

boolType TimeManager::hasTime(guidType timeGuid) {
    if (hasActiveTime(timeGuid) || hasInactiveTime(timeGuid)) {
	return true;
    }

    return false;
}

boolType TimeManager::hasActiveTime(guidType timeGuid) {
    //check the active container
    for (auto timeTuple : activeTimeContainer) {
	if (timeTuple.second == timeGuid) {
	    return true;
	}
    }
    return false;
}

boolType TimeManager::hasInactiveTime(guidType timeGuid) {
    //check the inactive container
    for (auto timeTuple : inActiveTimeContainer) {
	if (timeTuple.second == timeGuid) {
	    return true;
	}
    }
    return false;
}

boolType TimeManager::isActive(guidType timeGuid) {
    return hasActiveTime(timeGuid);
}

void TimeManager::removeTime(guidType timeGuid) {
    assert(hasTime(timeGuid) || "given timeGuid doesn't exist");

    auto timeTuple = getTimeTuple(timeGuid);
    if (hasActiveTime(timeGuid)) {
	activeTimeContainer.erase(timeTuple);
    }
    else if (hasInactiveTime(timeGuid)) {
	inActiveTimeContainer.erase(timeTuple);
    }
    else {
	std::cerr << "Warning: given timeGuid " << timeGuid << " DNE" << std::endl;
    }
}

const timeTuple& TimeManager::getTimeTuple(guidType timeGuid) {
    assert(hasTime(timeGuid) || "given timeGuid doesn't exist");

    //check if it's within the active time container
    for (auto& timeTuple : activeTimeContainer) {
	if (timeTuple.second == timeGuid) {
	    return timeTuple;
	}
    }

    //check if it's within the active time container
    for (auto& timeTuple : inActiveTimeContainer) {
	if (timeTuple.second == timeGuid) {
	    return timeTuple;
	}
    }

    return TimeManager::nullTime;
}

timeType TimeManager::getTime(guidType timeGuid) {
    auto timeTuple = getTimeTuple(timeGuid);
    
    return timeTuple.first;
}

partialTimeContainer TimeManager::getNewInactives() {
    return partialTimeContainer();
}
