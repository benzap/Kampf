#include "collision_rectangle.hpp"

boolType check_rect_rect(const COL_rect& first, const COL_rect& second) {
    if (first.max.x < second.min.x || first.min.x > second.max.x) return false;
    if (first.max.y < second.min.y || first.min.y > second.max.y) return false;
    if (first.max.z < second.min.z || first.min.z > second.max.z) return false;

    return true;
}

Vector3 get_rect_rect_pt(const COL_rect& first, const COL_rect& second) {
    return Vector3();
}
 
