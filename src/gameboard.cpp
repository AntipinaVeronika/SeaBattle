#include "gameboard.h"

int
Gameboard::check_placement(int x, int y, Ship* ship, Position position) {
        //check ships' coordinates;
    for (int i = 0; i < ship->getLength(); ++i) {
        int check_x = position == Position::HORIZONTAL ? x + i : x; 
        int check_y = position == Position::HORIZONTAL ? y : y + i;
        if (check_x < 0 || check_y < 0 || check_x >= width || check_y >= height || p_gameboard[check_y][check_x].state == State::SHIP) {   
            //std::cout << "First\n";
            return 1; // Корабль не может быть размещён
        }
    }
//    check cells around him;
    int x_st = x - 1 >= 0 ? x - 1 : 0;
    int y_st = y - 1 >= 0 ? y - 1 : 0;
    int x_end = position == Position::HORIZONTAL ? x + ship->getLength() : x + 1;
    int y_end = position == Position::HORIZONTAL ? y + 1 : y + ship->getLength();

    if( x_end == width )
        x_end = width - 1;
    if( y_end == height )
        y_end = height - 1;

    for( int i = y_st; i <= y_end; ++i ){
        for( int j = x_st; j <= x_end; j++ ){
            if( p_gameboard[i][j].state == State::SHIP ){
                //std::cout << "Second\n";
                return 1;
            }
        }
    }
    return 0; // Корабль может быть размещён
}

Gameboard::Gameboard(int height, int width):height(height),width(width){
    if( width <= 0 || height <= 0 ){
        throw IncorrectBoardSize();
    }
    p_gameboard.resize(height);
    e_gameboard.resize(height);
    for( int i = 0; i < height; i++ ){
        p_gameboard[i].resize(width);
        e_gameboard[i].resize(width);
        for( int j = 0; j < width; j++ ){
            p_gameboard[i][j].state = State::EMPTY;
            e_gameboard[i][j].state = State::UNKNOWN;
        }
    }
}

Gameboard::Gameboard( const Gameboard& other ): width(other.width), height(other.height), p_gameboard(other.p_gameboard), e_gameboard(other.e_gameboard){}

// Gameboard::Gameboard(const Gameboard& other)
//     : width(other.width), height(other.height) {
//     p_gameboard.resize(height);
//     e_gameboard.resize(height);
    
//     for (int i = 0; i < height; i++) {
//         for (int j = 0; j < width; j++) {
//             p_gameboard[i][j].state = other.p_gameboard[i][j].state;
//             p_gameboard[i][j].seg_idx = other.p_gameboard[i][j].seg_idx;
//             p_gameboard[i][j].ship = other.p_gameboard[i][j].ship;
//             e_gameboard[i][j].state = other.e_gameboard[i][j].state;
//             e_gameboard[i][j].seg_idx = other.e_gameboard[i][j].seg_idx;
//             e_gameboard[i][j].ship = other.e_gameboard[i][j].ship;
//         }
//     }
// }

Gameboard& Gameboard::operator=( const Gameboard& other ){
    if( this != &other ){
        width = other.width;
        height = other.height;
        p_gameboard = other.p_gameboard;
        e_gameboard = other.e_gameboard;
    }
    return *this;
}

Gameboard::Gameboard( Gameboard&& other ): width(other.width), height(other.height), p_gameboard(std::move(other.p_gameboard)), e_gameboard(std::move(other.e_gameboard)){
    other.width = 0;
    other.height = 0;
}

Gameboard& Gameboard::operator= ( Gameboard&& other ){
    if( this != &other ){
        width = other.width;
        other.width = 0;
        height = other.height;
        other.height = 0;
        p_gameboard = std::move(other.p_gameboard);
        e_gameboard = std::move(other.e_gameboard);
    }
    return *this;
}

void
Gameboard::addShip( Ship* black_pearl, int x, int y, Position position ){
    //std::cout << black_pearl->getLength() << '\n';
    if( check_placement(x,y, black_pearl, position) ){
        throw PlacementError();
    }else{
        for( int i = 0; i < black_pearl->getLength(); i++ ){
            if( position == Position::HORIZONTAL ){
                p_gameboard[y][x+i].state = State::SHIP;
                p_gameboard[y][x+i].ship = black_pearl;
                p_gameboard[y][x+i].seg_idx = i;
            }else{
                p_gameboard[y+i][x].state = State::SHIP;
                p_gameboard[y+i][x].ship = black_pearl;
                p_gameboard[y+i][x].seg_idx = i;
            }
        }
    }
}

void
Gameboard::hitShip( int x, int y ){
    if( x < 0 || y < 0 || x>=width || y >=height ){
        throw MissingAim( x, y );
    }
    if (p_gameboard[y][x].state == State::SHIP ){
        p_gameboard[y][x].ship->damage(p_gameboard[y][x].seg_idx, this->damage_amount);
        e_gameboard[y][x].state = State::SHIP;
        e_gameboard[y][x].ship = p_gameboard[y][x].ship;
        e_gameboard[y][x].seg_idx = p_gameboard[y][x].seg_idx;
    }else{
        e_gameboard[y][x].state = State::EMPTY;
    }
}      

// Gameboard::~Gameboard() {
//     for (int i = 0; i < height; i++) {
//         for (int j = 0; j < width; j++) {
//             delete p_gameboard[i][j].ship; // Освобождение памяти для кораблей
//         }
//     }
// }

std::vector < std::vector <Cell> >
Gameboard::getUsersGameboard(){
    return p_gameboard;
}

std::vector < std::vector <Cell> >
Gameboard::getHiddenGameboard(){
    return e_gameboard;
}

int
Gameboard::getHeight(){
    return height;
}

int
Gameboard::getWidth(){
    return width;
}

void
Gameboard::change_damage_amount(){
        if( damage_amount == 1 )
            damage_amount = 2;
        else
            damage_amount = 1;
    }

void
Gameboard::reset_damage(){
    damage_amount = 1;
}
// int main(){
//     Gameboard player1{10,10};
//     Gameboard player2 = player1;

//     Ship black_pearl{5};
//     player1.addShip(&black_pearl, 0, 0, Position(1));
//     player2.printUsersGameboard();
// }