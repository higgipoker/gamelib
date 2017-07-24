#pragma once

#include "window.h"
#include "../math/shapes.h"
#include "color.h"

namespace GameLib{

class Primitives{
public:
	static void Circle(Window &target, unsigned int x, unsigned int y, unsigned int radius);
	static void Rectangle(Window &target, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
	static void Lines(Window &target, const std::vector<Line> &lines, int thickness = 1);
	static void Arc(Window &target, float x, float y, float radius, float start, float end, int segments, int thickness);

	static Color outline_color;
	static Color fill_color;
};

}// GameLib
