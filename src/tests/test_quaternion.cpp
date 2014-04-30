#include <iostream>
#include <cassert>
#include <cmath>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
  TEST_NAME();

  auto q1 = Quaternion(1,2,3,0);


  auto q2 = Quaternion(1,1,1,1);
  
  auto q3 = q1 + q2;  
  TEST_EQUAL(q3, Quaternion(2,3,4,1), "quaternion addition");

  std::cout << "q1: " << q1 << std::endl;
  std::cout << "q2: " << q2 << std::endl;

  std::cout << "q1 * q2 = " << q1 * q2 << std::endl;

  TEST_EQUAL(q1*q2, 6.0, "scalar multiplication");
  
  std::cout << "q1 x q2 = " << q1 % q2 << std::endl;
  TEST_EQUAL(q1%q2, Quaternion(-4,6,2,0), "product multiplication");

  TEST_EQUAL(q1.conj(), Quaternion(1,-2,-3,0), "Conjugate");

  TEST_EQUAL(q2.magnitude_real(), 2, "Real Magnitude");
  TEST_EQUAL(q2.magnitude(), 4, "Magnitude");
  
  auto q4 = Quaternion(5,3,2,2);

  std::cout << "q4-unit: " << q4.unit() << std::endl;
  std::cout << "q4-inverse: " << q4.inv() << std::endl;
  
  auto q5 = Quaternion(4,5,1,2);
  auto q6 = q5 % q1;
  q5 %= q1;
  TEST_EQUAL(q5, q6, "testing product2");

  auto q7 = Quaternion();
  q7[0] = 1;
  q7[1] = 2;
  q7[2] = q7[0] + q7[1];
  q7[3] = q7[0] + q7[2];
  std::cout << "q7: " << q7 << std::endl;
  TEST_EQUAL(q7, Quaternion(1,2,3,4), "testing assignment");


  return 0;
}
