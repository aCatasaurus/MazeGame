#ifndef __SMART__SPRITE__H__
#define __SMART__SPRITE__H__

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "olcPixelGameEngine.h"
#include <stdlib.h> // rand
#include <vector>

using std::vector;


class Sprites : public vector<olc::Sprite*> {
public:
    using vector<olc::Sprite*>::vector;
    Sprites(const char * const files[]);

    olc::Sprite* rand();
    olc::Sprite* rand(int seed);
};


#endif//__SMART__SPRITE__H__
