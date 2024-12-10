#include <string>
#include <iostream>
#include <fstream>
#include "incorrect_command.cpp"

class ConsoleProcessor{
    std::fstream man;

    int
    auto_regime( char c ){
        switch( c ){
            case 'a':
                return 0;
            case 's':
                return 1;
            case 'l':
                return 2;
            case 'c':
                return 3;
            default:
                return -1;
        }
    }

public:
    ConsoleProcessor(){
        man.open("command_list.txt");
    }
    ~ConsoleProcessor(){
        man.close();
    }
    int
    getCommand(){
        std::string command;
        std::string buffer;
        std::cin >> command;

        if( man.is_open( ) ){
            while( getline( man, buffer )){
                getline( man, buffer, ' ' );
                if( buffer == command ){
                    getline( man, buffer, '\n' );
                    return std::stoi(buffer);
                }
            }
        }
        int res = auto_regime( command[0] );
        if( res == -1 ){
            throw IncorrectCommand( command );
        }
        return res;
    }

};