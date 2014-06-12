#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
    auto kampf = Kampf(enumInitType::Basic); 
    auto lua = kampf.getLua();
    lua->loadScript("test_collision.lua");

    return 0;
}
