#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
    TEST_NAME("test_guid.cpp");

    std::cout << generateGUID() << std::endl;
    std::cout << generateGUID() << std::endl;
    std::cout << generateGUID() << std::endl;
    std::cout << generateGUID() << std::endl;
    
    return 0;
}
