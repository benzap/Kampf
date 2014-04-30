#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
    TEST_NAME();

    COL_circle first = {
	Vector3{10, 0, 0},
	10
    };

    COL_circle second = {
	Vector3{0, 0, 0},
	10
    };

    COL_circle third = {
	Vector3{100, 0, 0},
	10
    };
    
    TEST_BOOL(check_circle_circle(first, second),
	      "circle and circle collision");

    TEST_BOOL(!check_circle_circle(second, third),
	      "circle and circle no collision");
    
    return 0;
}
