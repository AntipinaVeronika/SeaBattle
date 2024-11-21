#include "ability_manager.h"

AbilitiesManager::AbilitiesManager( Gameboard& gameboard ){
    std::vector <IAbility*> abilities = { new DoubleDamage( gameboard ), new Scanner( gameboard ), new Rafale( gameboard ) };

    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(abilities.begin(), abilities.end(), g);
    for( int i = 0; i < 3; i++ ){
        ability_queue.push( abilities.at(i) );
    }
}

void
AbilitiesManager::addAbility( Gameboard& gameboard ){
    std::vector <IAbility*> abilities = { new DoubleDamage( gameboard ), new Scanner( gameboard ), new Rafale( gameboard ) };

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(abilities.begin(), abilities.end(), g);
    ability_queue.push( abilities.at(0) );
    delete abilities.at(1);
    delete abilities.at(2);
    //милая девушка посоветовала с шаблонами - обсудить с Костей!
}

void
AbilitiesManager::useAbility(){
    if( ability_queue.size() == 0 ){
        throw EmptyQueue();
    }

    std::cout << "QUEUE SIZE " << ability_queue.size() << '\n';

    IAbility* ab = ability_queue.front();
    ab->activateAbility();
    IAbility* tmp = ab;
    ability_queue.pop();
    delete ab;
}