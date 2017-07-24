#include "primitives.h"

#include <math.h>
#include <SFML/Graphics.hpp>
#include "../math/constants.h"

namespace GameLib {

Color Primitives::outline_color;
Color Primitives::fill_color;

// ------------------------------------------------------------
// Circle
// ------------------------------------------------------------
void Primitives::Circle (Window &target, unsigned int x, unsigned int y, unsigned int radius) {
	sf::CircleShape circle (radius);
	circle.setFillColor (sf::Color (fill_color.r, fill_color.g, fill_color.b, fill_color.a));
	circle.setOutlineThickness (1);
	circle.setOutlineColor (sf::Color (outline_color.r, outline_color.g, outline_color.b, outline_color.a));
	circle.setPosition (x - radius, y - radius);
	target.Draw (circle);
}

// ------------------------------------------------------------
// Rectangle
// ------------------------------------------------------------
void Primitives::Rectangle (Window &target, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	sf::RectangleShape rectangle (sf::Vector2f (w, h));
	rectangle.setFillColor (sf::Color (fill_color.r, fill_color.g, fill_color.b, fill_color.a));
	rectangle.setOutlineThickness (1);
	rectangle.setOutlineColor (sf::Color (outline_color.r, outline_color.g, outline_color.b, outline_color.a));
	rectangle.setPosition (sf::Vector2f (x, y));
	target.Draw (rectangle);
}

// ------------------------------------------------------------
// Lines
// ------------------------------------------------------------
void Primitives::Lines (Window &target, const std::vector<Line> &lines, int thickness) {

	// construct the vertex list
	std::vector<sf::Vertex> vertices;

	for (unsigned int i = 0; i < thickness; ++i) {

		// add the vertices
		for (auto it = lines.begin(); it != lines.end(); ++it) {
			vertices.push_back (sf::Vertex (sf::Vector2f ( (*it).x1 + i * 0.2f, (*it).y1 + i * 0.2f), sf::Color (outline_color.r, outline_color.g, outline_color.b, outline_color.a)));
			vertices.push_back (sf::Vertex (sf::Vector2f ( (*it).x2 + i * 0.2f, (*it).y2 + i * 0.2f), sf::Color (outline_color.r, outline_color.g, outline_color.b, outline_color.a)));
		}

	}
	// draw vertex list
	target.window.draw (&vertices[0], vertices.size(), sf::Lines);
}

// ------------------------------------------------------------
// Arc
// ------------------------------------------------------------
void Primitives::Arc (Window &target, float x, float y, float radius, float start, float end, int segments, int thickness) {

	// construct the vertex list
	std::vector<sf::Vertex> vertices;

	// trackers
	float act_start = start;
	float act_end = end;

	for (unsigned int i = 0; i < thickness; ++i) {
		float current = act_start;
		while (current <= act_end) {
			float ax = x + radius * cos (RADIANS (current));
			float ay = y + radius * sin (RADIANS (current));
			current += ( (act_end - act_start) / segments);

			vertices.push_back (sf::Vertex (sf::Vector2f (ax, ay), sf::Color (outline_color.r, outline_color.g, outline_color.b, outline_color.a)));
		}
		radius += 0.2f;
		act_start = start;
		act_end = end;
	}

	// draw vertex list
	target.window.draw (&vertices[0], vertices.size(), sf::LinesStrip);
}

}// GameLib
