#ifndef MANAGER
#define MANAGER
#include "ship.h"
#include "../src/s_manager_errors.cpp"

class ShipManager{
    int ships_count;
    std::vector <Ship> ships;
public:
    ShipManager();
    ShipManager( const std::vector<int>& nums, const std::vector<int>& sizes );
    //конструктор копирования, перемщения
    ShipManager( const ShipManager& other );

    ShipManager& operator=(const ShipManager& other);

    ShipManager(ShipManager&& other);

    ShipManager& operator = ( ShipManager&& other );

    Ship*
    getShipIdx( int idx );

    int
    getCapacity();

    int
    areLeft();

    bool
    isOver();
};
#endif

    // void
    // spoiler(){
    //     Ship another = Ship{5};
    //     ships.at(0) = another;
    // }
// int main(){
//     int arr1[] = {4,3,2,1};
//     int arr2[] = {1,2,3,4};
//     ShipManager manager1{arr1,arr2};
//     ShipManager manager2 = manager1;
//     manager1.printManager();
//     manager2.spoiler();
//     manager1.printManager();
// }