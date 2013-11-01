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

  TEST_BOOL(m3 == Matrix3(), "Testing addition");

  Matrix3 m4 = {
    1,2,3,
    4,5,6,
    7,8,9
  };
  std::cout << "m4:" << m4 << std::endl;

  Matrix3 m5 = {
    1,0,0,
    0,1,0,
    0,0,1,
  };
  Matrix3 m6 = {};
  m6.identity(1);

  std::cout << "m6:" << m6 << std::endl;

  TEST_EQUAL(m5,m6, "Identity");
  
  m5 = {
    4,5,1,
    2,3,4,
    1,2,1,
  };

  TEST_EQUAL(m5.det(), -9, "determinate");
  std::cout << "m4 det" << m5.det() << std::endl;

  


  return 0;
}
