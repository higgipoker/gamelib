#include "primitives.h"

#include <math.h>
#include <SFML/Graphics.hpp>
#include "../math/constants.h"

namespace GameLib {

Color Primitives::outline_color(0,0,0,0);
Color Primitives::fill_color(0,0,0,0);
Color Primitives::last_outline_color(0,0,0,0);
Color Primitives::last_fill_color(0,0,0,0);


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
void Primitives::Triangle(Window &target, unsigned int x1, unsigned int y1,
        unsigned int x2, unsigned int y2,
        unsigned int x3, unsigned int y3
                         ) {

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
void Primitives::Lines(Window &target, const std::vector<Line> &lines, int thickness) {

    // construct the vertex list
    std::vector<sf::Vertex> vertices;

    for(unsigned int i = 0; i < thickness; ++i) {

        // add the vertices
        for(auto it = lines.begin(); it != lines.end(); ++it) {
            vertices.push_back(sf::Vertex(sf::Vector2f((*it).x1 + i * 0.2f, (*it).y1 + i * 0.2f), sf::Color(outline_color.r, outline_color.g, outline_color.b, outline_color.a)));
            vertices.push_back(sf::Vertex(sf::Vector2f((*it).x2 + i * 0.2f, (*it).y2 + i * 0.2f), sf::Color(outline_color.r, outline_color.g, outline_color.b, outline_color.a)));
        }

    }

    // draw vertex list
    target.window.draw(&vertices[0], vertices.size(), sf::Lines);
}

void Primitives::DrawLine(Window &target, const Vector3 &point1, const Vector3 &point2, int thickness) {
    sf::Vertex vertices[4];
    Vector3 direction = point2 - point1;
    Vector3 unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
    Vector3 unitPerpendicular(-unitDirection.y, unitDirection.x);

    Vector3 offset = unitPerpendicular * (thickness / 2.f);

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


    for(int i = 0; i < 4; ++i)
        vertices[i].color = sf::Color(outline_color.r, outline_color.g, outline_color.b, outline_color.a);

    target.window.draw(vertices, 4, sf::Quads);
}

// ------------------------------------------------------------
// Arc
// ------------------------------------------------------------
void Primitives::Arc(Window &target, float x, float y, float radius, float start, float end, int segments, int thickness) {

    // construct the vertex list
    std::vector<sf::Vertex> vertices;

    // trackers
    float act_start = start;
    float act_end = end;

    float lastx = 0;
    float lasty = 0;

    for(unsigned int i = 0; i < thickness; ++i) {
        float current = act_start;
        int segments_drawn = 0;

        while(current <= act_end) {
            float ax = x + radius * cos(RADIANS(current));
            float ay = y + radius * sin(RADIANS(current));
            current += ((act_end - act_start) / segments);

            vertices.push_back(sf::Vertex(sf::Vector2f(ax, ay), sf::Color(outline_color.r, outline_color.g, outline_color.b, outline_color.a)));

            if(segments_drawn) {
                DrawLine(target, Vector3(lastx, lasty), Vector3(ax, ay), thickness);
                //target.Present();
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
    //target.window.draw(&vertices[0], vertices.size(), sf::LinesStrip);
}

void Primitives::OutlineColor(const Color &c){
    last_outline_color = outline_color;
    outline_color = c;
}

void Primitives::FillColor(const Color &c){
    last_fill_color = fill_color;
    fill_color = c;
}

void Primitives::RestoreColors(){
    outline_color = last_outline_color;
    fill_color = last_fill_color;
}

}// GameLib
