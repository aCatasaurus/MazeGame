#include "sprites.h"


Sprites::Sprites(const char * const files[]) {
    for ( int i = 0; files[i] != nullptr; ++i ) {
        olc::Sprite* ptr = new olc::Sprite(files[i]);
        push_back(ptr);
    }
}


olc::Sprite* Sprites::rand() {
    return (*this)[::rand() % size()];
}


olc::Sprite* Sprites::rand(int seed) {
    return (*this)[seed % size()];
}
