#include "time.h"
#include "ability_manager.h"
#include "ship_manager.h"
//#include "game_state.h"
#include "../src/printer_un.cpp"
class Game{
    std::vector<IObserver*> observers; 
   // InputHandler input;
    GameState* state;

    void
    move( int& count );

    void
    save();

    void
    load();

    int round();
public:
    //Game( Gameboard& player1, Gameboard& player2, ShipManager& manager1, ShipManager& manager2, AbilitiesManager& queue );
    Game();
   ~Game();
    int start();

    void AddObserver(IObserver* observer);
    void RemoveObserver(IObserver* observer);
    void Notify( EventType event );
};