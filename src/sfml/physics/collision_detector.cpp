#include "collision_detector.h"

namespace GameLib {

//  -----------------------------------------------------
//  collision circle and circle
//  -----------------------------------------------------
const bool CollisionDetector::collision( int x1, int y1, int radius1, int x2, int y2, int radius2 ) {

    if (radius1 == 0 || radius2 == 0) {
        return false;
    }

    // compare the distance to combined radii
    int dx = x2 - x1;
    int dy = y2 - y1;
    int radii = radius1 + radius2;
    if ((dx * dx) + (dy * dy) < radii * radii) {
        return true;
    }
    return false;
}

//  -----------------------------------------------------
//  collision circle and circle
//  -----------------------------------------------------
const bool CollisionDetector::collision( const Circle &c1, const Circle &c2){
	return (collision(c1.x, c1.y, c1.radius, c2.x, c2.y, c2.radius));
}

}// GameLib
