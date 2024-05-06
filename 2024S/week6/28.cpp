#include <iostream>
#include <cmath>

class Point {
private:
    float x;
    float y;

public:
    Point() : x(0), y(0) {}
    Point(float _x, float _y) : x(_x), y(_y) {}

    void printPoint() const {
        std::cout << "(" << x << ", " << y << ")";
    }

    float getX() const { return x; }
    void setX(float _x) { x = _x; }

    float getY() const { return y; }
    void setY(float _y) { y = _y; }

    float getDistance(const Point& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

class Segment {
private:
    Point point1;
    Point point2;

public:
    Segment() : point1(Point()), point2(Point()) {}
    Segment(const Point& p1, const Point& p2) : point1(p1), point2(p2) {}

    float getLength() const {
        return point1.getDistance(point2);
    }
};
