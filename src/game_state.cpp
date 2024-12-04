//#include "../headers/game_state.h"
#include "save_load.cpp"
// #include "file_not_found.cpp"
// #include "cheating_alert.cpp"
// // GameState::GameState( Gameboard* player1, Gameboard* player2, ShipManager* manager1, ShipManager* manager2, AbilitiesManager* queue, std::vector<std::vector<int>>& placement1, std::vector<std::vector<int>>& placement2 ):
//     player1(player1),player2(player2),manager1(manager1),manager2(manager2),queue(queue), placement1(placement1), placement2(placement2){

//     }

GameState::GameState(){
    MessagePrinter say;
    this->manager1 = new ShipManager();
    this->manager2 = new ShipManager();
    this->player1 = new Gameboard();
    this->player2 = new Gameboard();
    this->queue = new AbilitiesManager();
    say.greeting();
    say.load_needed();

    int answer = 0;
    input.get_answer( answer );

    SaveLoad saveload;
    if( answer ){
        try{
           saveload.load(this);
            //load();
        }catch( FileDoesNotExist& e ){
            std::cout << e.what();
            exit(0);
        }catch( CheatingAlert& e ){
            std::cout << e.what();
            exit(0);
        }
    }else{
        (this->input).manager_initialize( *(manager1), *(manager2) );
        input.gameboard_initialize( *(player1), *(manager1), placement1 );
        input.e_gameboard_initialize( *(player1), *(player2), *(manager1), *(manager2), placement2 );
        AbilitiesManager* queue = new AbilitiesManager( *(player2) );
        delete this->queue;
        this->queue = queue;
    }
}

GameState::~GameState(){
    delete this->manager1;
    delete this->manager2;
    delete this->player1;
    delete this->player2;
    delete this->queue;
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

    std::vector<std::vector<int>> empties;
    int vec_i = 0;
    std::vector<std::vector<Cell>> hidden = state.player2->getHiddenGameboard();
    for( int j = 0; j < state.player2->getHeight(); ++j ){
        for( int i = 0; i < state.player2->getWidth(); ++i ){
            if( hidden.at(j).at(i).state == State::EMPTY ){
                empties.resize(vec_i + 1);
                empties.at(vec_i).resize(2);
                empties.at(vec_i++) = { i, j };
            }
        }
    }
    out << std::to_string(vec_i) + '\n';
    for( int v = 0; v < vec_i; ++v ){
        out << std::to_string( empties.at(v).at(0) ) + ' ' + std::to_string( empties.at(v).at(1) ) << '\n';
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

    delete state.manager1;
    delete state.manager2;

    state.manager1 = new ShipManager( nums, sizes );
    state.manager2 = new ShipManager( nums, sizes );

    int n;
    std::string users;
    std::string robo;
    std::vector<std::string> un = {"",""};
    std::vector<std::vector<int>> indexes_to_hit;
    std::vector<std::vector<int>> indexes_to_hit_me;
    indexes_to_hit.resize(capacity);
    indexes_to_hit_me.resize(capacity);

    for( int i = 0; i < capacity; ++i ){
        un.erase( un.begin(), un.end() );
        std::getline(in, unsplitted);//n  
        n = std::stoi(unsplitted);

        std::getline(in, unsplitted);
        std::istringstream a(unsplitted);
        while( getline( a, unsplitted, ' ' ) ){
            un.push_back(unsplitted);
        }
        users = un[0];
        robo = un[1];

        for( int j = 0; j < n; ++j ){
            if( users[j] != '0' ){
                if( users[j] == '2' )
                    state.manager1->getShipIdx(i)->damage( j, 1 );
                indexes_to_hit_me.at(i).push_back(j);
            }
            if( robo[j] != '0' ){
                if( robo[j] == '2' )
                    state.manager2->getShipIdx(i)->damage( j, 1 );
                indexes_to_hit.at(i).push_back(j);
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

    delete state.player1;
    delete state.player2;

    state.player1 = new Gameboard( height, width );
    state.player2 = new Gameboard( height, width );

    state.placement1.erase(state.placement1.begin(),state.placement1.end());
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
        state.placement1.push_back({x,y,pos});
        if( indexes_to_hit_me.at(i).size() ){
            for( int idx = 0; idx < indexes_to_hit_me.at(i).size(); ++idx ){
                if( pos )
                    state.player1->hitShip( x + indexes_to_hit_me.at(i).at(idx), y );
                else
                    state.player1->hitShip( x, y + indexes_to_hit_me.at(i).at(idx) );
            }
        }
    }

    std::getline(in, unsplitted);
    int vec_i = std::stoi(unsplitted);
    for( int v = 0; v < vec_i; ++v ){
        int x, y;
        std::getline(in, unsplitted);
        std::istringstream h(unsplitted);
        getline(h, unsplitted, ' ');
        x = std::stoi(unsplitted);
        getline(h, unsplitted, ' ');
        y = std::stoi(unsplitted);
        state.player2->hitShip( x, y );
    }

    state.placement2.erase(state.placement2.begin(),state.placement2.end());
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
        state.placement2.push_back({x,y,pos});

        if( indexes_to_hit.at(i).size() ){
            for( int idx = 0; idx < indexes_to_hit.at(i).size(); ++idx ){
                if( pos )
                    state.player2->hitShip( x + indexes_to_hit.at(i).at(idx), y );
                else
                    state.player2->hitShip( x, y + indexes_to_hit.at(i).at(idx) );
            }
        }
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

int
GameState::getSum(){
    int sum = 0;
    std::ifstream file("seabattle.txt");
    std::string line;
    if( !file.is_open() ){
        throw FileDoesNotExist();
    }
    while( std::getline(file, line) )
    {
        //std::getline(file, line);
        for( char num: line ){
            sum += (int(num)+2153)*6319;
        }
    }
    
    file.close(); 
    return sum;
}

void
GameState::save(){
    MessagePrinter say;
    say.save_start();
    std::ofstream out;
    out.open("seabattle.txt");      // открываем файл для записи
    if (out.is_open())
    {
        out << *this;
    }
    out.close(); 
    std::ofstream strict;
    strict.open("check.txt");
    if( strict.is_open()){
        int control_sum = getSum();
        strict << control_sum;
    }else{
        exit(0);
    }
    strict.close();
    say.save_completed();
}

void
GameState::load(){
    MessagePrinter say;
    say.loading();
    int current_sum = getSum();
    int correct = 0;
    std::ifstream strict;
    strict.open("check.txt");
    if( strict.is_open() ){
        strict >> correct;
    }
    strict.close();
    if( correct != current_sum ){
        throw CheatingAlert();
    }


    std::ifstream in("seabattle.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        in >> *this;
    }else{
        throw FileDoesNotExist();
    }
    in.close();
    say.game_loaded();
}