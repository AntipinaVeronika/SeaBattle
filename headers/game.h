#include "time.h"
#include "ability_manager.h"
#include "ship_manager.h"
#include "game_state.h"

class Game{
    // Gameboard player1;
    // Gameboard player2;
    // std::vector<std::vector<int>> placement1;
    // std::vector<std::vector<int>> placement2;
    // ShipManager manager1;
    // ShipManager manager2;
    // AbilitiesManager* queue;
    MessagePrinter say;
    InputHandler input;
    GameState* state;

    void
    move( int& count );

    int round();
public:
    //Game( Gameboard& player1, Gameboard& player2, ShipManager& manager1, ShipManager& manager2, AbilitiesManager& queue );
    Game();
   ~Game();
    int start();
};