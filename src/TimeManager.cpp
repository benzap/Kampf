#include "TimeManager.hpp"

void TimeManager::cleanActiveContainer() {

}

guidType TimeManager::appendTime(int offset) {
    if (offset > 0) {
	
    }
    return generateGUID();
}
    
void TimeManager::extendTime(guidType timeGuid, timeType duration) {
    
}

boolType TimeManager::hasTime(guidType timeGuid) {
    return false;
}

boolType TimeManager::isActive(guidType timeGuid) {
    return false;
}

void TimeManager::removeTime(guidType timeGuid) {

}

timeType TimeManager::getTime(guidType timeGuid) {
    return 0;
}

partialTimeContainer TimeManager::getNewInactives() {
    return partialTimeContainer();
}
