#include "map.h"

using std::ostream;


Map::Map(int height, int width) : ROWS(height), COLS(width)
{
    data = alloc2D(ROWS, COLS, ALL);
    repr = (char**)alloc2D(ROWS * 2 + 1, COLS * 2 + 1, '#');

    srand(time(NULL));

    generate();
}

Map::~Map()
{
    free2D(data);
    free2D((byte**)repr);
}

Tile Map::at(Point row_col) { return at(row_col.r, row_col.c); }

Tile Map::at(int row, int col)
{
    if ( ( row < 0 || row >= ROWS ) || ( col < 0 || col >= COLS ) )
        throw std::domain_error("Error: position is not in the maze!");

    return Tile(
        &(repr[row * 2 + 1][col * 2 + 1]),
        &(data[row][col]),
        COLS
    );
}

Point Map::rand_adj(Point pt)
{
    if ( rand() % 2 ) // change row
    {
        if ( (pt.r - 1 < 0) || ((pt.r + 1 < ROWS) && (rand() % 2)) )
            pt.r += 1;
        else
            pt.r -= 1;
    }
    else // change column
    {
        if ( (pt.c - 1 < 0) || ((pt.c + 1 < COLS) && (rand() % 2)) )
            pt.c += 1;
        else
            pt.c -= 1;
    }

    return pt;
}

void Map::join(Point a, Point b)
{
    if ( abs(a.r - b.r) == 1 )
    {
        if ( a.r > b.r )
        {
            at(a).set(0, NORTH);
            at(b).set(0, SOUTH);
        }
        else
        {
            at(a).set(0, SOUTH);
            at(b).set(0, NORTH);
        }
    }
    else if ( abs(a.c - b.c) == 1 )
    {
        if ( a.c > b.c )
        {
            at(a).set(0, WEST);
            at(b).set(0, EAST);
        }
        else
        {
            at(a).set(0, EAST);
            at(b).set(0, WEST);
        }
    }
    else
        throw std::domain_error("Error: points to be joined are not adjacent!");
}

void Map::generate()
{
    // get vector of all points in the map
    Points pts_to_add;
    for ( int i = 0, j; i < ROWS; i++ )
        for ( j = 0; j < COLS; j++ )
            pts_to_add.push_back(Point(i, j));

    // move one point to the completed map
    Points pts_added = { pts_to_add.back() };
    pts_added.reserve(pts_to_add.size());
    pts_to_add.pop_back();

    // add paths to the map until there are no unconnected points
    while ( !pts_to_add.empty() )
    {
        Point pt = pts_to_add.rand(); // random starting point
        Points path = { pt };

        do // add points until the path joins the completed map
        {
            pt = rand_adj(pt);

            // if the path loops, start over
            if ( path.contains(pt) )
            {
                path.clear();
                pt = pts_to_add.rand();
                path.push_back(pt);
            }
            else
                path.push_back(pt);
        }
        while ( pts_to_add.contains(pt) );

        // add path to completed map, i.e.,
        // join points in path and move them from pts_to_add to pts_added
        for ( unsigned i = 0; i < path.size() - 1; ++i )
        {
            join(path[i], path[i + 1]);
            pts_to_add.remove(path[i]);
            pts_added.push_back(path[i]);
        }
    }
}

void Map::print(ostream& out)
{
    out << '/';
    for ( int i = 0; i < COLS * 2 + 1; ++i ) out << '~';
    out << "\\\n";

    for ( int i = 0; i < ROWS * 2 + 1; ++i )
    {
        out << "|";
        for ( int j = 0; j < COLS * 2 + 1; ++j ) out << repr[i][j];
        out << "|\n";
    }

    out << '\\';
    for ( int i = 0; i < COLS * 2 + 1; ++i ) out << '~';
    out << "/\n";
}


const char * const * const Map::get() const {
    return repr;
}
