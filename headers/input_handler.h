#ifndef INPHAND
#define INPHAND
#include "printer.h"
#include "message_printer.h"
#include "../src/incorrect_ability_answ.cpp"
#include <iostream>

class InputHandler{
    ShipManager manager1;
    ShipManager manager2;
    Gameboard player1;
    Gameboard player2;

    int width = 5;
    int height = 5;
    std::vector<int> nums;

    std::vector<int> 
    create_num_vector();
   
    void 
    gameboard_creation();

    void
    enemy_rise_gb( int height, int width );

    void 
    place_opponent( ShipManager& manager1, ShipManager& manager, std::vector<std::vector<int>>& placement2 );

    void 
    place_ships( ShipManager& manager1, std::vector<std::vector<int>>& placement1 );

public:
    InputHandler();

    void 
    gameboard_initialize( Gameboard& player1, ShipManager& manager1, std::vector<std::vector<int>>& placement1 );

    void
    e_gameboard_initialize( Gameboard& player1, Gameboard& player2, ShipManager& manager1, ShipManager& manager2, std::vector<std::vector<int>>& placement2 );

    void
    enemy_s_manager( ShipManager& manager1, ShipManager& manager2 );

    void 
    manager_initialize( ShipManager& manager1, ShipManager& manager2 );

    void
    get_x_y( int& x, int& y );

    void
    get_answer( int& answer );

};
#endif