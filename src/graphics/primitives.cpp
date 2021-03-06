/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
/**
 * @file primitives.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "primitives.h"

#include "../math/constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

namespace GameLib {

// ************************************************************
// TODO: primitives do not take account of viewport for HUD elements!!!
// ************************************************************

Color Primitives::outline_color(0, 0, 0, 0);
Color Primitives::fill_color(0, 0, 0, 0);
Color Primitives::last_outline_color(0, 0, 0, 0);
Color Primitives::last_fill_color(0, 0, 0, 0);

// ------------------------------------------------------------
// Circle
// ------------------------------------------------------------
void Primitives::Circle(Window &target, unsigned int x, unsigned int y, unsigned int radius) {
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, fill_color.a));
    circle.setOutlineThickness(1);
    circle.setOutlineColor(sf::Color(outline_color.r, outline_color.g, outline_color.b, outline_color.a));
    circle.setPosition(x - radius, y - radius);
    target.Draw(circle);
}

// ------------------------------------------------------------
// Triangle
// ------------------------------------------------------------
void Primitives::Triangle(Window &target, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3) {

    // create an array of 3 vertices that define a triangle primitive
    sf::VertexArray triangle(sf::Triangles, 3);

    // define the position of the triangle's points
    triangle[0].position = sf::Vector2f(x1, y1);
    triangle[1].position = sf::Vector2f(x2, y2);
    triangle[2].position = sf::Vector2f(x3, y3);

    // define the color of the triangle's points
    triangle[0].color = sf::Color(fill_color.r, fill_color.g, fill_color.b, fill_color.a);
    triangle[1].color = triangle[0].color;
    triangle[2].color = triangle[0].color;

    target.Draw(triangle);
}

// ------------------------------------------------------------
// Rectangle
// ------------------------------------------------------------
void Primitives::Rectangle(Window &target, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(w, h));
    rectangle.setPosition(sf::Vector2f(x, y));
    rectangle.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, fill_color.a));
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(sf::Color(outline_color.r, outline_color.g, outline_color.b, outline_color.a));
    target.Draw(rectangle);
}

// ------------------------------------------------------------
// Lines
// ------------------------------------------------------------
void Primitives::Lines(Window &target, const std::vector<Line> &lines, unsigned int thickness) {

    // construct the vertex list
    std::vector<sf::Vertex> vertices;

    for (unsigned int i = 0; i < thickness; ++i) {

        // add the vertices
        for (auto line : lines) {
            vertices.push_back(sf::Vertex(sf::Vector2f(line.x1 + i * 0.2f, line.y1 + i * 0.2f),
                                          sf::Color(outline_color.r, outline_color.g, outline_color.b, outline_color.a)));
            vertices.push_back(sf::Vertex(sf::Vector2f(line.x2 + i * 0.2f, line.y2 + i * 0.2f),
                                          sf::Color(outline_color.r, outline_color.g, outline_color.b, outline_color.a)));
        }
    }

    // draw vertex list
    target.window.draw(&vertices[0], vertices.size(), sf::Lines);
}

// ------------------------------------------------------------
// Drawline
// ------------------------------------------------------------
void Primitives::DrawLine(Window &target, const Vector3 &point1, const Vector3 &point2, unsigned int thickness) {
    sf::Vertex vertices[4];
    Vector3 direction = point2 - point1;
    Vector3 unit_direction = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
    Vector3 unit_perpendicular(-unit_direction.y, unit_direction.x);

    Vector3 offset = unit_perpendicular * (thickness / 2.f);

    Vector3 tmp1 = point1 + offset;
    Vector3 tmp2 = point2 + offset;
    Vector3 tmp3 = point2 - offset;
    Vector3 tmp4 = point1 - offset;

    vertices[0].position.x = tmp1.x;
    vertices[0].position.y = tmp1.y;

    vertices[1].position.x = tmp2.x;
    vertices[1].position.y = tmp2.y;

    vertices[2].position.x = tmp3.x;
    vertices[2].position.y = tmp3.y;

    vertices[3].position.x = tmp4.x;
    vertices[3].position.y = tmp4.y;

    for (int i = 0; i < 4; ++i) {
        vertices[i].color = sf::Color(outline_color.r, outline_color.g, outline_color.b, outline_color.a);
    }

    target.window.draw(vertices, 4, sf::Quads);
}

// ------------------------------------------------------------
// Arc
// ------------------------------------------------------------
void Primitives::Arc(Window &target, float x, float y, float radius, float start, float end, unsigned int segments, unsigned int thickness) {

    // construct the vertex list
    std::vector<sf::Vertex> vertices;

    // trackers
    float act_start = start;
    float act_end = end;

    float lastx = 0;
    float lasty = 0;

    for (unsigned int i = 0; i < thickness; ++i) {
        float current = act_start;
        int segments_drawn = 0;

        while (current <= act_end) {
            float ax = x + radius * cosf(RADIANS(current));
            float ay = y + radius * sinf(RADIANS(current));
            current += ((act_end - act_start) / segments);

            vertices.push_back(sf::Vertex(sf::Vector2f(ax, ay), sf::Color(outline_color.r, outline_color.g, outline_color.b, outline_color.a)));

            if (segments_drawn) {
                DrawLine(target, Vector3(lastx, lasty), Vector3(ax, ay), thickness);
                // target.Present();
            }

            lastx = ax;
            lasty = ay;

            ++segments_drawn;
        }

        radius += 0.2f;
        act_start = start;
        act_end = end;
    }

    // draw vertex list
    target.window.draw(&vertices[0], vertices.size(), sf::LinesStrip);
}
// ------------------------------------------------------------
// OutlineColor
// ------------------------------------------------------------
void Primitives::OutlineColor(const Color &c) {
    last_outline_color = outline_color;
    outline_color = c;
}
// ------------------------------------------------------------
// FillColor
// ------------------------------------------------------------
void Primitives::FillColor(const Color &c) {
    last_fill_color = fill_color;
    fill_color = c;
}
// ------------------------------------------------------------
// Restorecolors
// ------------------------------------------------------------
void Primitives::RestoreColors() {
    outline_color = last_outline_color;
    fill_color = last_fill_color;
}

} // GameLib
