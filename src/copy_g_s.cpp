#include "../headers/game_state.h"

GameState::GameState( Gameboard* player1, Gameboard* player2, ShipManager* manager1, ShipManager* manager2, AbilitiesManager* queue, std::vector<std::vector<int>>& placement1, std::vector<std::vector<int>>& placement2 ):
    player1(player1),player2(player2),manager1(manager1),manager2(manager2),queue(queue), placement1(placement1), placement2(placement2){

    }

std::ostream& operator<<( std::ostream& out, const GameState& state ){
    //ShipManager1&2
    out << std::to_string(state.manager1->getCapacity()) + '\n';
    std::string nums = "";
    std::string sizes = "";
    Ship* ship1 = state.manager1->getShipIdx(0);
    int length = ship1->getLength();
    int count = 0;

    for( int i = 0; i < state.manager1->getCapacity(); ++i ){
            ship1 = state.manager1->getShipIdx(i);

            if( length != ship1->getLength() ){
                nums += std::to_string(count) + ' ';
                count = 0;
                sizes += std::to_string(length) + ' ';
                length = ship1->getLength();
            }
            length = ship1->getLength();
            count++;
    }
    nums += std::to_string(count) + ' ';
    length = ship1->getLength();
    sizes += std::to_string(length) + ' ';
    out << nums + '\n';
    out << sizes + '\n';

    for( int i = 0; i < state.manager1->getCapacity(); ++i ){
        Ship* ship1 = state.manager1->getShipIdx(i);
        out << std::to_string(ship1->getLength()) << '\n';
        for( int j = 0; j < ship1->getLength(); ++j ){
            out << std::to_string(int(ship1->getSegment( j )));
        }
        out << ' ';
        Ship* ship2 = state.manager2->getShipIdx(i);
        for( int j = 0; j < ship2->getLength(); ++j ){
            out << std::to_string(int(ship2->getSegment( j )));
        }
        out << '\n';
    }
    //Gameboard1
    out << std::to_string(state.player1->getWidth()) + ' ' + std::to_string(state.player1->getHeight()) + '\n';
    for( int i = 0; i < state.placement1.size(); ++i ){
        out << std::to_string(state.placement1.at(i).at(0)) + ' ' +std::to_string(state.placement1.at(i).at(1)) + ' ' + std::to_string(state.placement1.at(i).at(2)) + '\n'; 
    }
    //Gameboard2
    for( int i = 0; i < state.placement2.size(); ++i ){
        out << std::to_string(state.placement2.at(i).at(0)) + ' ' + std::to_string(state.placement2.at(i).at(1)) + ' ' + std::to_string(state.placement2.at(i).at(2)) + '\n'; 
    }
    //AbilityManager
    out << state.queue->getCoded() + '\n';
    return out;
}
std::istream& operator>>( std::istream& in, GameState& state ){
    //ShipManager1&2
    std::string unsplitted;
    std::getline(in, unsplitted);
    int capacity = std::stoi(unsplitted);
    
    std::vector<int> nums;
    std::vector<int> sizes;
 
    std::getline(in, unsplitted);  
    std::istringstream f(unsplitted);
    while( getline( f, unsplitted, ' ' ) ){
        nums.push_back(std::stoi(unsplitted));
    }
    std::getline(in, unsplitted);    
    std::istringstream g(unsplitted);
    while( getline( g, unsplitted, ' ' ) ){
        sizes.push_back(std::stoi(unsplitted));
    }

    state.manager1 = new ShipManager( nums, sizes );
    state.manager2 = new ShipManager( nums, sizes );

    int n;
    std::string users;
    std::string robo;
    std::vector<std::string> un = {"",""};
    for( int i = 0; i < capacity; ++i ){
        un.erase( un.begin(), un.end() );
        std::getline(in, unsplitted);//n  
        n = std::stoi(unsplitted);

        std::getline(in, unsplitted);
        std::cout << unsplitted << '\n';
        std::istringstream a(unsplitted);
        while( getline( a, unsplitted, ' ' ) ){
            un.push_back(unsplitted);
        }
        users = un[0];
        robo = un[1];

        for( int j = 0; j < n; ++j ){
            if( users[j] != '0' ){
                if( users[j] == '1' )
                    state.manager1->getShipIdx(i)->damage( j, 1 );
                else
                    state.manager1->getShipIdx(i)->damage( j, 2 );
            }
            if( robo[j] != '0' ){
                if( robo[j] == '1' )
                    state.manager2->getShipIdx(i)->damage( j, 1 );
                else
                    state.manager2->getShipIdx(i)->damage( j, 2 );
            }
        }
    }
    //Gameboard1&2
    int width = 5;
    int height = 5;
    std::vector<int> nu;
    std::getline(in, unsplitted);

    std::istringstream e(unsplitted);
    while( getline( e, unsplitted, ' ' ) ){
        nu.push_back(std::stoi(unsplitted));
    }
    if( nu.size() ){
        width = nu[0];
        height = nu[1];
    }else{
        throw IncorrectBoardSize();
    }

    state.player1 = new Gameboard( height, width );
    state.player2 = new Gameboard( height, width );

    for( int i = 0; i < capacity; i++ ){
        int x, y, pos;
        std::vector<int> u;
        // in >> x >> y >> pos;
        std::getline(in, unsplitted);  
        std::istringstream h(unsplitted);
        while( getline( h, unsplitted, ' ' ) ){
            u.push_back(std::stoi(unsplitted));
        }
        if( u.size() >= 3 ){
            x = u[0];
            y = u[1];
            pos = u[2];
        }
        state.player1->addShip( state.manager1->getShipIdx(i), x, y, Position(pos) ); 
    }
        for( int i = 0; i < capacity; i++ ){
        int x, y, pos;
        std::vector<int> u;
        // in >> x >> y >> pos;
        std::getline(in, unsplitted);  
        std::istringstream h(unsplitted);
        while( getline( h, unsplitted, ' ' ) ){
            u.push_back(std::stoi(unsplitted));
        }
        if( u.size() >= 3 ){
            x = u[0];
            y = u[1];
            pos = u[2];
        }

        state.player2->addShip( state.manager2->getShipIdx(i), x, y, Position(pos) );
    }
    //Abilities
    std::string secret_coded_queue;
    AbilitiesManager q = AbilitiesManager();
    *(state.queue) = q;
    std::getline(in, secret_coded_queue); 
    for( int i = 0; i < secret_coded_queue.size(); ++i ){
        state.queue->addAbility( *(state.player2), secret_coded_queue[i] );
    }


    return in;
}    
    
void
GameState::save(){
    MessagePrinter say;
    say.save_start();
    std::ofstream out;
    out.open("seabattle.txt");      // открываем файл для записи
    if (out.is_open())
    {
        std::cout << "Not here\n";
        out << *this;
    }
    out.close(); 
    say.save_completed();
}

void
GameState::load(){
    MessagePrinter say;
    say.loading();
    std::ifstream in("seabattle.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        in >> *this;
    }
    in.close();
    say.game_loaded();
}