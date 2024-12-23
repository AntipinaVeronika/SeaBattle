#include "secret_agent.cpp"
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
    }
    ~SaveKeeper(){
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
    }
    ~LoadKeeper(){
        file.close();
    }
};

class Load{
private:
    std::ifstream strict;
    void
    prepare(){
        SecretAgent agent_007;
        if( strict.is_open()){
            int control_sum = agent_007.getSum();
            int current_sum = 0;
            strict >> current_sum;
            if( current_sum != control_sum ){
                throw CheatingAlert();
            }
        }else{
            throw CheatingAlert();
        }
    }
public:
    Load(){
        strict.open("check.txt");
        if( !strict.is_open() )
            throw FileDoesNotExist();
    }
    ~Load(){
        strict.close();
    }
    void
    load( GameState* state ){
        try{
            prepare();
        }
        catch( CheatingAlert& e ){
            std::cout << e.what();
            exit(0);
        }
        LoadKeeper keep = LoadKeeper(state);
    }
};

class Save{
private:
    std::ofstream strict;

    void
    insecure_save( GameState* state ){
        SaveKeeper keep = SaveKeeper(state);
    }

public:
    Save(){
        strict.open("check.txt");
    }
    ~Save(){
        strict.close();
    }
    void
    save( GameState* state ){
        insecure_save( state );

        SecretAgent agent_007;
        if( strict.is_open()){
            int control_sum = agent_007.getSum();
            strict << control_sum;
        }else{
            exit(0);
        }
    }
};
