#define OLC_PGE_APPLICATION
#include "main.h"


int main(int argc, char** argv)
{
    Parameters args;

    if ( !parse_args(argc, argv, args) )
    {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    Game game(args.rows, args.cols, args.start, args.exit, args.keys);

    game.run();

    return EXIT_SUCCESS;
}


bool parse_args(int argc, char** argv, Parameters& args)
{
    args.rows = args.cols = 0;
    args.start = Point(-1, -1);

    for ( int i = 1; i < argc; i++ ) // parse argv
    {
        try // catch invalid args via i >= argc checks and invalid input types
        {
            if ( i == 1 )
            {
                if ( i + 2 > argc )
                    throw string( "too few values" );

                args.rows = atoi( argv[i] );
                args.cols = atoi( argv[i + 1] );

                args.exit = Point(-1, -1);

                ++i;
            }
            else if ( strcmp( argv[i], "-k" ) == 0 ) // add a key
            {
                if ( i + 2 >= argc )
                    throw string( "-k coordinates not given" );

                args.keys.emplace_back( atoi(argv[i + 1]), atoi(argv[i + 2]) );

                ++++i;
            }
            else if ( strcmp( argv[i], "-s" ) == 0 ) // start position
            {
                if ( i + 2 >= argc )
                    throw string( "-s too few values" );

                args.start = Point( atoi( argv[i + 1] ), atoi( argv[i + 2] ) );

                ++++i;
            }
            else if ( strcmp( argv[i], "-e" ) == 0 ) // exit position
            {
                if ( i + 2 >= argc )
                    throw string( "-e too few values" );

                args.exit = Point( atoi( argv[i + 1] ), atoi( argv[i + 2] ) );

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

    if ( args.start == Point(-1, -1) )
        args.start = Point(0, 0);

    if ( args.exit == Point(-1, -1) )
        args.exit = Point(args.cols - 1, args.rows - 1);

    if ( args.rows == 0 || args.cols == 0 )
        return false;

    return true;
}


void usage(char* name)
{
    printf("Usage: %s [-h] rows cols -s <r> <c> -e <r> <c> [-k <r> <c> [-k ...]]\n"
    "\trows : the number of rows in the maze\n"
    "\tcols : the number of columns in the maze\n"
    "\t-h : display this information\n"
    "\t-s : the starting position, e.g., '-s <row> <column>; default = (0, 0)'\n"
    "\t-e : position of the exit; default = (rows - 1, cols - 1)\n"
    "\t-k : position for a key to be placed, may be given multiple times\n",
    name
    );
}
