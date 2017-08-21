#pragma once

#include "window.h"
#include "../math/vector3.h"
#include "../math/shapes.h"
#include "color.h"

namespace GameLib{

class Primitives{
public:
	static void Circle(Window &target, unsigned int x, unsigned int y, unsigned int radius);
    static void Triangle(Window &target,    unsigned int x1, unsigned int y1,
                                            unsigned int x2, unsigned int y2,
                                            unsigned int x3, unsigned int y3);
	static void Rectangle(Window &target, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
	static void Lines(Window &target, const std::vector<Line> &lines, int thickness = 1);
	static void DrawLine(Window &target, const Vector3 &point1, const Vector3 &point2, int thickness = 1);
	static void Arc(Window &target, float x, float y, float radius, float start, float end, int segments, int thickness);

    static void OutlineColor(const Color &c);
    static void FillColor(const Color &c);
    static void RestoreColors();

private:

	static Color outline_color;
	static Color fill_color;
    static Color last_outline_color;
	static Color last_fill_color;
};

}// GameLib
