#ifndef __MAP__H__
#define __MAP__H__

#include <iostream>     // cout, ostream
#include <stdlib.h>     // rand, srand
#include <time.h>       // time
#include <functional>   // function
#include "alloc2D.h"

using std::cout;
using std::function;
using std::ostream;

typedef function<byte&(int, int)> TileGetter;
typedef void(*Generator)(TileGetter, int, int);

enum Tile : char { CHAR = '@', OPEN = ' ', WALL = '#', EXIT = 'n', KEY  = '%' };
enum Direction : char { NONE, NORTH, SOUTH, EAST, WEST };


class Map
{
protected:
    byte** data;
    int ROWS, COLS;

public:
    Map(int width, int height);
    ~Map();

    byte& at(int x, int y);
    byte get(int x, int y) const;
    int height() const;
    int width() const;

    void generate(Generator);
    void print(ostream& out = cout);
};


#endif//__MAP__H__