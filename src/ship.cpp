#include "ship.h"

Ship::Ship() = default;
Ship::Ship(int length, Position position): length(length), position(position){
    if( length < 1 || length >4 )
        throw IncorrectShipSize( length );
        
    std::vector <Segment> new_ship(length, INTACT);
    ship = std::move(new_ship);
}
Ship::Ship( const Ship& other ): length(other.length), position(other.position), ship(other.ship){}
Ship& Ship::operator=(const Ship& other){
    if( this != &other ){
        length = other.length;
        ship = other.ship;
    }
    return *this;
}

Ship::Ship(Ship&& other): length(other.length), position(other.position), ship(std::move(other.ship)) {
    other.length = 0;
}

Ship& Ship::operator = ( Ship&& other ){
    if( this != &other ){
        length = other.length;
        ship = std::move( other.ship );
        other.length = 0;
    }
    return *this;
}


void 
Ship::changePosition(){
    if( position == Position::HORIZONTAL )
        position = Position::VERTICAL;
    else
        position = Position::HORIZONTAL;
}

int 
Ship::getLength(){
    return length;
}

Position
Ship::getPosition(){
    return position;
}

void
Ship::damage( int idx, int damage_amount ){
    int state = int(ship.at(idx)) + damage_amount;
    if( state == 1 )
        ship.at(idx) = Segment::DAMAGED;
    else if ( state >= 2 )
        ship.at(idx) = Segment::DESTROYED;
    else
        ship.at(idx) = Segment::INTACT;
}

bool
Ship::isDestroyed(){
    for( int i = 0; i < length; i++ ){
        if( ship.at(i) != Segment::DESTROYED )
            return false;
    }
    return true;
}

Segment
Ship::getSegment( int idx ){
    return ship.at(idx);
}