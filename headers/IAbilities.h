#ifndef IA
#define IA

#include "input_handler.h"

class IAbility{
public:
    virtual void activateAbility() = 0;
    virtual char secretCode() = 0;
    virtual IAbility* clone() = 0;
};

class DoubleDamage: public IAbility{
    Gameboard& gameboard;
public:
    DoubleDamage( Gameboard& gameboard );
    DoubleDamage(const DoubleDamage& other);
    
    void activateAbility();
    char secretCode();
    IAbility* clone();
};

class Scanner: public IAbility{
    int x = 0;
    int y = 0;
    // std::vector < std::vector <Cell> > area;
    Gameboard& gameboard;
public:
    Scanner( Gameboard& gameboard );
    Scanner(const Scanner& other);

    void activateAbility();
    char secretCode();
    IAbility* clone();
};

class Rafale: public IAbility{
    Gameboard& gameboard;
public:
    Rafale( Gameboard& gameboard );
    Rafale(const Rafale& other);

    void activateAbility();
    char secretCode();
    IAbility* clone();
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