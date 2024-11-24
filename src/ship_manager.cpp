#include "../headers/ship_manager.h"

ShipManager::ShipManager() = default;

ShipManager::ShipManager(const std::vector<int>& nums, const std::vector<int>& sizes): ships_count(0) {
    if( nums.size() != sizes.size() ){
         throw LengthDiscrepancy( nums.size(), sizes.size() );
    }
    for( int num : nums ){
        if( num < 0 ){
            throw SizeOfNumberUnderZero( num );
        }
        ships_count += num;
    }
        
    ships.resize(ships_count);

    int s_idx = 0;
    for( int i = 0; i < nums.size(); i++ ){
        for( int j = 0; j < nums[i]; j++ ){
            try{
                ships.at(s_idx++) = Ship(sizes[i]);
            }
            catch( IncorrectShipSize e ){
                std::cerr << "Failed to create a ship." << e.what() << '\n';
            }
        }
    }
}

    //конструктор копирования, перемщения
ShipManager::ShipManager( const ShipManager& other ): ships_count(other.ships_count), ships(other.ships){}

ShipManager& ShipManager::operator=(const ShipManager& other){
    if( this != &other ){
        ships_count = other.ships_count;
        ships = other.ships;
    }
    return *this;
}

ShipManager::ShipManager(ShipManager&& other): ships_count(other.ships_count), ships(std::move(other.ships)) {
    other.ships_count = 0;
}

ShipManager& ShipManager::operator = ( ShipManager&& other ){
    if( this != &other ){
        ships_count = other.ships_count;
        ships = std::move( other.ships );
        other.ships_count = 0;
    }
    return *this;
}

Ship*
ShipManager::getShipIdx( int idx ) {
    return &(ships.at(idx));
}

int
ShipManager::getCapacity(){
    return ships_count;
}

int
ShipManager::areLeft(){
    int count = 0;
    for( int i = 0; i < ships_count; i++ ){
        if( ships.at(i).isDestroyed() == false)
            ++count;
    }
    return count;
}

bool
ShipManager::isOver(){
    for( int i = 0; i < ships_count; i++ ){
        if( ships.at(i).isDestroyed() == false)
            return false;
    }
    return true;
}

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