#include <iostream>
#include <cassert>
#include <cmath>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
  TEST_NAME("test_matrix3.cpp");

  auto m1 = Matrix3();
  auto m2 = Matrix3();

  for (int i = 0; i < 9; i++) {
    m1.data[i] = i;
    m2.data[i] = -i;
  }
  auto m3 = m1 + m2;

  TEST_BOOL(m3.data[0] == 0, "Testing addition");

  return 0;
}
