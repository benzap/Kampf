#include "KF_Vector3.hpp"

//Makes an orthonormal basis between the three provided vectors
void makeOrthonormalBasis(Vector3 *a, Vector3 *b, Vector3 *c) {
  //normalize our first vector
  *a = a->unit();

  //c is normal of a and b
  (*c) = (*a) % (*b);

  //if a cross b is zero, return, can't form a basis
  if (c->magnitude() == 0.0) {
    return;
  }

  //normalize our normal
  *c = c->unit();

  //reapply cross product to get a unit vector for B
  //(less expensive than getting it's unit vector)
  (*b) = (*c) % (*a);
};
