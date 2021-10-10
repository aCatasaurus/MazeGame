#ifndef __GAME__H__
#define __GAME__H__

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "olcPixelGameEngine.h"
#include <algorithm>    // min
#include <stdlib.h> // exit, EXIT_FAILURE
#include <stdexcept>
#include "map.h"
#include "point.h"
#include "random_walk.h"
#include "sprites.h"
#include "spritedata.h"

constexpr float FRAME_TIME = 1.0f / 60.0f;
constexpr int INPUT_DELAY = 6;
constexpr int TILE_SIZE = 8;
constexpr int PXL_SIZE = 3;


class Game : public olc::PixelGameEngine {
protected:
    Sprites* barrierSprs;
    Sprites* charSprs;
    Sprites* doorSprs;
    Sprites* wallSprs;
    Sprites* floorSprs;
    Sprites* fogSprs[FOG_N];
    olc::Sprite endcardSpr;
    olc::Sprite ladderSpr;
    olc::Sprite keySpr;
    bool moving;
    int input_delay;

    Map* map;
    byte** explored;
    byte** tile_seed;
    Point exit;
    Point entrance;
    Point player;
    Points keys;
    bool over;
    Direction facing;

    void draw();
    void map_init(int rows, int cols);
    bool move(byte direction);
    void update_fog();

public:
    Game(int rows, int cols);
    Game(int rows, int cols, Point start, Point end, Points keys);
    ~Game();

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    void run();
};


#endif//__GAME__H__
