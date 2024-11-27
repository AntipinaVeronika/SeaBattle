#include "../headers/input_handler.h"

std::vector<int>
InputHandler::create_num_vector(){
    int one, two, three, four;
    std::cout << "How many ships of size one would you like?\n";
    std::cin >> one;
    std::cout << "How many ships of size two would you like?\n";
    std::cin >> two;
    std::cout << "How many ships of size three would you like?\n";
    std::cin >> three;
    std::cout << "How many ships of size four would you like?\n";
    std::cin >> four;
    std::vector<int> ret{one,two,three,four};

    return ret;
}

void 
InputHandler::gameboard_creation(){
    MessagePrinter say;
    bool flag = false;
    do{
        try{
            say.ask_gameboard_sizes();
            std::cin >> this->width >> this->height;
            player1 = Gameboard(height, width);
            flag = true;
        }
        catch(IncorrectBoardSize& e){
            std::cout << e.what();
            flag = false;
        }
    }while( flag == false );
}

void
InputHandler::enemy_rise_gb( int height, int width ){
    this->height = height;
    this->width = width;
    this->player2 = Gameboard( this->height, this->width );
}

void 
InputHandler::place_opponent( ShipManager& manager1, ShipManager& manager, std::vector<std::vector<int>>& placement2 ){
    int x = 0;
    int y = 0;
    int pos = 0;

    placement2.resize(manager1.getCapacity());
    time_t timer;
    std::srand(time(&timer));
    //opponents' placement
    for( int i = manager1.getCapacity()-1; i>-1; i-- ){
        placement2.at(i).resize(3);
        bool flag = false;
        do{
            try{
                x = std::rand() % (this->width);
                y = std::rand() % (this->height);
                pos = std::rand() % 2;
                player2.addShip( manager.getShipIdx(i), x, y, Position(pos) );
                flag = true;
            }
            catch(PlacementError& e){
                flag = false;
            }
            if( flag ){
                placement2.at(i) = { x, y, pos };
            }
        } while( flag == false );
    }
}

void 
InputHandler::place_ships( ShipManager& manager1, std::vector<std::vector<int>>& placement1 ){
    int x = 0;
    int y = 0;
    int pos = 0;
    Printer printer;
    MessagePrinter say;
    placement1.resize(manager1.getCapacity());

    for( int i = manager1.getCapacity()-1; i>-1; i-- ){
        bool flag = false;
        placement1.at(i).resize(3);
            
        std::vector < std:: vector <Cell> > users_gameboard_1;

        do{
            try{
                users_gameboard_1 = player1.getUsersGameboard(); 
                printer.printUsersGameboard( users_gameboard_1, width, height );                   

                say.ask_placement();
                say.what_length( manager1.getShipIdx(i)->getLength() );
                std::cin >> x >> y >> pos;
                player1.addShip( manager1.getShipIdx(i), x, y, Position(pos) );
                flag = true;
            }  
            catch(PlacementError& e){
                std::cout << e.what();
                flag = false;
            }
            if( flag ){
                placement1.at(i) = { x, y, pos };
            }
        }while( flag == false );
    }
    
}

InputHandler::InputHandler(){}

void 
InputHandler::gameboard_initialize( Gameboard& player1, ShipManager& manager1, std::vector<std::vector<int>>& placement1 ){
    gameboard_creation();
    place_ships( manager1, placement1 );
    player1 = this->player1;
    Printer printer;
    std::vector < std::vector <Cell> > users_gameboard_1 = (this->player1).getUsersGameboard();
    printer.printUsersGameboard( users_gameboard_1, (this->player1).getWidth(), (this->player1).getHeight() );
}

void 
InputHandler::e_gameboard_initialize( Gameboard& player1, Gameboard& player2, ShipManager& manager1, ShipManager& manager2, std::vector<std::vector<int>>& placement2 ){
    enemy_rise_gb( player1.getHeight(), player1.getWidth() );
    place_opponent( manager1, manager2, placement2 );
    player2 = this->player2;
}

void
InputHandler::enemy_s_manager( ShipManager& manager1, ShipManager& manager2 ){
    std::vector<int> sizes = {1,2,3,4};
    if( this->nums.size()==0 ){
        std::vector<int> n;
        Ship* ship1 = manager1.getShipIdx(0);

        int length = ship1->getLength();
        int cur = 1;
        int count = 0;
        if( length != cur ){
            n.push_back(0);
            cur++;
        }
        for( int i = 0; i < manager1.getCapacity(); ++i ){
                ship1 = manager1.getShipIdx(i);

                if( length != ship1->getLength() ){
                    n.push_back(count);
                    count = 0;
                    length = ship1->getLength();
                    cur++;
                }
                if( length != cur ){
                    n.push_back(0);
                    cur++;
                }

                length = ship1->getLength();
                count++;
        }
        n.push_back( count );
        if( length < 5 ){
            for( int i = length+1; i < 5; i++ ){
                n.push_back(0);
            }
        }

        this->nums = n;
    }

    this->manager2 = ShipManager(this->nums, sizes);
    manager2 = this->manager2;
}

void 
InputHandler::manager_initialize( ShipManager& manager1, ShipManager& manager2 ){
    std::vector<int> sizes = {1,2,3,4};

    bool flag = false;
    do{
        try{
            this->nums = create_num_vector();
            this->manager1 = ShipManager(nums, sizes);
            //this->manager2 = ShipManager(nums, sizes);
            flag = true;
        }
        catch(LengthDiscrepancy& e){
            std::cout << e.what();
            flag = false;
        }
        catch(SizeOfNumberUnderZero& e){
            std::cout << e.what();
            flag = false;
        }
    }while( flag == false );
    manager1 = this->manager1;
    enemy_s_manager( manager1, manager2 );
    //manager2 = this->manager2;
}

void
InputHandler::get_x_y( int& x, int& y ){
    std::cin >> x >> y;
}

void
InputHandler::get_answer( int& answer ){
    std::string answ;
    std::cin >> answ;
    if( answ != "1" && answ != "0" ){
        throw IncorrectAbilityAnswer( answ );
    }else{
        answer = stoi(answ);
    }
}
