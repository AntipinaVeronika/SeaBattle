#include "../headers/game_state.h"
#include "secret_agent.cpp"

class Keeper{
private:
    std::fstream file;
    std::fstream strict;
public:
    Keeper(){
        file.open("seabattle.txt");
        if( !file.is_open() ){
            throw FileDoesNotExist();
        }

        strict.open("check.txt");
        if( !strict.is_open() )
            throw CheatingAlert();
    }
    ~Keeper(){
        file.close();
        strict.close();
    }
    void
    save( GameState* state ){
        MessagePrinter say;
        say.save_start();

        if (file.is_open())
        {
            file << *state;
        }

        SecretAgent agent_007;
        if( strict.is_open()){
            int control_sum = agent_007.getSum();
            strict << control_sum;
        }else{
            exit(0);
        }

        say.save_completed();
    }
    void
    load( GameState* state ){
        MessagePrinter say;
        say.loading();

        SecretAgent agent_007;
        int current_sum = agent_007.getSum();
        int correct = 0;
        std::ifstream strict;

        if( strict.is_open() ){
            strict >> correct;
        }

        if( correct != current_sum ){
            throw CheatingAlert();
        }

        if (file.is_open())
        {
            file >> *state;
        }else{
            throw FileDoesNotExist();
        }

        say.game_loaded();
    }
};