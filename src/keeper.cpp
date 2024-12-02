#include "../headers/game_state.h"
#include "file_not_found.cpp"
#include "cheating_alert.cpp"

class Keeper{
private:
    int
    getSum(){
        int sum = 0;
        int idx = 15;
        std::ifstream file("seabattle.txt");
        std::string line;
        if( !file.is_open() ){
            throw FileDoesNotExist();
        }
        while( std::getline(file, line) )
        {
            //std::getline(file, line);
            for( char num: line ){
                ++idx;
                if( idx%3 == 0 )
                    sum += (int(num)+2153)*6319;
                else
                    sum += (int(num)*3)-19;
            }
        }
        
        file.close(); 
        return sum;
    }
public:
    void
    save( GameState* state ){
        MessagePrinter say;
        say.save_start();
        std::ofstream out;
        out.open("seabattle.txt");      // открываем файл для записи
        if (out.is_open())
        {
            out << *state;
        }
        out.close(); 
        std::ofstream strict;
        strict.open("check.txt");
        if( strict.is_open()){
            int control_sum = getSum();
            strict << control_sum;
        }else{
            exit(0);
        }
        strict.close();
        say.save_completed();
    }
    void
    load( GameState* state ){
        MessagePrinter say;
        say.loading();
        int current_sum = getSum();
        int correct = 0;
        std::ifstream strict;
        strict.open("check.txt");
        if( strict.is_open() ){
            strict >> correct;
        }
        strict.close();
        if( correct != current_sum ){
            throw CheatingAlert();
        }


        std::ifstream in("seabattle.txt"); // окрываем файл для чтения
        if (in.is_open())
        {
            in >> *state;
        }else{
            throw FileDoesNotExist();
        }
        in.close();
        say.game_loaded();
    }
};