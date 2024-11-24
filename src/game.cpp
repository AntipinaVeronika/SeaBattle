#include "../headers/game.h"

int
Game::round(){
    Printer printer;
    //InputHandler input;
    int x = 0;
    int y = 0;
    int count = manager2.areLeft();

    int answer = 0;
    while( manager1.isOver() != 1 && manager2.isOver() != 1){
        say.ability_needed();
        try{
            input.get_answer( answer );
        }
        catch( IncorrectAbilityAnswer& e ){
            std::cout << e.what();
            say.crime_and_punishment();
            answer = 0;
        }


        if( answer ){
            try{
                queue.useAbility();
            }
            catch( EmptyQueue& e ){
                std::cout << e.what();
            }
        }

        say.ask_coordinates();
        bool flag = false;
        do{
            try{
                input.get_x_y( x, y );
                player2.hitShip( x, y );
                std::cout << "COUNT: " << count << "ARENOW: " << manager2.areLeft() << '\n';
                flag = true;
            }catch(MissingAim& e){
                std::cout << e.what();
                flag = false;
            }
        }while( flag == false );
        player2.reset_damage();
        if( manager2.areLeft() != count ){
            queue.addAbility( player2 );
            count = manager2.areLeft();
        }

        flag = false;
        time_t timer;
        std::srand(time(&timer));
        do{
            try{
                x = std::rand() % (player1.getWidth());
                y = std::rand() % (player1.getHeight());
                player1.hitShip( x, y );
                flag = true;
            }catch(MissingAim& e){
                flag = false;
            }
        }while( flag == false );

        std::vector < std::vector <Cell> > users_gameboard_1 = player1.getUsersGameboard();
        printer.printUsersGameboard( users_gameboard_1, player1.getWidth(), player1.getHeight() );

        std::vector < std::vector <Cell> > hidden_gameboard_2 = player2.getHiddenGameboard();
        printer.printHiddenGameboard( hidden_gameboard_2, player2.getWidth(), player2.getHeight() );

    }
    if( manager2.isOver() == 1 )
        return 1;
    else
        return 0;
}

// Game::Game( Gameboard& player1, Gameboard& player2, ShipManager& manager1, ShipManager& manager2, AbilitiesManager& queue ):
//         player1(player1),player2(player2),
//         manager1(manager1),manager2(manager2), queue(queue){}

Game::Game(){
    //InputHandler input;
    say.greeting();
    input.manager_initialize( manager1, manager2 );
    input.gameboard_initialize( player1, player2, manager1, manager2 );
    AbilitiesManager queue( player2 );
    this->queue = queue;
}

int 
Game::start(){
    int round_res = 1;
    while( round_res = 1 ){
        round_res = round();
        say.congratulations();
        return 0;
    }
    say.dont_be_upset();
    return 0;
}