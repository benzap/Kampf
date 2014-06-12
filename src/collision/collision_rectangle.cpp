#include "collision_rectangle.hpp"

boolType check_rect_rect(const COL_rect& first, const COL_rect& second) {
    if (first.max.x < second.max.x || first.min.x > second.min.x) return false;
    if (first.max.y < second.max.y || first.min.y > second.min.y) return false;
    if (first.max.z < second.max.z || first.min.z > second.min.z) return false;

    return true;
}

Vector3 get_rect_rect_pt(const COL_rect& first, const COL_rect& second) {
    return Vector3();
}
 
