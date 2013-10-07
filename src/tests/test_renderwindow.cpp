#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
  TEST_NAME("test_renderwindow.cpp");
  auto kampf = Kampf(enumInitType::Basic); 

  kampf.runMainLoop(5000);
  return 0;
}
