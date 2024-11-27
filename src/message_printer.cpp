#include "../headers/message_printer.h"

MessagePrinter::MessagePrinter() = default;


void
MessagePrinter::double_damage_activated(){
    std::cout << "Double damage is activated! Don't miss!\n";
}
    
void
MessagePrinter::scanner_message( bool is ){
    if( is ){
        std::cout << "Ship is here!\n";
    }
    else{
        std::cout << "There is no ship!\n";
    }
}

void
MessagePrinter::scanner_request(){
    std::cout << "Which area do you want to scan?\n";
}

void
MessagePrinter::rafale(){
    std::cout << "Ready, aim, fire!\n";
}
    
void
MessagePrinter::congratulations(){
    std::cout << "Congratulations! Now let's continue that adventure! Next round!\n";
}
    
void
MessagePrinter::dont_be_upset(){
    std::cout << "Errr.... Better luck next time?\n";
}

void
MessagePrinter::ask_coordinates(){
    std::cout << "Where do you want to hit?\n";
}

void
MessagePrinter::ability_needed(){
    std::cout << "Do you want to use ability? 1/0\n";
}

void
MessagePrinter::ask_placement(){
    std::cout << "Enter abscisse, ordinate and position (0 - for vertical, 1 - for horizontal)\n";
}

void
MessagePrinter::what_length( int num ){
    std::cout << "Place ship of length " << num << '\n';
}

void
MessagePrinter::ask_gameboard_sizes(){
    std::cout << "Enter gameboard width and height\n";
}

void
MessagePrinter::greeting(){
    std::cout << "Hola chico nuevo!\n";
    std::cout << "Or do we have a sea wolf here?\n";
    std::cout << "Perhaps it's time to find out!\n";
    std::cout << "Time to scrub the deck, tie some sailor knots, and catch a fair wind!\n";
    std::cout << "Good luck, sailor!\n";
    std::cout << "------------------------------------------------------------------------\n\n";
}

void
MessagePrinter::crime_and_punishment(){
    std::cout << "But still - no ability is being activated now\n";
}

void
MessagePrinter::save_start(){
    std::cout << "Saving in process!\n";
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << ".\n";
}

void
MessagePrinter::save_completed(){
    std::cout << "Saved!\n";
}

void
MessagePrinter::loading(){
    std::cout << "Loading...\n";
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << '.';
    std::cout << ".\n";
}

void
MessagePrinter::game_loaded(){
    std::cout << "Load is done!\n";
}