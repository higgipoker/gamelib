#pragma once

namespace GameLib {

class Vector3;
struct Point;

struct Rectangle {
    Rectangle();
    Rectangle(const Rectangle &r);
    Rectangle(float _x, float _y, float _w, float _h);
    void init(float _x, float _y, float _w, float _h);
    float area() const;
    void contract(float amount);
    Point GetCenter(void) const;
    Point getRandomPoint(void) const;
    bool overlaps(const Rectangle &_rect) const;
    bool contains(const Point &_p) const;
    float x, y, w, h;
};

struct Point {
    Point();
    Point(float _x, float _y);
    void init(int _x, int _y);
    void Reset(void);
    bool inRect(const Rectangle &_rect) const;
    Vector3 vector();
    bool operator==(const Point &_p);
    bool operator!=(const Point &_p) const;

    float x;
    float y;
};

struct Line {
    Line(void);
    Line(float _x1, float _y1, float _x2, float _y2);
    void init(float _x1, float _y1, float _x2, float _y2);
    float x1, y1, x2, y2;
};

struct Triangle {
    Triangle(Point &_p1, Point &_p2, Point &_p3);
    Triangle();

    Point p1;
    Point p2;
    Point p3;
};

struct Circle {
    Circle(float _x, float _y, float _radius);
    Circle();

    bool in_rect(const Rectangle &r);
    float x, y, radius;
};

struct Post {
    Post(float _x, float _y, float _height, float _radius);
    float x, y, height, radius;
};

struct Bar {
    Bar(float _x, float _y, float _w, float _h);
    float x, y, w, h;
};

struct Ball {
    Ball(float _x, float _y, float _z, float _radius);
    float x, y, z, radius;
};

// like side netting
struct UprightVerticalPlane {
    UprightVerticalPlane(float _x, float _y, float _depth, float _height);
    float x, y, depth, height;
};

// like back netting
struct UprightHorizontalPlane {
    UprightHorizontalPlane(float _x, float _y, float _width, float _height);
    float x, y, width, height;
};

// like top of net
struct FlatPlane {
    FlatPlane(float _x, float _y, float _w, float _h, float _z);
    float x, y, width, height, z;
};
} // namespace GameLib
