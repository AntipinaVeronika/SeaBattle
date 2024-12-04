// #include "../headers/game_state.h"
#include "secret_agent.cpp"

// class Keeper{
// private:
//     std::fstream file;
//     std::fstream strict;
//     GameState* state;
// public:
//     Keeper( GameState* state ):state(state){
//         file.open("seabattle.txt");
//         if( !file.is_open() ){
//             throw FileDoesNotExist();
//         }

//         strict.open("check.txt");
//         if( !strict.is_open() )
//             throw CheatingAlert();
//     }
//     ~Keeper(){
//         file.close();
//         strict.close();
//     }
//     void
//     save( ){
//         MessagePrinter say;
//         say.save_start();

//         if (file.is_open())
//         {
//             file << *state;
//         }

//         say.save_completed();
//     }
//     void
//     load( ){
//         MessagePrinter say;
//         say.loading();

//         if (file.is_open())
//         {
//             file >> *state;
//         }else{
//             throw FileDoesNotExist();
//         }

//         say.game_loaded();
//     }
// };
#include <fstream>
#include "../headers/game_state.h"

class SaveKeeper {
private:
    std::ofstream file;
public:
    SaveKeeper(GameState* state) {
        file.open("seabattle.txt", std::ios::out | std::ios::trunc);
        if (!file.is_open()) {
            throw FileDoesNotExist();
        }
        file << *state;
        file.close();
    }
};

class LoadKeeper {
private:
    std::ifstream file;
public:
    LoadKeeper(GameState* state) {
        file.open("seabattle.txt");
        if (!file.is_open()) {
            throw FileDoesNotExist();
        }
        file >> *state;
        file.close();
    }
};