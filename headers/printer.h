#ifndef PRINTER
#define PRINTER
#include <iostream>
#include <vector>
#include "gameboard.h"
class Printer{
public:
    void
    printUsersGameboard(std::vector < std::vector <Cell> > p_gameboard, int width, int height );
    void
    printHiddenGameboard( std::vector < std:: vector <Cell> > e_gameboard, int width, int height );
};
#endif