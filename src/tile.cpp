#include "tile.h"


Tile::Tile(char* ptr, byte* state, int columns)
    : center(ptr), state(state), cols(columns) {}

byte Tile::get() { return *state; }

void Tile::set(byte new_state, byte mask)
{
    if ( new_state != *state )
    {
        // set walls
        if ( mask & NORTH )
            *(center - (cols * 2 + 1)) = ( new_state & NORTH ? WALL : OPEN );

        if ( mask & SOUTH )
            *(center + (cols * 2 + 1)) = ( new_state & SOUTH ? WALL : OPEN );

        if ( mask & EAST )
            *(center + 1 ) = ( new_state & EAST ? WALL : OPEN );

        if ( mask & WEST )
            *(center - 1 ) = ( new_state & WEST ? WALL : OPEN );

        // update state
        *state = (*state & ~mask) | (new_state & mask);

        // set center
        if ( new_state & PLAYER )
            *center = CHAR;
        else if ( new_state & EXIT )
            *center = DOOR;
        else if ( new_state & KEY )
            *center = ITEM;
        else
            *center = ( *state == ALL ? WALL : OPEN );
    }
}
