#include "collision_circle.hpp"

boolType check_circle_circle(const COL_circle& first,
			     const COL_circle& second) {
    Vector3 d = first.center;
    d -= second.center;
    floatType dist2 = d * d;
    floatType radiusSum = first.radius + second.radius;
    boolType chk = (dist2 <= radiusSum * radiusSum);
    return chk;
}

Vector3 get_circle_circle_contactNormal(const COL_circle& first,
					const COL_circle& second) {
    Vector3 s = second.center;
    s -= first.center;
    return s.unit();
}

floatType get_circle_circle_separation(const COL_circle& first,
				       const COL_circle& second) {
    Vector3 s = second.center;
    s -= first.center;
    return s.magnitude_real() - (first.radius + second.radius);
}
