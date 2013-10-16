#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
  TEST_NAME("test_math.cpp");

  auto q = Quaternion(1,2,3,0);
  std::cout << q << std::endl;

  auto q2 = Quaternion(1,1,1,1);
  
  auto q3 = q + q2;
  
  TEST_EQUAL(q3, Quaternion(2,3,4,1), "quaternion addition");


  return 0;
}
