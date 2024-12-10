#include "../headers/printer.h"

void
Printer::printUsersGameboard(std::vector < std::vector <Cell> > p_gameboard, int width, int height ){
    for( int i = 0; i < height; i++ ){
        for( int j = 0; j < width; j++ ){
            if( (p_gameboard.at(i)).at(j).state == State::EMPTY )
                std::cout << "* ";
            else{
                if( (*(p_gameboard.at(i)).at(j).ship).getSegment((p_gameboard.at(i)).at(j).seg_idx)==Segment::DAMAGED )
                    std::cout << "$ ";
                else if( (*(p_gameboard.at(i)).at(j).ship).getSegment((p_gameboard.at(i)).at(j).seg_idx)==Segment::INTACT )
                    std::cout << "S ";
                else
                    std::cout << "X ";
            }
        }
        std::cout << '\n';
    }
    std::cout << "------------------------------------------------------------------------\n\n";
}

void
Printer::printHiddenGameboard( std::vector < std:: vector <Cell> > e_gameboard, int width, int height ){
    std::cout << "  ";
    for( int j = 0; j < width; j++ ){
        std::cout << j << ' ';
    }
    std::cout << '\n';
    for( int i = 0; i < height; i++ ){
        std::cout << i << ' ';
        for( int j = 0; j < width; j++ ){
            if( (e_gameboard.at(i)).at(j).state == EMPTY )
                std::cout << "  ";
            else if( (e_gameboard.at(i)).at(j).state == SHIP ){
                if( (*(e_gameboard.at(i)).at(j).ship).getSegment((e_gameboard.at(i)).at(j).seg_idx)==Segment::DAMAGED )
                    std::cout << "$ ";
                else if( (*(e_gameboard.at(i)).at(j).ship).getSegment((e_gameboard.at(i)).at(j).seg_idx)==Segment::DESTROYED )
                    std::cout << "X ";
                else
                    std::cout << "S ";
            }else{
                std::cout << "? ";
            }
        }
        std::cout << '\n';
    }
    std::cout << "------------------------------------------------------------------------\n\n";
}