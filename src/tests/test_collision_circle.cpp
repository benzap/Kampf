#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
    TEST_NAME("test_collision_circle.cpp");

    COL_circle first = {
	Vector3{10, 0, 0},
	10
    };

    COL_circle second = {
	Vector3{0, 0, 0},
	10
    };

    TEST_BOOL(check_circle_circle(first, second),
	      "circle and circle collision");
    
    return 0;
}
