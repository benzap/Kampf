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
    
    auto time2 = timeManager->appendTime(1000);
    TEST_BOOL(timeManager->hasTime(time2), "hasTime (Active)");
    TEST_BOOL(!timeManager->hasInactiveTime(time2), "hasInactiveTime (DNE)");
    TEST_BOOL(timeManager->hasActiveTime(time2), "hasActiveTime");

    return 0;    
}

