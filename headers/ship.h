#ifndef SHIP_H
#define SHIP_H
#include <vector>
#include <iostream>
#include <utility>
#include "ship_errors.cpp"

enum Segment{
    INTACT,
    DAMAGED,
    DESTROYED,
};

enum Position{
    VERTICAL,
    HORIZONTAL,
};

class Ship{
    int length;
    Position position;
    std::vector <Segment> ship;

public:
    Ship();
    Ship(int length, Position position = Position::HORIZONTAL);
    Ship( const Ship& other );
    Ship& operator=(const Ship& other);
    Ship(Ship&& other);
    Ship& operator = ( Ship&& other );

    void 
    changePosition();

    int 
    getLength();

    Position
    getPosition();

    void
    damage( int idx, int damage_amount );

    bool
    isDestroyed();

    Segment
    getSegment( int idx );
};
#endif