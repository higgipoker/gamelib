#include "shapes.h"
#include "vector3.h"
#include <random>

namespace GameLib {

// ----------------------------------------------------------------------------------------------------
// Point
// ----------------------------------------------------------------------------------------------------
Point::Point() {
    x = 0;
    y = 0;
}
Point::Point(float _x, float _y) {
    x = _x;
    y = _y;
}
Point::Point(const Vector3 &v) {
    x = v.x;
    y = v.y;
}
void Point::init(int _x, int _y) {
    x = _x;
    y = _y;
}
void Point::Reset(void) { x = y = 0; }
bool Point::inRect(const Rectangle &_rect) const {
    if (x > _rect.x && x < _rect.x + _rect.w && y > _rect.y && y < _rect.y + _rect.h) {
        return true;
    } else {
        return false;
    }
}
Vector3 Point::vector() { return Vector3(x, y); }

bool Point::operator==(const Point &_p) {
    if (floorf(this->x) == floorf(_p.x) && floorf(this->y) == floorf(_p.y)) {
        return true;
    }

    return false;
}
bool Point::operator!=(const Point &_p) const { return !(this == &_p); }

// ----------------------------------------------------------------------------------------------------
// Line
// ----------------------------------------------------------------------------------------------------
Line::Line(void) { x1 = y1 = x2 = y2 = 0; }
Line::Line(float _x1, float _y1, float _x2, float _y2) {
    x1 = _x1;
    y1 = _y1;
    x2 = _x2;
    y2 = _y2;
}
void Line::init(float _x1, float _y1, float _x2, float _y2) {
    x1 = _x1;
    y1 = _y1;
    x2 = _x2;
    y2 = _y2;
}

// ----------------------------------------------------------------------------------------------------
// Triangle
// ----------------------------------------------------------------------------------------------------
Triangle::Triangle(Point &_p1, Point &_p2, Point &_p3) : p1(_p1), p2(_p2), p3(_p3) {}

Triangle::Triangle() {}

// ----------------------------------------------------------------------------------------------------
// Circle
// ----------------------------------------------------------------------------------------------------
Circle::Circle(float _x, float _y, float _radius) {
    x = _x;
    y = _y;
    radius = _radius;
}
Circle::Circle() { x = y = radius = 0; }

bool Circle::in_rect(const Rectangle &r) {

    if (x - radius > r.x && x + radius < r.x + r.w && y - radius > r.y && y + radius < r.y + r.h) {
        return true;
    }

    return false;
}

// ----------------------------------------------------------------------------------------------------
// Rectangle
// ----------------------------------------------------------------------------------------------------
Rectangle::Rectangle() { x = y = w = h = 0; }
Rectangle::Rectangle(const Rectangle &r) {
    x = r.x;
    y = r.y;
    w = r.w;
    h = r.h;
}
Rectangle::Rectangle(float _x, float _y, float _w, float _h) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}
void Rectangle::init(float _x, float _y, float _w, float _h) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}
void Rectangle::SetSize(float _w, float _h) {
    w = _w;
    h = _h;
}
void Rectangle::SetPosition(float _x, float _y) {
    x = _x;
    y = _y;
}
void Rectangle::SetCenter(float _x, float _y) {
    x = (_x - w / 2);
    y = (_y - h / 2);
}
Point Rectangle::GetCenter() const { return Point(x + w / 2, y + h / 2); }
float Rectangle::area() const { return w * h; }
void Rectangle::contract(float amount) {
    x += amount;
    y += amount;
    w -= amount * 2;
    h -= amount * 2;
}
Point Rectangle::getRandomPoint(void) const {
    Point p;
    p.x = x + rand() % int(w);
    p.y = y + rand() % int(h);

    return p;
}

Size2D::Size2D() {
    w = 0;
    h = 0;
}

Size2D::Size2D(float _w, float _h) {
    w = _w;
    h = _h;
}
bool Rectangle::overlaps(const Rectangle &_rect) const {
    if (this->x < _rect.x + _rect.w && this->x + this->w > _rect.x && this->y < _rect.y + _rect.h && this->y + this->h > _rect.y) {
        return true;
    }

    return false;
}

bool Rectangle::contains(const Point &p) const {
    if (p.x < x || p.x > x + w || p.y > y + h || p.y < y) {
        return false;
    }
    return true;
}

// ----------------------------------------------------------------------------------------------------
// Post
// ----------------------------------------------------------------------------------------------------
Post::Post(float _x, float _y, float _height, float _radius) {
    x = _x;
    y = _y;
    height = _height;
    radius = _radius;
}

// ----------------------------------------------------------------------------------------------------
// Bar
// ----------------------------------------------------------------------------------------------------
Bar::Bar(float _x, float _y, float _w, float _h) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

// ----------------------------------------------------------------------------------------------------
// Ball
// ----------------------------------------------------------------------------------------------------
Ball::Ball(float _x, float _y, float _z, float _radius) {
    x = _x;
    y = _y;
    z = _z;
    radius = _radius;
}

// ----------------------------------------------------------------------------------------------------
// UprightVerticalPlane
// ----------------------------------------------------------------------------------------------------
UprightVerticalPlane::UprightVerticalPlane(float _x, float _y, float _depth, float _height) {
    x = _x;
    y = _y;
    depth = _depth;
    height = _height;
}

// ----------------------------------------------------------------------------------------------------
// UprightHorizontalPlane
// ----------------------------------------------------------------------------------------------------
UprightHorizontalPlane::UprightHorizontalPlane(float _x, float _y, float _width, float _height) {
    x = _x;
    y = _y;
    width = _width;
    height = _height;
}

// ----------------------------------------------------------------------------------------------------
// FlatPlane
// ----------------------------------------------------------------------------------------------------
FlatPlane::FlatPlane(float _x, float _y, float _w, float _h, float _z) {
    x = _x;
    y = _y;
    width = _w;
    height = _h;
    z = _z;
}

} // namespace GameLib
