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
 
Vector3 get_rect_rect_contactNormal(const COL_rect& first,
				    const COL_rect& second) {
    
    
}

floatType get_rect_rect_separation(const COL_rect& first,
				   const COL_rect& second) {
    auto contactNormal = get_rect_rect_contactNormal(first, second);
    
}

const COL_rect get_penetration_rectangle(const COL_rect& first,
					 const COL_rect& second) {
    COL_rect penRect;
    
    if (first.max.x > second.min.x) {
	if (first.max.y > second.min.y) {
	    penRect.min = first.max;
	    penRect.max = second.min;
	}
	if ((first.min.y + first.max.y) > (second.min.y + second.max.y)) {
	    penRect.min = 0;
	}
    }
    return penRect;
}
