#ifndef __ALLOC2D__H__
#define __ALLOC2D__H__

#include <string.h> // memset

typedef unsigned char byte;


byte** alloc2D(int rows, int cols, byte value = 0);
void free2D(byte** ptrs);


#endif//__ALLOC2D__H__
