#include "point.h"


/*******************************************************************************
*                               Point Functions                                *
*******************************************************************************/

Point::Point() : x(0), y(0) {}

Point::Point(int _x, int _y) : x(_x), y(_y) {}

Point Point::operator*(int scalar) const {
    return Point(x * scalar, y * scalar);
}

Point Point::operator+(const Point& other) const {
    return Point(this->x + other.x, this->y + other.y);
}

bool Point::operator==(const Point& other) const
{
    return (this->x == other.x) && (this->y == other.y);
}

ostream& operator<<(ostream& out, Point pt)
{
    return out << '(' << pt.x << ", " << pt.y << ')';
}


/*******************************************************************************
*                              Points Functions                                *
*******************************************************************************/

Point Points::rand() const
{
    return (*this)[::rand() % size()];
}

void Points::remove(Point pt)
{
    auto iter = find(begin(), end(), pt);

    if ( iter == end() )
        throw std::domain_error("Error: point to be removed is not in vector!");

    erase(iter);
}

bool Points::contains(Point pt) const
{
    return find(begin(), end(), pt) != end();
}

ostream& operator<<(ostream& out, const Points& pts)
{
    out << '[';
    if ( !pts.empty() )
    {
        unsigned i;
        for ( i = 0; i < pts.size() - 1; ++i )
            out << pts[i] << ", ";
        out << pts[i];
    }
    out << ']';

    return out;
}
