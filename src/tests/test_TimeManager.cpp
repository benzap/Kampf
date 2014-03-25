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
    for (auto timeTuple : timeManager->getInactiveContainer()) {
	std::cout << "TimeTuple<" << timeTuple.first << ", " << timeTuple.second << ">" << std::endl;
    }

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

    return 0;    
}

