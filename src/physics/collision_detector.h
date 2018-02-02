#pragma once
#include "../math/shapes.h"
namespace GameLib {

namespace CollisionDetector {
/**
* @brief circle and circle
*/
bool collision(int x1, int y1, int radius1, int x2, int y2, int radius2);

/**
* @brief circle and circle
*/
bool collision(const Circle &c1, const Circle &c2);

/**
* @brief point and circle
*/
bool collision(const Point &p, const Circle &c);

/**
* @brief point and triangle
*/
bool collision(const Point &point, const Triangle &triangle);
};

} // GameLib
