#ifndef STATE
#define STATE
#include "gameboard.h"
#include "ship_manager.h"
#include "ability_manager.h"
#include <sstream>
#include <fstream>

class GameState{
private:
    Gameboard* player1;
    Gameboard* player2;
    ShipManager* manager1;
    ShipManager* manager2;
    AbilitiesManager* queue;
    InputHandler input;
    std::vector<std::vector<int>> placement1;
    std::vector<std::vector<int>> placement2;
    friend class Game;
public:
    //GameState() = default;
    GameState();
    //GameState( Gameboard* player1, Gameboard* player2, ShipManager* manager1, ShipManager* manager2, AbilitiesManager* queue, std::vector<std::vector<int>>& placement1, std::vector<std::vector<int>>& placement2 );
    ~GameState();

    friend std::ostream& operator<<( std::ostream& out, const GameState& state );
    friend std::istream& operator>>( std::istream& in, GameState& state );    

    std::vector<std::vector<Cell>>
    getUser();

    std::vector<std::vector<Cell>>
    getHidden();

    int
    getWidth();

    int
    getHeight();
    // int
    // getSum();

    // void
    // save();

    // void
    // load();
};
#endif