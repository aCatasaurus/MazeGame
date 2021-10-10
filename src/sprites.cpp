#include "sprites.h"


Sprites::Sprites(const char * const files[]) {
    for ( int i = 0; files[i] != nullptr; ++i )
        push_back(std::make_unique<olc::Sprite>(files[i]));
}


SpritePtr& Sprites::rand() {
    return (*this)[::rand() % size()];
}


SpritePtr& Sprites::rand(int seed) {
    return (*this)[seed % size()];
}
