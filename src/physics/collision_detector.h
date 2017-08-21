#pragma once
#include "../math/shapes.h"
namespace GameLib {

class CollisionDetector {
public:

    /**
    * @brief circle and circle
    */
    static const bool collision(int x1, int y1, int radius1, int x2, int y2, int radius2);

    /**
    * @brief circle and circle
    */
    static const bool collision(const Circle &c1, const Circle &c2);

    /**
    * @brief point and circle
    */
    static bool collision(const Point &p, const Circle &c);

    /**
    * @brief point and triangle
    */
    static bool collision(const Point &point, const Triangle &triangle);
};

}// GameLib
