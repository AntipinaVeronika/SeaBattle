#ifndef AQ
#define AQ
#include "IAbilities.h"
#include "../src/empty_queue_error.cpp"
#include <queue>
#include <random>
#include <algorithm>

class AbilitiesManager{
private:
    //Gameboard& gameboard;
    std::queue<IAbility*> ability_queue;
    std::string code = "";
public:
//DEBUG ONLY!
    //std::queue<IAbility*> ability_queue;
    AbilitiesManager() = default;
    AbilitiesManager( Gameboard& gameboard );
    ~AbilitiesManager();
//copy
    AbilitiesManager( const AbilitiesManager& other );
    AbilitiesManager& operator=( const AbilitiesManager& other );
//move
    AbilitiesManager( AbilitiesManager&& other );
    AbilitiesManager& operator = ( AbilitiesManager&& other );
    
    void addAbility( Gameboard& gameboard );
    void addAbility( Gameboard& gameboard, char code );
    void useAbility();
    std::string getCoded();


    IAbility*
    get_front();
};
#endif