#include "input_handler.h"

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
            player2 = Gameboard(height, width);
            flag = true;
        }
        catch(IncorrectBoardSize& e){
            std::cout << e.what();
            flag = false;
        }
    }while( flag == false );
}

void 
InputHandler::place_opponent( ShipManager& manager ){
    int x = 0;
    int y = 0;
    int pos = 0;

    time_t timer;
    std::srand(time(&timer));
    //opponents' placement
    for( int i = manager1.getCapacity()-1; i>-1; i-- ){
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
        } while( flag == false );
    }
}

void 
InputHandler::place_ships( ShipManager& manager1, ShipManager& manager2 ){
    int x = 0;
    int y = 0;
    int pos = 0;
    Printer printer;
    MessagePrinter say;

    for( int i = manager1.getCapacity()-1; i>-1; i-- ){
        bool flag = false;
            
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
        }while( flag == false );
    }
    place_opponent( manager2 );
}

InputHandler::InputHandler(){}

void 
InputHandler::gameboard_initialize( Gameboard& player1, Gameboard& player2, ShipManager& manager1, ShipManager& manager2  ){
    gameboard_creation();
    place_ships( manager1, manager2 );
    player1 = this->player1;
    player2 = this->player2;
    // manager1 = this->manager1;
    // manager2 = this->manager2;
    Printer printer;
    std::vector < std::vector <Cell> > users_gameboard_1 = (this->player1).getUsersGameboard();
    printer.printUsersGameboard( users_gameboard_1, (this->player1).getWidth(), (this->player1).getHeight() );
}

void 
InputHandler::manager_initialize( ShipManager& manager1, ShipManager& manager2 ){
    std::vector<int> sizes = {1,2,3,4};

    bool flag = false;
    do{
        try{
            std::vector<int> nums = create_num_vector();
            this->manager1 = ShipManager(nums, sizes);
            this->manager2 = ShipManager(nums, sizes);
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
    manager2 = this->manager2;
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
