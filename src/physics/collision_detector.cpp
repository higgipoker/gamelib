#include "collision_detector.h"
#include "../math/vector3.h"

namespace GameLib {

namespace CollisionDetector {

//  -----------------------------------------------------
//  collision circle and circle
//  -----------------------------------------------------
bool collision (float x1, float y1, float radius1, float x2, float y2, float radius2) {

    if (radius1 < TOL || radius2 < TOL) {
        return false;
    }

    // compare the distance to combined radii
    float dx = x2 - x1;
    float dy = y2 - y1;
    float radii = radius1 + radius2;

    if ( (dx * dx) + (dy * dy) < radii * radii) {
        return true;
    }

    return false;
}

//  -----------------------------------------------------
//  collision circle and circle
//  -----------------------------------------------------
bool collision (const Circle &c1, const Circle &c2) {
    return (collision (c1.x, c1.y, c1.radius, c2.x, c2.y, c2.radius));
}

//  -----------------------------------------------------
//  collision point and circle
//  -----------------------------------------------------
bool collision (const Point &p, const Circle &c) {
    if ( ( (p.x - c.x) * (p.x - c.x) + (p.y - c.y) * (p.y - c.y)) <= (c.radius * c.radius)) {
        return true;
    }

    return false;
}

//  -----------------------------------------------------
//  collision circle and triangle
//  -----------------------------------------------------
bool collision (const Point &point, const Triangle &triangle) {

    /**************************************************************************
     *
     * the Barycentric Technique using dot products to cleverly avoid roots...
     * see: http://www.blackpawn.com/texts/pointinpoly/default.html
     *
     **************************************************************************/

    Vector3 v0 = Vector3 (triangle.p3.x, triangle.p3.y) - Vector3 (triangle.p1.x, triangle.p1.y);
    Vector3 v1 = Vector3 (triangle.p2.x, triangle.p2.y) - Vector3 (triangle.p1.x, triangle.p1.y);
    Vector3 v2 = Vector3 (point.x, point.y) - Vector3 (triangle.p1.x, triangle.p1.y);

    float dot00 = v0 * v0;
    float dot01 = v0 * v1;
    float dot02 = v0 * v2;
    float dot11 = v1 * v1;
    float dot12 = v1 * v2;

    float inv_denom = 1 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * inv_denom;
    float v = (dot00 * dot12 - dot01 * dot02) * inv_denom;

    return (u >= 0) && (v >= 0) && (u + v < 1);
}
} // CollisionDetector
} // GameLib
