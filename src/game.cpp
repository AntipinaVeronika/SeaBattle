#include "../headers/game_state.h"
#include "../headers/game.h"
// #include "file_not_found.cpp"
// #include "cheating_alert.cpp"
#include "save_load.cpp"
//think about it!
void
Game::move( int& count ){
    int x,y = 0;
    int answer = 0;

    Notify( EventType::Save );
    state->input.get_answer( answer );
    if( answer ){
        try{
            save();
        }catch( FileDoesNotExist& e ){
            std::cout << e.what();
        }catch( CheatingAlert& e ){
            std::cout << e.what();
        }
    }

    Notify( EventType::Load );
    state->input.get_answer( answer );
    if( answer ){
        try{
            load();
        }catch( FileDoesNotExist& e ){
            std::cout << e.what();
        }catch( CheatingAlert& e ){
            std::cout << e.what();
        }
    }

    Notify( EventType::Ab );
    try{
        state->input.get_answer( answer );
    }
    catch( IncorrectAbilityAnswer& e ){
        std::cout << e.what();
        Notify( EventType::Crime );
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

    Notify( EventType::Input );
    bool flag = false;
    do{
        try{
            state->input.get_x_y( x, y );
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

void
Game::save(){
    Save save;
    save.save(this->state);
    //state->save();
}

void
Game::load(){
    Load load;
    load.load(this->state);
   // state->load();
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
        // std::cout << state->manager2->getShipIdx(0)->isDestroyed() << '\n';
        return 1;
    }
    return 0;
}

// Game::Game( Gameboard& player1, Gameboard& player2, ShipManager& manager1, ShipManager& manager2, AbilitiesManager& queue ):
//         player1(player1),player2(player2),
//         manager1(manager1),manager2(manager2), queue(queue){}

Game::Game(){
    this->state = new GameState();

    AddObserver( new PrinterConsole() );
   // message_observer = new Message( &code );
}

Game::~Game(){
    //delete queue;
    delete this->state;
    while (!observers.empty()) {
        delete observers.back();
        observers.pop_back();
    }
    //delete message_observer;
}

int 
Game::start(){
    int round_res = 1;
    while( round_res ){
        round_res = round();
        if( round_res ){
            Notify( EventType::Win );
            (state->input).enemy_s_manager( *(state->manager1), *(state->manager2) );
            (state->input).e_gameboard_initialize( *(state->player1), *(state->player2), *(state->manager1), *(state->manager2), state->placement2 );
        }
        else{
            Notify( EventType::Loss );
            break;
        }
    }
    return 1;
}
void 
Game::AddObserver( IObserver* observer ) {
    observers.push_back(observer);
}
       
void 
Game::RemoveObserver( IObserver* observer ) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}
void
Game::Notify( EventType type) {
    GameEvent event(type);
    for (auto observer : observers) {
        observer->Update(event);
    }
}