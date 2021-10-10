#ifndef __SMART__SPRITE__H__
#define __SMART__SPRITE__H__

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "olcPixelGameEngine.h"
#include <memory>
#include <stdlib.h> // rand
#include <vector>

typedef std::unique_ptr<olc::Sprite> SpritePtr;

using std::vector;


class Sprites : public vector<SpritePtr> {
public:
    using vector<SpritePtr>::vector;
    Sprites(const char * const files[]);

    SpritePtr& rand();
    SpritePtr& rand(int seed);
};


#endif//__SMART__SPRITE__H__
