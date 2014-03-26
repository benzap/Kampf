#include <iostream>
#include <cassert>
#include <ctime>

#include "KF_test.hpp"
void sleep( clock_t wait ) {
    clock_t goal;
    goal = wait + clock();
    while( goal > clock() )
	;
}

void printTimeTuple(timeTuple theTime) {
    auto currentTime = SDL_GetTicks();
    
    std::cout << "TimeTuple<" << theTime.first << ", " << theTime.second;
    std::cout << "> (" << currentTime << ")" << std::endl;
}



void viewContainers() {
    auto timeManager = TimeManager::getInstance();
    auto currentTime = SDL_GetTicks();

    std::cout << std::endl;
    std::cout << "Viewing at time: " << currentTime << std::endl;
    std::cout << std::endl;
    std::cout << "Inactive Time Container" << std::endl;
    std::cout << "-----------------------" << std::endl;
    for (auto timeTuple : timeManager->getInactiveContainer()) {
	printTimeTuple(timeTuple);
    }

    std::cout << std::endl;
    
    std::cout << "Active Time Container" << std::endl;
    std::cout << "---------------------" << std::endl;
    for (auto timeTuple : timeManager->getActiveContainer()) {
	printTimeTuple(timeTuple);
    }
    
}

int main(int argc, char *argv[]) {
    TEST_NAME("test_TimeManager.cpp");

    auto timeManager = TimeManager::getInstance();

    TEST_BOOL(!timeManager->hasTime(generateGUID()), "hasTime (DNE)");

    auto time1 = timeManager->appendTime();
    TEST_BOOL(timeManager->hasTime(time1), "hasTime (Inactive)");
    TEST_BOOL(timeManager->hasInactiveTime(time1), "hasInactiveTime");
    TEST_BOOL(!timeManager->hasActiveTime(time1), "hasActiveTime (DNE)");
    
    auto time2_active = timeManager->appendTime(1000);
    TEST_BOOL(timeManager->hasTime(time2_active), "hasTime (Active)");
    TEST_BOOL(!timeManager->hasInactiveTime(time2_active), "hasInactiveTime (DNE)");
    TEST_BOOL(timeManager->hasActiveTime(time2_active), "hasActiveTime");

    std::cout << "Waiting One Second..." << std::endl;
    
    SDL_Delay(1000);
    auto time3 = timeManager->appendTime();

    SDL_Delay(1000);
    auto time4 = timeManager->appendTime();

    //check out the timeTuples in the inactive container
    viewContainers();

    //test deletion within the inactive container
    timeManager->removeTime(time4);
    TEST_BOOL(!timeManager->hasTime(time4), "removeTime");

    //test active timer part of the time manager
    auto activeTimer_oneSecond = timeManager->appendTime(1000);
    auto activeTimer_twoSeconds = timeManager->appendTime(2000);
    //set a delay past 
    SDL_Delay(1010);
    
    TEST_BOOL(timeManager->getNewInactives().size() == 2,
	      "getNewInactives()");

    timeManager->cleanActiveContainer();

    TEST_BOOL(timeManager->getNewInactives().size() == 0,
	      "cleanActiveContainer()");

    //try extending a time into the active container
    auto newActive = timeManager->appendTime();
    timeManager->extendTime(newActive, 1000);

    TEST_BOOL(timeManager->hasActiveTime(newActive), "extendTime");
    
    SDL_Delay(1010);
    timeManager->cleanActiveContainer();
    timeManager->extendTime(newActive, 2000);

    TEST_BOOL(timeManager->hasActiveTime(newActive), "extendTime2");

    viewContainers();

    
    
    return 0;    
}

