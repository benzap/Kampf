#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
  TEST_NAME("test_renderwindow.cpp");
  auto kampf = Kampf(enumInitType::Basic); 
  auto lua = kampf.getLua();
  lua->loadScript(KF_INIT_FILE);
      
  kampf.runMainLoop(5000);
  return 0;
}
