#include "point.h"


Point::Point() : r(0), c(0) {}

Point::Point(int row, int col) : r(row), c(col) {}

bool Point::operator==(const Point& o) const
{
    return (r == o.r) && (c == o.c);
}

ostream& operator<<(ostream& out, Point pt)
{
    return out << "(r=" << pt.r << ", c=" << pt.c << ')';
}


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
    unsigned i;

    out << '[';
    if ( !pts.empty() )
    {
        for ( i = 0; i < pts.size() - 1; ++i )
            out << pts[i] << ", ";
        out << pts[i];
    }
    out << ']';

    return out;
}
