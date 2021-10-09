#include "map.h"


Map::Map(int width, int height) : ROWS(height), COLS(width)
{
    data = alloc2D(ROWS, COLS, WALL);
}

Map::~Map()
{
    free2D(data);
}

byte& Map::    at(int x, int y)       { return data[ROWS - 1 - y][x]; }
byte  Map::   get(int x, int y) const { return data[ROWS - 1 - y][x]; }
int   Map::height()             const { return ROWS; }
int   Map:: width()             const { return COLS; }

void Map::generate(Generator generator) {
    // passes this->at (as a lambda), width, and height to the generator
    byte&(Map::*at_ptr)(int, int) = &Map::at;
    TileGetter getter = [this, at_ptr](int x, int y) -> byte& {
        return (this->*at_ptr)(x, y);
    };
    generator(getter, width(), height());
}

void Map::print(ostream& out)
{
    out << '/';
    for ( int i = 0; i < COLS; ++i ) out << '~';
    out << "\\\n";

    for ( int i = ROWS - 1; i >= 0; --i )
    {
        out << '|';
        for ( int j = 0; j < COLS; ++j )
            out << data[i][j];
        out << "|\n";
    }

    out << '\\';
    for ( int i = 0; i < COLS; ++i ) out << '~';
    out << "/\n";
}
