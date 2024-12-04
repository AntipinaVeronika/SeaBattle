#include "../headers/game_state.h"
#include "file_not_found.cpp"
#include "cheating_alert.cpp"

class SecretAgent{
private:
    std::fstream file;

public:
    SecretAgent(){
        file.open("seabattle.txt");
        if( !file.is_open() )
            throw FileDoesNotExist();
    }
    ~SecretAgent(){
        file.close();
    }
    int
    getSum(){
        int sum = 0;
        int idx = 15;

        std::string line;

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

        return sum;
    }
};