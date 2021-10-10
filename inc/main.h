#ifndef __MAIN__HEADER__H__
#define __MAIN__HEADER__H__

#include <stdlib.h> // exit, EXIT_FAILURE, atoi
#include <stdio.h> // printf
#include <string>
#include "game.h"

using std::cout;
using std::endl;
using std::string;

struct Parameters {
    int rows, cols;
    Point start, exit;
    Points keys;
};


bool parse_args(int argc, char** argv, Parameters& args);
void random_init(Parameters& args);
void usage(char* name);


#endif//__MAIN__HEADER__H__
