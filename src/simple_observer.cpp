#include "../headers/message_printer.h"
#include "observer.cpp"

class Message: public Observer{
    int* code = nullptr;
    void
    print_msg(){
        MessagePrinter say;
        if( code != nullptr ){
            switch( *code ){
                case 0:
                    say.ability_needed();
                    break;
                case 1:
                    say.ask_coordinates();
                    break;
                case 2:
                    say.load_needed();
                    break;
                case 3:
                    say.congratulations();
                    break;
                case 4:
                    say.dont_be_upset();
                    break;
                case 5:
                    say.crime_and_punishment();
                    break;
                case 6:
                    say.save_needed();
                    break;
                default:
                    say.dont_be_upset();
                    exit(0);
            }
        }
    }
public:
    Message( int* code ):code(code){}
    Message() = default;

    void
    Update(){
        print_msg();
    }
};