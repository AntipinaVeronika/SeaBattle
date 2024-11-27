#include "../headers/game_state.h"
#include "../headers/game.h"
//think about it!
void
Game::move( int& count ){
    int x,y = 0;
    int answer = 0;

    std::cout << "Do you want to save the game?\n";
    std::cin >> answer;
    if( answer ){
        state->save();
        state->load();
    }

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
            state->queue->useAbility();
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
            state->player2->hitShip( x, y );
            std::cout << "COUNT: " << count << "ARENOW: " << state->manager2->areLeft() << '\n';
            flag = true;
        }catch(MissingAim& e){
            std::cout << e.what();
            flag = false;
        }
    }while( flag == false );
    state->player2->reset_damage();
    if( state->manager2->areLeft() != count ){
        state->queue->addAbility( *(state->player2) );
        count = state->manager2->areLeft();
    }
}

int
Game::round(){
    Printer printer;
    //InputHandler input;
    int x = 0;
    int y = 0;
    int count = state->manager2->areLeft();

    while( state->manager1->isOver() != 1 && state->manager2->isOver() != 1){
        move( count );

        int flag = false;
        time_t timer;
        std::srand(time(&timer));
        do{
            try{
                x = std::rand() % (state->player1->getWidth());
                y = std::rand() % (state->player1->getHeight());
                state->player1->hitShip( x, y );
                flag = true;
            }catch(MissingAim& e){
                flag = false;
            }
        }while( flag == false );

        std::vector < std::vector <Cell> > users_gameboard_1 = state->player1->getUsersGameboard();
        printer.printUsersGameboard( users_gameboard_1, state->player1->getWidth(), state->player1->getHeight() );

        std::vector < std::vector <Cell> > hidden_gameboard_2 = state->player2->getHiddenGameboard();
        printer.printHiddenGameboard( hidden_gameboard_2, state->player2->getWidth(), state->player2->getHeight() );

    }

    if( state->manager2->isOver() == 1 ){
        std::cout << state->manager2->getShipIdx(0)->isDestroyed() << '\n';
        return 1;
    }
    return 0;
}

// Game::Game( Gameboard& player1, Gameboard& player2, ShipManager& manager1, ShipManager& manager2, AbilitiesManager& queue ):
//         player1(player1),player2(player2),
//         manager1(manager1),manager2(manager2), queue(queue){}

Game::Game(){
    InputHandler input;
    say.greeting();
    input.manager_initialize( manager1, manager2 );
    input.gameboard_initialize( player1, manager1, placement1 );
    input.e_gameboard_initialize( player1, player2, manager1, manager2, placement2 );
    AbilitiesManager* queue = new AbilitiesManager( player2 );
    this->queue = queue;
    this->state = new GameState( &player1, &player2, &manager1, &manager2, queue, placement1, placement2 );
   // this->state = GameState();
}

Game::~Game(){
    delete queue;
    delete state;
}

int 
Game::start(){
    int round_res = 1;
    while( round_res ){
        round_res = round();
        if( round_res ){
            say.congratulations();
            input.enemy_s_manager( manager1, *(state->manager2) );
            input.e_gameboard_initialize( player1, *(state->player2), manager1, *(state->manager2), placement2 );
        }
        else{
            say.dont_be_upset();
            break;
        }
    }
    return 1;
}