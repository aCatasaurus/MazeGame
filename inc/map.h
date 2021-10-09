#ifndef __MAP__H__
#define __MAP__H__

#include <iostream>
#include <stdlib.h> // rand, srand
#include <time.h> // time
#include "alloc2D.h"
#include "tile.h"
#include "point.h"

using std::cout;
using std::ostream;


class Map
{
protected:
    byte** data;
    char** repr;

    void join(Point, Point);
    Point rand_adj(Point);
    void generate();

public:
    const int ROWS, COLS;

    Map(int height, int width);
    ~Map();

    Tile at(Point);
    Tile at(int row, int col);
    void print(ostream& out = std::cout);

    const char * const * const get() const;
};


#endif//__MAP__H__
