#include "time.h"
#include "ability_manager.h"
#include "ship_manager.h"

class Game{
    Gameboard player1;
    Gameboard player2;
    ShipManager manager1;
    ShipManager manager2;
    AbilitiesManager queue;
    MessagePrinter say;
    InputHandler input;

    int round();
public:
    //Game( Gameboard& player1, Gameboard& player2, ShipManager& manager1, ShipManager& manager2, AbilitiesManager& queue );
    Game();
    int start();
};