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
    
    auto time2_active = timeManager->appendTime(2000);
    TEST_BOOL(timeManager->hasTime(time2_active), "hasTime (Active)");
    TEST_BOOL(!timeManager->hasInactiveTime(time2_active), "hasInactiveTime (DNE)");
    TEST_BOOL(timeManager->hasActiveTime(time2_active), "hasActiveTime");

    std::cout << "Waiting One Second..." << std::endl;
    sleep(1000);
    auto time3 = timeManager->appendTime();

    sleep(1000);
    auto time4 = timeManager->appendTime();

    //check out the timeTuples in the inactive container
    for (auto timeTuple : timeManager->getInactiveContainer()) {
	std::cout << "TimeTuple<" << timeTuple.first << ", " << timeTuple.second << ">" << std::endl;
    }
    

    return 0;    
}

