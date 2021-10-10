#ifndef __SPRITE__DATA__H__
#define __SPRITE__DATA__H__

#define PATH "./assets/sprites/"
constexpr int FOG_N = 4;


constexpr const char * const BARRIER_SPRS[] = {
    PATH "barrier0.png", PATH "barrier1.png",
    PATH "barrier2.png", PATH "barrier3.png", nullptr
};


constexpr const char * const CHAR_SPRS[] = {
    PATH "characterE.png", PATH "characterW.png",
    PATH "characterN.png", PATH "characterS.png", nullptr
};


constexpr const char * const DOOR_SPRS[] = {
    PATH "doorClosed.png", PATH "doorOpen.png", nullptr
};


constexpr const char * const FLOOR_SPRS[] = {
    PATH "floor0.png", PATH "floor1.png", PATH "floor2.png",
    PATH "floor3.png", PATH "floor4.png", PATH "floor5.png",
    PATH "floor6.png", PATH "floor7.png", PATH "floor8.png", nullptr
};


constexpr const char * const FOG_W_SPRS[] = {
    PATH "wispyfog0.png", PATH "wispyfog1.png", PATH "wispyfog2.png",
    PATH "wispyfog3.png", PATH "wispyfog4.png", nullptr
};


constexpr const char * const FOG_L_SPRS[] = {
    PATH "lightfog0.png", PATH "lightfog1.png",
    PATH "lightfog2.png", nullptr
};


constexpr const char * const FOG_SPRS[] = {
    PATH "fog0.png", PATH "fog1.png",
    PATH "fog2.png", PATH "fog3.png", nullptr
};


constexpr const char * const FOG_H_SPRS[] = {
    PATH "heavyfog0.png", PATH "heavyfog1.png",
    PATH "heavyfog2.png", PATH "heavyfog3.png", nullptr
};


constexpr const char * const WALLS_SPRS[] = {
    PATH "wall0.png", PATH "wall1.png", PATH "wall2.png", PATH "wall3.png",
    PATH "wall4.png", PATH "wall5.png", PATH "wall6.png", nullptr
};


#endif//__SPRITE__DATA__H__
