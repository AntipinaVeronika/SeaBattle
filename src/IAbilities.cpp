#include "../headers/IAbilities.h"

DoubleDamage::DoubleDamage( Gameboard& gameboard ): gameboard(gameboard) {};
    
void 
DoubleDamage::activateAbility(){
    MessagePrinter printer;
    gameboard.change_damage_amount();
    printer.double_damage_activated();
}

Scanner::Scanner( Gameboard& gameboard ): gameboard(gameboard){}

void 
Scanner::activateAbility(){
    InputHandler input;
    MessagePrinter printer;
    std::vector < std::vector <Cell>  > board = gameboard.getUsersGameboard();
    int width = gameboard.getWidth();
    int height = gameboard.getHeight();
    do{
        printer.scanner_request();
        input.get_x_y( x, y );
    }while( x > width-1 || y > height - 1 || x < 0 || y < 0 );
    int f = 0;

    if( height - y >= 2 )
        height = y+2;
    if( width - x >= 2 )
        width = x+2;
    for( int j = y; j < height; j++ ){
        for( int i = x; i < width; i++ ){
            if( board.at(j).at(i).state == State::SHIP){
                f = 1;
                break;
            }
        }
    }
    printer.scanner_message( f );
}

Rafale::Rafale( Gameboard& gameboard ): gameboard(gameboard){}

void 
Rafale::activateAbility(){
    MessagePrinter printer;
    std::vector <std::vector <Cell> > opponent_board = gameboard.getUsersGameboard();

    int x = std::rand() % (gameboard.getWidth());
    int y = std::rand() % (gameboard.getHeight());
    while( opponent_board.at(y).at(x).state != State::SHIP ){
        x = std::rand() % (gameboard.getWidth());
        y = std::rand() % (gameboard.getHeight());
    }
    gameboard.hitShip( x, y );
    printer.rafale();
}

// int main(){
//     Gameboard gameboard( 10, 10 );
//     std::vector<int>sizes = {1};
//     std::vector<int>nums = {1};
//     ShipManager manager( nums, sizes );

//     gameboard.addShip( manager.getShipIdx(0), 0, 0, Position::HORIZONTAL );

//     DoubleDamage dd( gameboard );
//     dd.activateAbility();
//     gameboard.hitShip(0,0);
//     std::cout << manager.isOver();

//     return 0;
// }