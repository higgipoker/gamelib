#pragma once
#include <math.h>
namespace GameLib {

class Vector3;
struct Point;

struct Rectangle {
    Rectangle();
    Rectangle(const Rectangle &r);
    Rectangle(double _x, double _y, double _w, double _h);
    void init(double _x, double _y, double _w, double _h);
    double area() const;
    void contract(double amount);
    Point GetCenter(void) const;
    Point getRandomPoint(void) const;
    bool overlaps(const Rectangle &_rect) const;
    bool contains(const Point &_p) const;
    double x, y, w, h;
};

struct Point {
    Point();
    Point(double _x, double _y);
    explicit Point(const Vector3 &v);
    void init(int _x, int _y);
    void Reset(void);
    bool inRect(const Rectangle &_rect) const;
    Vector3 vector();
    bool operator==(const Point &_p);
    bool operator!=(const Point &_p) const;

    double x;
    double y;
};

struct Line {
    Line(void);
    Line(double _x1, double _y1, double _x2, double _y2);
    void init(double _x1, double _y1, double _x2, double _y2);
    double length(){
        return sqrt( (x2 - x1)*(x2 - x1) +  (y2 - y1)*(y2 - y1 ) );
    }
    double x1, y1, x2, y2;
};

struct Triangle {
    Triangle(Point &_p1, Point &_p2, Point &_p3);
    Triangle();
    double area() {
        double side1 = sqrt( (p2.x - p1.x)*(p2.x - p1.x) +  (p2.y - p1.y)*(p2.y - p1.y ) );
        double side2 = sqrt( (p3.x - p2.x)*(p3.x - p2.x) +  (p3.y - p2.y)*(p3.y - p2.y ) );
        double side3 = sqrt( (p1.x - p3.x)*(p1.x - p3.x) +  (p1.y - p3.y)*(p1.y - p3.y ) );
        double s = (side1 + side2 + side3) / 2;
        double area = sqrt(s * (s - side1) * (s - side2) * (s - side3));
        return area;
    }

    Point p1;
    Point p2;
    Point p3;
};

struct Circle {
    Circle(double _x, double _y, double _radius);
    Circle();

    bool in_rect(const Rectangle &r);
    double x, y, radius;
};

struct Post {
    Post(double _x, double _y, double _height, double _radius);
    double x, y, height, radius;
};

struct Bar {
    Bar(double _x, double _y, double _w, double _h);
    double x, y, w, h;
};

struct Ball {
    Ball(double _x, double _y, double _z, double _radius);
    double x, y, z, radius;
};

// like side netting
struct UprightVerticalPlane {
    UprightVerticalPlane(double _x, double _y, double _depth, double _height);
    double x, y, depth, height;
};

// like back netting
struct UprightHorizontalPlane {
    UprightHorizontalPlane(double _x, double _y, double _width, double _height);
    double x, y, width, height;
};

// like top of net
struct FlatPlane {
    FlatPlane(double _x, double _y, double _w, double _h, double _z);
    double x, y, width, height, z;
};
} // namespace GameLib
