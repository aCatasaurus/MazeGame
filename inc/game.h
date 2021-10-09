#ifndef __GAME__H__
#define __GAME__H__

#include "olcPixelGameEngine.h"
#include <stdlib.h> // exit, EXIT_FAILURE
#include <stdexcept>
#include "map.h"
#include "point.h"
#include "random_walk.h"
#include "sprites.h"
#include "spritedata.h"

enum Orientation : byte { RIGHT, LEFT, UP, DOWN };
constexpr float FRAME_TIME = 1 / 60.0;
constexpr int TILE_SIZE = 8;
constexpr int PXL_SIZE = 2;


class Game : public olc::PixelGameEngine
{
protected:
    Sprites* charSprs;
    Sprites* wallSprs;
    Sprites* floorSprs;
    olc::Sprite doorSpr;
    olc::Sprite keySpr;

    Map* map;
    Point exit;
    Point player;
    Points keys;
    bool over;
    byte facing;

    void draw();
    void map_init(int rows, int cols);
    bool move(byte direction);

public:
    Game(int rows, int cols);
    Game(int rows, int cols, Point start, Point end, Points keys);
    ~Game();

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    void run();
};


#endif//__GAME__H__
