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
public:
    AbilitiesManager() = default;
    AbilitiesManager( Gameboard& gameboard );
    
    void addAbility( Gameboard& gameboard );
    void useAbility();
};
#endif