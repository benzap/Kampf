#include "KF_math.hpp"

//Makes an orthonormal basis between the three provided vectors
void makeOrthonormalBasis(Vector *a, Vector *b, Vector *c) {
*a = a->unit();
(*c) = (*a) % (*b);
if (c->magnitude() == 0.0) return;
*c = c->unit();
(*b) = (*c) % (*a);
};
