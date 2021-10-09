#include "random_walk.h"

constexpr int DY = 2;
constexpr int DX = 2;


void join(TileGetter at, Point a, Point b);
Point rand_adj(Point pt, int width, int height);


void random_walk(TileGetter at, int width, int height) {
    // get vector of all points in the map
    Points pts_to_add;
    for ( int x = 1, y; x < width; x += DX )
        for ( y = 1; y < height; y += DY )
            pts_to_add.push_back(Point(x, y));

    // move one point to the completed map
    Points pts_added = { pts_to_add.back() };
    pts_added.reserve(pts_to_add.size());
    pts_to_add.pop_back();

    // add paths to the map until there are no unconnected points
    while ( !pts_to_add.empty() ) {
        Point pt = pts_to_add.rand(); // random starting point
        Points path = { pt };

        do {    // add points until the path joins the completed map
            pt = rand_adj(pt, width, height);

            // if the path loops, start over
            if ( path.contains(pt) ) {
                path.clear();
                pt = pts_to_add.rand();
                path.push_back(pt);
            } else
                path.push_back(pt);
        } while ( pts_to_add.contains(pt) );

        // add path to completed map, i.e.,
        // join points in path and move them from pts_to_add to pts_added
        for ( unsigned i = 0; i < path.size() - 1; ++i ) {
            join(at, path[i], path[i + 1]);
            pts_to_add.remove(path[i]);
            pts_added.push_back(path[i]);
        }
    }
}


void join(TileGetter at, Point a, Point b) {
    at(a.x, a.y) = OPEN;
    at(b.x, b.y) = OPEN;

    if ( abs(a.x - b.x) == DX )
        at((a.x + b.x) / 2, a.y) = OPEN;

    else
        at(a.x, (a.y + b.y) / 2) = OPEN;
}


Point rand_adj(Point pt, int width, int height) {
    if ( rand() % 2 ) { // change x
        if ( (pt.x - DX < 0) || ((pt.x + DX < width) && (rand() % 2)) )
            pt.x += DX;

        else
            pt.x -= DX;

    } else {    // change y
        if ( (pt.y - DY < 0) || ((pt.y + DY < height) && (rand() % 2)) )
            pt.y += DY;

        else
            pt.y -= DY;
    }

    return pt;
}
