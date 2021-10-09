#ifndef __TILE__H__
#define __TILE__H__

typedef unsigned char byte;

// tile displays
constexpr char CHAR = '&';
constexpr char DOOR = 'N';
constexpr char ITEM = '%';
constexpr char OPEN = ' ';
constexpr char WALL = '#';

enum Direction : byte {
    NORTH = 0b0001,
    SOUTH = 0b0010,
    EAST  = 0b0100,
    WEST  = 0b1000,
    ALL   = 0b1111,
};
constexpr byte BYTE_MASK = 0xFF;
constexpr byte PLAYER    = 0b00010000;
constexpr byte EXIT      = 0b00100000;
constexpr byte KEY       = 0b01000000;


class Tile
{
protected:
    char* center;
    byte* state;
    int cols;

public:
    Tile(char* ptr, byte* state, int cols);

    byte get();
    void set(byte new_state, byte mask = BYTE_MASK);
};


#endif//__TILE__H__
