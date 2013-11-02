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

  m1 = {
    1,2,3,
    4,5,6,
    7,8,9
  };
  
  m2 = {
    1,3,5,
    3,4,5,
    6,7,8
  };


  auto vectorRow = m1.row(0);
  TEST_EQUAL(vectorRow, Vector3(1,2,3), "row1");

  auto vectorCol = m1.col(0);
  TEST_EQUAL(vectorCol, Vector3(1,4,7), "col1");

  Matrix3 result = {
    25, 32, 39,
    55, 74, 93,
    85, 116, 147
  };

  m3 = m1 % m2;

  std::cout << "m3: " << m3 << std::endl;

  TEST_EQUAL(m3, result, "Matrix Multiplication");

  m1 %= m2;
  TEST_EQUAL(m1, result, "Matrix Multiplication 2");
  return 0;
}
