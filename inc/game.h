#ifndef __GAME__H__
#define __GAME__H__

#include "olcPixelGameEngine.h"
#include <limits>
#include <stdlib.h> // exit, EXIT_FAILURE
#include "map.h"

using std::streamsize;
enum Orientation : byte { UP, LEFT, DOWN, RIGHT };
constexpr const char* DIRECTION_CSTRINGS[4] = { "Forward", "Right", "Back", "Left" };
constexpr streamsize MAX_BUFF_SIZE = std::numeric_limits<streamsize>::max();
constexpr float FRAME_TIME = 1 / 60.0;


class Game : public olc::PixelGameEngine
{
protected:
    olc::Sprite charSpr, wallSpr, doorSpr, itemSpr;

    int width, height;

    Map map;
    Point exit;
    Point player;
    Points keys;
    bool over;
    byte facing;

    void draw();
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
