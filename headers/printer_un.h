#include "../src/observer.cpp"
#include "../headers/game_state.h"
#include <iostream>
class PrinterConsole : public IObserver {
    GameState* state;

    void
    printUsersGameboard(std::vector < std::vector <Cell> > p_gameboard, int width, int height );

    void
    printHiddenGameboard( std::vector < std:: vector <Cell> > e_gameboard, int width, int height );

    void
    congratulations();
        
    void
    dont_be_upset();

    void
    ask_coordinates();

    void
    ability_needed();

    void
    greeting();

    void
    crime_and_punishment();

    void
    save_start();

    void
    save_completed();

    void
    loading();

    void
    game_loaded();

    void
    load_needed();

    void
    save_needed();

    void
    print_boards();


public:
    PrinterConsole( GameState* state );
    void Update(const GameEvent& event);
};