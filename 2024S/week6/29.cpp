#include <iostream>
#include <cmath>

using namespace std;

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

    bool operator!=( const Point& other ) const 
    {
	    return !( other.x == x && other.y == y);
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

    Point &getStart() { return point1; };
    Point &getEnd() { return point2; };

    friend std::ostream &operator<<( std::ostream &out, const Segment& s ) 
    {
	    s.point1.printPoint();
	    s.point2.printPoint();
	    out << " -> ";

	    return out;
    }

};

class Shape
{
	public:
		Shape() : edgeCount(0) {};
		Shape( Segment *segments, int _edgeCount ) : edgeCount(_edgeCount) 
		{
			Point *first = &(segments[0].getStart());  
			Point *last = &(segments[edgeCount - 1].getEnd());

			if ( *first != *last )
				throw std::invalid_argument("invalid_argument");
			
			for( size_t i = 0; i < _edgeCount; ++i ) 
				seg[i] = segments[i];

		  }; // to construct a shape with a serial of segment. Throw an invalid_argument if the segment can not construct a close path.

		  virtual float getArea() = 0;
		  float getPerimeter() 
		  {
			  // The perimeter is the sum of all the segment length
			  float perimeter = 0;
			  for ( size_t i = 0; i < edgeCount; ++i )
				  perimeter += getSeg(i).getLength();
			  
			  return perimeter;
		  };

		  Segment &getSeg(int index)
		  {
			return seg[index];
		  }

		private:
		  Segment seg[10];
		  int edgeCount;
};