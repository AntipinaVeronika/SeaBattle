#ifndef IA
#define IA

#include "input_handler.h"

class IAbility{
public:
    virtual void activateAbility() = 0;
};

class DoubleDamage: public IAbility{
    Gameboard& gameboard;
public:
    DoubleDamage( Gameboard& gameboard );
    
    void activateAbility();
};

class Scanner: public IAbility{
    int x = 0;
    int y = 0;
    // std::vector < std::vector <Cell> > area;
    Gameboard& gameboard;
public:
    Scanner( Gameboard& gameboard );

    void activateAbility();
};

class Rafale: public IAbility{
    Gameboard& gameboard;
public:
    Rafale( Gameboard& gameboard );

    void activateAbility();
};
#endif

// int main(){
//     Gameboard gameboard( 10, 10 );
//     std::vector<int>sizes = {1};
//     std::vector<int>nums = {1};
//     ShipManager manager( nums, sizes );

//     gameboard.addShip( manager.getShipIdx(0), 0, 0, Position::HORIZONTAL );

//     DoubleDamage dd( gameboard );
//     dd.activateAbility();
//     gameboard.hitShip(0,0);
//     std::cout << manager.isOver();

//     return 0;
// }