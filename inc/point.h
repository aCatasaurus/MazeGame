#ifndef __POINT__H__
#define __POINT__H__

#include <algorithm> // find
#include <iostream>
#include <stdlib.h> // rand
#include <vector>

using std::ostream;
using std::vector;


struct Point
{
    int r, c;
    Point();
    Point(int row, int col);
    bool operator==(const Point& o) const;
};

ostream& operator<<(ostream& out, Point p);


class Points : public vector<Point>
{
public:
    using vector<Point>::vector; // inherit vector ctors

    Point rand() const;
    void remove(Point);
    bool contains(Point) const;
};

ostream& operator<<(ostream& out, const Points& pts);


#endif//__POINT__H__
