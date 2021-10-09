#define OLC_PGE_APPLICATION
#include <stdlib.h> // exit, EXIT_FAILURE, atoi
#include <stdio.h> // printf
#include <string>

#include "game.h"

using std::cout;
using std::endl;
using std::string;


bool parse_args(int argc, char** argv,
                int& rows, int& cols, Point& start, Point& end, Points& keys);
void usage(char** argv);


int main(int argc, char** argv)
{
    int rows, cols;
    Point start, end;
    Points keys;

    if ( !parse_args(argc, argv, rows, cols, start, end, keys) )
    {
        usage(argv);
        return EXIT_FAILURE;
    }

    Game game(rows, cols, start, end, keys);

    game.run();

    return EXIT_SUCCESS;
}


bool parse_args(int argc, char** argv,
                int& rows, int& columns, Point& start, Point& exit, Points& keys)
{
    rows = columns = 0;
    start = Point(0, 0);

    for ( int i = 1; i < argc; i++ ) // parse argv
    {
        try // catch invalid args via i >= argc checks and invalid input types
        {
            if ( i == 1 )
            {
                if ( i + 2 > argc )
                    throw string( "too few values" );

                rows = atoi( argv[i] ); columns = atoi( argv[i + 1] );

                exit = Point(-1, -1);

                ++i;
            }
            else if ( strcmp( argv[i], "-k" ) == 0 ) // add a key
            {
                if ( i + 2 >= argc )
                    throw string( "-k coordinates not given" );

                keys.emplace_back( atoi(argv[i + 1]), atoi(argv[i + 2]) );

                ++++i;
            }
            else if ( strcmp( argv[i], "-s" ) == 0 ) // start position
            {
                if ( i + 2 >= argc )
                    throw string( "-s too few values" );

                start = Point( atoi( argv[i + 1] ), atoi( argv[i + 2] ) );

                ++++i;
            }
            else if ( strcmp( argv[i], "-e" ) == 0 ) // exit position
            {
                if ( i + 2 >= argc )
                    throw string( "-e too few values" );

                exit = Point( atoi( argv[i + 1] ), atoi( argv[i + 2] ) );

                ++++i;
            }
            else if ( strcmp( argv[i], "-h" ) == 0 ) // help
            {
                return false;
            }
            else
            {
                throw string( "Argument not recognized: " ) + argv[i];
            }
        }
        catch (string error)
        {
            printf("Error: %s\n", error.c_str());
            return false;
        }
    }

    if ( exit.r == -1 )
        exit = Point(rows - 1, columns - 1);

    if ( rows == 0 || columns == 0 )
        return false;

    return true;
}


void usage(char** argv)
{
    printf("Usage: %s [-h] rows cols -s <r> <c> -e <r> <c> [-k <r> <c> [-k ...]]\n"
    "\trows : the number of rows in the maze\n"
    "\tcols : the number of columns in the maze\n"
    "\t-h : display this information\n"
    "\t-s : the starting position, e.g., '-s <row> <column>; default = (0, 0)'\n"
    "\t-e : position of the exit; default = (rows - 1, cols - 1)\n"
    "\t-k : position for a key to be placed, may be given multiple times\n",
    argv[0]
    );
}
