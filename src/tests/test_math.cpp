#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
  TEST_NAME("test_math.cpp");

  auto v = Vector(0,0,0);

  v[0] = 1;

  TEST_EQUAL(v[0], 1, "test assignment - x");
  TEST_EQUAL(v[0], v.x, "test equal assignment");

  v[1] = 3;

  TEST_EQUAL(v[1], 3, "test assignment - y");
  TEST_EQUAL(v[1], v.y, "test equal assignment");

  v[2] = 5;

  TEST_EQUAL(v[2], 5, "test assignment - z");
  TEST_EQUAL(v[2], v.z, "test equal assignment");

  
  auto v2 = Vector(1,2,3);
  auto v3 = Vector(1,1,1);

  //adding vectors
  auto added = v2 + v3;
  TEST_EQUAL(added[0], 2, "added-x");
  TEST_EQUAL(added[1], 3, "added-y");
  TEST_EQUAL(added[2], 4, "added-z");

  //scalar with a vector
  auto scalarVec = v3 * 2;
  TEST_EQUAL(scalarVec[0], 2, "scalar-x");
  TEST_EQUAL(scalarVec[1], 2, "scalar-y");
  TEST_EQUAL(scalarVec[2], 2, "scalar-z");

  //adding scalars
  auto addedScalar = v2 + 1;
  TEST_EQUAL(addedScalar[0], 2, "addedScalar-x");
  TEST_EQUAL(addedScalar[1], 3, "addedScalar-y");
  TEST_EQUAL(addedScalar[2], 4, "addedScalar-z");

  //dot product
  auto dotScalar = v2 * v3;
  TEST_EQUAL(dotScalar, 6, "dot scalar");

  //component product
  auto compV = v2.comp_prod(v3*2);
  TEST_EQUAL(compV[0], 2, "compV-x");
  TEST_EQUAL(compV[1], 4, "compV-y");
  TEST_EQUAL(compV[2], 6, "compV-z");

  //component product update
  compV.comp_prod_update(-v3);
  TEST_EQUAL(compV[0], -2, "compV-x update");
  TEST_EQUAL(compV[1], -4, "compV-y update");
  TEST_EQUAL(compV[2], -6, "compV-z update");

  //cross product
  TEST_EQUAL(Vector(1,2,3), -Vector(-1,-2,-3), "testing boolean equality");
  
  //magnitude
  //apparently this works
  TEST_EQUAL(Vector(1,1,1).magnitude_real(), sqrt(3), "testing magnitude");

  //testing unit vector
  auto v4 = Vector(1,2,1);
  std::cout << "orig: " << v4 << std::endl;
  std::cout << "unit: " << v4.unit() << std::endl;

  //testing cross product
  auto crossV = V_i % V_j;
  TEST_EQUAL(crossV, V_k, "cross product");

  auto crossV2 = V_k;
  crossV2 %= V_i;

  TEST_EQUAL(crossV2, V_j, "cross product2");

  auto VI = V_i;
  auto VJ = V_j;
  auto VK = Vector(0,0,0);

  makeOrthonormalBasis(&VI, &VJ, &VK);

  TEST_EQUAL(VK, V_k, "testing orthonormal");


  return 0;
}
