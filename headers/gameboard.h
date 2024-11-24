#ifndef GAMEBOARD
#define GAMEBOARD
#include "ship_manager.h"
#include "../src/gameboard_errors.cpp"

enum State{
    EMPTY,
    UNKNOWN,
    SHIP,
};
class Cell{
public:
    State state;
    Ship* ship;
    int seg_idx;
    Cell(): state(State::EMPTY), ship(nullptr), seg_idx(-1){}
};

class Gameboard{
    int width;
    int height;
    int damage_amount = 1;
    std::vector < std::vector <Cell>  > p_gameboard;
    std::vector < std::vector <Cell>  > e_gameboard;

    int
    check_placement(int x, int y, Ship* ship, Position position);
public:
    Gameboard(int height = 10, int width = 10);

    Gameboard( const Gameboard& other );

    Gameboard& operator=( const Gameboard& other );

    Gameboard( Gameboard&& other );

    Gameboard& operator= ( Gameboard&& other );

    // ~Gameboard();

    void
    addShip( Ship* black_pearl, int x, int y, Position position );

    void
    hitShip( int x, int y );

    int
    getWidth();

    int
    getHeight();

    std::vector < std::vector <Cell>  > getUsersGameboard();
    std::vector < std::vector <Cell>  > getHiddenGameboard();    

    void
    change_damage_amount();

    void
    reset_damage();
};
#endif
// int main(){
//     Gameboard player1{10,10};
//     Gameboard player2 = player1;

//     Ship black_pearl{5};
//     player1.addShip(&black_pearl, 0, 0, Position(1));
//     player2.printUsersGameboard();
// }
