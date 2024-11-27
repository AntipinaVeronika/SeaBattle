#include "../headers/IAbilities.h"

DoubleDamage::DoubleDamage( Gameboard& gameboard ): gameboard(gameboard) {};
DoubleDamage::DoubleDamage(const DoubleDamage& other)
    : gameboard(other.gameboard) {}
    
void 
DoubleDamage::activateAbility(){
    MessagePrinter printer;
    gameboard.change_damage_amount();
    printer.double_damage_activated();
}

IAbility*
DoubleDamage::clone(){
    return new DoubleDamage(*this);
}

char
DoubleDamage::secretCode(){
    return '0';
}

Scanner::Scanner( Gameboard& gameboard ): gameboard(gameboard){}
Scanner::Scanner(const Scanner& other)
    : gameboard(other.gameboard) {}

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

char
Scanner::secretCode(){
    return '1';
}

IAbility*
Scanner::clone(){
    return new Scanner(*this);
}

Rafale::Rafale( Gameboard& gameboard ): gameboard(gameboard){}
Rafale::Rafale(const Rafale& other)
    : gameboard(other.gameboard) {}

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

char
Rafale::secretCode(){
    return '2';
}

IAbility*
Rafale::clone(){
    return new Rafale(*this);
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