#include "../headers/ability_manager.h"

AbilitiesManager::AbilitiesManager( Gameboard& gameboard ){
    std::vector <IAbility*> abilities = { new DoubleDamage( gameboard ), new Scanner( gameboard ), new Rafale( gameboard ) };

    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(abilities.begin(), abilities.end(), g);
    for( int i = 0; i < 3; i++ ){
        ability_queue.push( abilities.at(i) );
        code += abilities.at(i)->secretCode();
    }
}

AbilitiesManager::AbilitiesManager(const AbilitiesManager& other) : code(other.code) {
    std::queue<IAbility*> temp_queue;

    std::queue<IAbility*> otherQueue = other.ability_queue;

    while (!otherQueue.empty()) {
        IAbility* ab = otherQueue.front();
        temp_queue.push(ab->clone());
        otherQueue.pop();
    }

    ability_queue = std::move(temp_queue);
}

AbilitiesManager& AbilitiesManager::operator=(const AbilitiesManager& other) {
    if (this != &other) {
        while (!ability_queue.empty()) {
            delete ability_queue.front();
            ability_queue.pop();
        }

        code = other.code;

        std::queue<IAbility*> temp_queue;
        std::queue<IAbility*> otherQueue = other.ability_queue;
        while (!otherQueue.empty()) {
            IAbility* ab = otherQueue.front();
            temp_queue.push(ab->clone());
            otherQueue.pop();
        }
        
        ability_queue = std::move(temp_queue);
    }
    return *this;
}
AbilitiesManager::AbilitiesManager(AbilitiesManager&& other) 
    : ability_queue(std::move(other.ability_queue)), 
      code(std::move(other.code)) {
    // Присваиваем пустой другой объект
    other.code.clear();
}

AbilitiesManager& AbilitiesManager::operator=(AbilitiesManager&& other){
    if (this != &other) {
        while (!ability_queue.empty()) {
            delete ability_queue.front();
            ability_queue.pop();
        }

        ability_queue = std::move(other.ability_queue);
        code = std::move(other.code);

        other.code.clear();
    }
    return *this;
}

AbilitiesManager::~AbilitiesManager(){
    while (!ability_queue.empty()) {
            delete ability_queue.front();
            ability_queue.pop();
    }
}

void
AbilitiesManager::addAbility( Gameboard& gameboard ){
    std::vector <IAbility*> abilities = { new DoubleDamage( gameboard ), new Scanner( gameboard ), new Rafale( gameboard ) };

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(abilities.begin(), abilities.end(), g);
    ability_queue.push( abilities.at(0) );
    this->code += abilities.at(0)->secretCode();

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
   // IAbility* tmp = ab;
    ability_queue.pop();
    code.erase( 0, 1 );
    delete ab;
}

void
AbilitiesManager::addAbility( Gameboard& gb, char c ){
    switch( c ){
        case '0':
        {
            IAbility* ab = new DoubleDamage( gb );
            ability_queue.push(ab);
            code += '0';
            break;
        }
        case '1':
        {
            IAbility* ab = new Scanner( gb );
            ability_queue.push(ab);
            code += '1';
            break;
        }
        default:
        {
            IAbility* ab = new Rafale( gb );
            ability_queue.push(ab);
            code += '2';
        }
    }
}

std::string
AbilitiesManager::getCoded(){
    return code;
}

IAbility*
AbilitiesManager::get_front(){
    return ability_queue.front();
}