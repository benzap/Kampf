#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
    auto kampf = Kampf(enumInitType::Basic); 
    auto lua = kampf.getLua();
    lua->loadScript("kampf_render.lua");

    return 0;
}
