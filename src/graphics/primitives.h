#pragma once

#include "../math/shapes.h"
#include "../math/vector3.h"
#include "color.h"
#include "window.h"

namespace GameLib {

// ************************************************************
// TODO: primitives do not take account of viewport for HUD elements!!!
// ************************************************************

/**
 * @brief The Primitives class
 */
class Primitives {
  public:
    static void Circle(Window &target, unsigned int x, unsigned int y,
                       unsigned int radius);
    static void Triangle(Window &target, unsigned int x1, unsigned int y1,
                         unsigned int x2, unsigned int y2, unsigned int x3,
                         unsigned int y3);
    static void Rectangle(Window &target, unsigned int x, unsigned int y, unsigned int w,
                          unsigned int h);
    static void Lines(Window &target, const std::vector<Line> &lines,
                      unsigned int thickness = 1);
    static void DrawLine(Window &target, const Vector3 &point1, const Vector3 &point2,
                         unsigned int thickness = 1);
    static void Arc(Window &target, float x, float y, float radius, float start,
                    float end, unsigned int segments, unsigned int thickness);

    static void OutlineColor(const Color &c);
    static void FillColor(const Color &c);
    static void RestoreColors();

  private:
    static Color outline_color;
    static Color fill_color;
    static Color last_outline_color;
    static Color last_fill_color;
};

} // GameLib
