#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
    TEST_NAME();

    COL_rect first = {
	Vector3{0, 0, 0},
	Vector3{50, 50, 0}
    };

    COL_rect second = {
	Vector3{49, 49, 0},
	Vector3{79, 79, 0}
    };

    COL_rect third = {
	Vector3{80, 80, 0},
	Vector3{100,100, 0}
    };
    
    TEST_BOOL(check_rect_rect(first, second),
	      "rect and rect collision");

    TEST_BOOL(!check_rect_rect(second, third),
	      "rect and rect no collision");
    
    return 0;
}
