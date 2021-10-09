#include "alloc2D.h"


byte** alloc2D(int rows, int cols, byte value)
{
    byte** ptrs = new byte*[rows];
    if ( ptrs == nullptr ) return nullptr;

    byte* bytes = new byte[rows * cols];
    if ( bytes == nullptr )
    {
        delete [] ptrs;
        return nullptr;
    }

    memset( bytes, value, rows * cols * sizeof(byte) );

    for ( int row = 0; row < rows; ++row, bytes += cols )
        ptrs[row] = bytes;

    return ptrs;
}


void free2D(byte** ptrs)
{
    if ( ptrs )
    {
        if ( *ptrs ) delete [] *ptrs;
        delete [] ptrs;
    }
}
