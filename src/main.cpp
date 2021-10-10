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

    if ( argc == 1 )
    {
        random_init(args);
        return true;
    }

    for ( int i = 1; i < argc; i++ ) // parse argv
    {
        try // catch invalid args via i >= argc checks and invalid input types
        {
            if ( i == 1 )
            {
                if ( argc == 2 && strcmp( argv[1], "-r" ) == 0)
                {
                    random_init(args);
                }
                else
                {
                    if ( i + 2 > argc )
                        throw string( "too few values" );

                    args.rows = atoi( argv[i] );
                    args.cols = atoi( argv[i + 1] );

                    args.exit = Point(-1, -1);

                    ++i;
                }
            }
            else if ( strcmp( argv[i], "-r" ) == 0 ) { // random setup
                random_init(args);
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


void random_init(Parameters& args) {
    srand((unsigned)time(NULL));

    int& rs = args.rows;
    int& cs = args.cols;

    if ( rs == 0 || cs == 0 ) {
        const int rmin = 4, rmax = 10;
        const int cmin = 4, cmax = 20;
        rs = rmin + rand() % (rmax - rmin + 1);
        cs = cmin + rand() % (cmax - cmin + 1);
    }

    Points objs;
    const int weight = rand() % ((rs * cs) / (2 * (rs + cs)) + 1);

    for ( int i = 0; i < weight + 2 + 1; ++i ) { // 2 for entrance/exit, 1 for a guaranteed key
        Point obj(rand() % cs, rand() % rs);
        while ( objs.contains(obj) )
            obj = Point(rand() % cs, rand() % rs);
        objs.push_back(obj);
    }

    // make entrance and exit the farthest from each other
    args.start = objs.back();
    objs.pop_back();
    sort(objs.begin(), objs.end(),
        [args](Point a, Point b) { return a.dist(args.start) < b.dist(args.start); }
    );

    args.exit = objs.back();
    args.keys.insert(args.keys.end(), objs.begin(), objs.end() - 1);
}


void usage(char* name)
{
    printf("Usage: %s [-h] (rows cols | [rows cols] -r) [-s <r> <c>] [-e <r> <c>] [-k <r> <c> [-k ...]]\n"
    "\trows : the number of rows in the maze\n"
    "\tcols : the number of columns in the maze\n"
    "\t-r : generate a random maze (for this, rows and cols are optional)\n"
    "\t-h : display this information\n"
    "\t-s : the starting position, e.g., '-s <row> <column>; default = (0, 0)'\n"
    "\t-e : position of the exit; default = (rows - 1, cols - 1)\n"
    "\t-k : position for a key to be placed, may be given multiple times\n"
    "\tNo arguments is equivalent to \"-r\".\n",
    name
    );
}
