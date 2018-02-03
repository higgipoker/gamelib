#pragma once
#include "../math/shapes.h"
namespace GameLib {

namespace CollisionDetector {
/**
* @brief circle and circle
*/
bool collision (float x1, float y1, float radius1, float x2, float y2, float radius2);

/**
* @brief circle and circle
*/
bool collision (const Circle &c1, const Circle &c2);

/**
* @brief point and circle
*/
bool collision (const Point &p, const Circle &c);

/**
* @brief point and triangle
*/
bool collision (const Point &point, const Triangle &triangle);
};

} // GameLib
