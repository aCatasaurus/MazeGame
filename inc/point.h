#ifndef __POINT__H__
#define __POINT__H__

#include <algorithm> // find
#include <iostream>
#include <math.h>   // pow
#include <stdlib.h> // rand
#include <vector>

using std::ostream;
using std::vector;


struct Point {
    int x, y;

    Point();
    Point(int x, int y);

    Point operator*(int scalar) const;
    Point operator+(const Point& o) const;
    bool operator==(const Point& o) const;

    double dist(Point) const;
};

ostream& operator<<(ostream& out, Point p);


class Points : public vector<Point> {
public:
    using vector<Point>::vector; // inherit vector ctors

    bool contains(Point) const;
    Point rand() const;
    void remove(Point);
};

ostream& operator<<(ostream& out, const Points& pts);


#endif//__POINT__H__
