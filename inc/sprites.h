#ifndef __SMART__SPRITE__H__
#define __SMART__SPRITE__H__

#include <stdlib.h> // rand
#include <vector>
#include "olcPixelGameEngine.h"

using std::vector;


class Sprites : public vector<olc::Sprite*> {
public:
    using vector<olc::Sprite*>::vector;
    Sprites(const char * const files[]);

    olc::Sprite* rand();
    olc::Sprite* rand(int seed);
};


#endif//__SMART__SPRITE__H__
