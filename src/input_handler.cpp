#include "../headers/input_handler.h"

// std::vector<int>
// InputHandler::create_num_vector(){
//     int one, two, three, four;
//     std::cout << "How many ships of size one would you like?\n";
//     std::cin >> one;
//     std::cout << "How many ships of size two would you like?\n";
//     std::cin >> two;
//     std::cout << "How many ships of size three would you like?\n";
//     std::cin >> three;
//     std::cout << "How many ships of size four would you like?\n";
//     std::cin >> four;
//     std::vector<int> ret{one,two,three,four};

//     return ret;
// }

// void 
// InputHandler::gameboard_creation(){
//     MessagePrinter say;
//     bool flag = false;
//     do{
//         try{
//             say.ask_gameboard_sizes();
//             std::cin >> this->width >> this->height;
//             player1 = Gameboard(height, width);
//             flag = true;
//         }
//         catch(IncorrectBoardSize& e){
//             std::cout << e.what();
//             flag = false;
//         }
//     }while( flag == false );
// }

// void
// InputHandler::enemy_rise_gb( int height, int width ){
//     this->height = height;
//     this->width = width;
//     this->player2 = Gameboard( this->height, this->width );
// }

// void 
// InputHandler::place_opponent( ShipManager& manager1, ShipManager& manager, std::vector<std::vector<int>>& placement2 ){
//     int x = 0;
//     int y = 0;
//     int pos = 0;

//     placement2.resize(manager1.getCapacity());
//     time_t timer;
//     std::srand(time(&timer));
//     //opponents' placement
//     for( int i = manager1.getCapacity()-1; i>-1; i-- ){
//         placement2.at(i).resize(3);
//         bool flag = false;
//         do{
//             try{
//                 x = std::rand() % (this->width);
//                 y = std::rand() % (this->height);
//                 pos = std::rand() % 2;
//                 player2.addShip( manager.getShipIdx(i), x, y, Position(pos) );
//                 flag = true;
//             }
//             catch(PlacementError& e){
//                 flag = false;
//             }
//             if( flag ){
//                 placement2.at(i) = { x, y, pos };
//             }
//         } while( flag == false );
//     }
// }

// void 
// InputHandler::place_ships( ShipManager& manager1, std::vector<std::vector<int>>& placement1 ){
//     int x = 0;
//     int y = 0;
//     int pos = 0;
//     Printer printer;
//     MessagePrinter say;
//     placement1.resize(manager1.getCapacity());

//     for( int i = manager1.getCapacity()-1; i>-1; i-- ){
//         bool flag = false;
//         placement1.at(i).resize(3);
            
//         std::vector < std:: vector <Cell> > users_gameboard_1;

//         do{
//             try{
//                 users_gameboard_1 = player1.getUsersGameboard(); 
//                 printer.printUsersGameboard( users_gameboard_1, width, height );                   

//                 say.ask_placement();
//                 say.what_length( manager1.getShipIdx(i)->getLength() );
//                 std::cin >> x >> y >> pos;
//                 player1.addShip( manager1.getShipIdx(i), x, y, Position(pos) );
//                 flag = true;
//             }  
//             catch(PlacementError& e){
//                 std::cout << e.what();
//                 flag = false;
//             }
//             if( flag ){
//                 placement1.at(i) = { x, y, pos };
//             }
//         }while( flag == false );
//     }
    
// }

// InputHandler::InputHandler(){}

// void 
// InputHandler::gameboard_initialize( Gameboard& player1, ShipManager& manager1, std::vector<std::vector<int>>& placement1 ){
//     gameboard_creation();
//     place_ships( manager1, placement1 );
//     player1 = this->player1;
//     Printer printer;
//     std::vector < std::vector <Cell> > users_gameboard_1 = (this->player1).getUsersGameboard();
//     printer.printUsersGameboard( users_gameboard_1, (this->player1).getWidth(), (this->player1).getHeight() );
// }

// void 
// InputHandler::e_gameboard_initialize( Gameboard& player1, Gameboard& player2, ShipManager& manager1, ShipManager& manager2, std::vector<std::vector<int>>& placement2 ){
//     enemy_rise_gb( player1.getHeight(), player1.getWidth() );
//     place_opponent( manager1, manager2, placement2 );
//     player2 = this->player2;
// }

// void
// InputHandler::enemy_s_manager( ShipManager& manager1, ShipManager& manager2 ){
//     std::vector<int> sizes = {1,2,3,4};
//     if( this->nums.size()==0 ){
//         std::vector<int> n;
//         Ship* ship1 = manager1.getShipIdx(0);

//         int length = ship1->getLength();
//         int cur = 1;
//         int count = 0;
//         if( length != cur ){
//             n.push_back(0);
//             cur++;
//         }
//         for( int i = 0; i < manager1.getCapacity(); ++i ){
//                 ship1 = manager1.getShipIdx(i);

//                 if( length != ship1->getLength() ){
//                     n.push_back(count);
//                     count = 0;
//                     length = ship1->getLength();
//                     cur++;
//                 }
//                 if( length != cur ){
//                     n.push_back(0);
//                     cur++;
//                 }

//                 length = ship1->getLength();
//                 count++;
//         }
//         n.push_back( count );
//         if( length < 5 ){
//             for( int i = length+1; i < 5; i++ ){
//                 n.push_back(0);
//             }
//         }

//         this->nums = n;
//     }

//     this->manager2 = ShipManager(this->nums, sizes);
//     manager2 = this->manager2;
// }

// void 
// InputHandler::manager_initialize( ShipManager& manager1, ShipManager& manager2 ){
//     std::vector<int> sizes = {1,2,3,4};

//     bool flag = false;
//     do{
//         try{
//             this->nums = create_num_vector();
//             this->manager1 = ShipManager(nums, sizes);
//             //this->manager2 = ShipManager(nums, sizes);
//             flag = true;
//         }
//         catch(LengthDiscrepancy& e){
//             std::cout << e.what();
//             flag = false;
//         }
//         catch(SizeOfNumberUnderZero& e){
//             std::cout << e.what();
//             flag = false;
//         }
//     }while( flag == false );
//     manager1 = this->manager1;
//     enemy_s_manager( manager1, manager2 );
//     //manager2 = this->manager2;
// }

// void
// InputHandler::get_x_y( int& x, int& y ){
//     std::cin >> x >> y;
// }

// void
// InputHandler::get_answer( int& answer ){
//     std::string answ;
//     std::cin >> answ;
//     if( answ != "1" && answ != "0" ){
//         throw IncorrectAbilityAnswer( answ );
//     }else{
//         answer = stoi(answ);
//     }
// }
#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept> // Для выброса исключений

std::vector<int>
InputHandler::create_num_vector() {
    int one, two, three, four;

    auto get_input = [](int &value, const std::string &prompt) {
        while (true) {
            std::cout << prompt;
            std::string input;  // Используем строку для ввода
            std::cin >> input;

            // Попробуем преобразовать строку в число
            try {
                value = std::stoi(input); // Преобразование строки в число
                if (value < 0) { // Проверка на отрицательное значение
                    throw std::invalid_argument("Number must be greater than zero.\n");
                }
                break; // Выход из цикла, если преобразование прошло успешно
            } catch (const std::invalid_argument &) {
                std::cout << "Incorrect input. Value must be greater than zero.\n";
            } catch (const std::out_of_range &) {
                std::cout << "Wow! That's too many!\n";
            }
        }
    };

    get_input(one, "How many ships of size 1 do you want?\n");
    get_input(two, "How many ships of size 2 do you want?\n");
    get_input(three, "How many ships of size 3 do you want?\n");
    get_input(four, "How many ships of size 4 do you want?\n");

    std::vector<int> ret{one, two, three, four};
    return ret;
}

void InputHandler::gameboard_creation() {
    MessagePrinter say;
    bool flag = false;
    do {
        try {
            say.ask_gameboard_sizes();
            std::cin >> this->width >> this->height;
            if (std::cin.fail() || this->width <= 0 || this->height <= 0) {
                throw IncorrectBoardSize();
            }

            player1 = Gameboard(height, width);
            flag = true;
        }
        catch (IncorrectBoardSize& e) {
            std::cout << e.what();
            std::cin.clear(); // Сброс состояния потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            flag = false;
        }
    } while (!flag);
}

void InputHandler::enemy_rise_gb(int height, int width) {
    this->height = height;
    this->width = width;
    this->player2 = Gameboard(this->height, this->width);
}

void InputHandler::place_opponent(ShipManager& manager1, ShipManager& manager, std::vector<std::vector<int>>& placement2) {
    int x = 0;
    int y = 0;
    int pos = 0;

    placement2.resize(manager1.getCapacity());
    time_t timer;
    std::srand(time(&timer));
    // Определение размещения врага
    for (int i = manager1.getCapacity() - 1; i > -1; i--) {
        placement2.at(i).resize(3);
        bool flag = false;
        do {
            try {
                x = std::rand() % this->width;
                y = std::rand() % this->height;
                pos = std::rand() % 2;
                player2.addShip(manager.getShipIdx(i), x, y, Position(pos));
                flag = true;
            }
            catch (PlacementError& e) {
                flag = false;
            }
            if (flag) {
                placement2.at(i) = { x, y, pos };
            }
        } while (flag == false);
    }
}

void InputHandler::place_ships(ShipManager& manager1, std::vector<std::vector<int>>& placement1) {
    int x = 0;
    int y = 0;
    int pos = 0;
    Printer printer;
    MessagePrinter say;
    placement1.resize(manager1.getCapacity());
    for (int i = manager1.getCapacity() - 1; i > -1; i--) {
        bool flag = false;
        placement1.at(i).resize(3);
        std::vector<std::vector<Cell>> users_gameboard_1;
        do {
            try {
                users_gameboard_1 = player1.getUsersGameboard();
                printer.printUsersGameboard(users_gameboard_1, width, height);

                say.ask_placement();
                say.what_length(manager1.getShipIdx(i)->getLength());

                // Запрашиваем ввод для x, y и pos с обработкой ошибок
                while (true) {
                    try {
                        std::cout << "Enter x, y and position (0 or 1): ";
                        std::string input_x, input_y, input_pos;
                        std::cin >> input_x >> input_y >> input_pos;

                        x = std::stoi(input_x); // Преобразование строки в число
                        y = std::stoi(input_y); // Преобразование строки в число
                        pos = std::stoi(input_pos); // Преобразование строки в число

                        if (x < 0 || y < 0 || (pos != 0 && pos != 1)) {
                            throw std::invalid_argument("Incorrect input. Please, enter coordinates greater than 0 and either 0 or 1 for position.");
                        }
                        break; // Ввод корректен, выходим из цикла
                    }
                    catch (const std::invalid_argument& e) {
                        std::cout << e.what() << std::endl;
                    }
                    catch (const std::out_of_range&) {
                        std::cout << "Lower values are required." << std::endl;
                    }
                }

                player1.addShip(manager1.getShipIdx(i), x, y, Position(pos));
                flag = true;
            }
            catch (PlacementError& e) {
                std::cout << e.what();
                flag = false;
            }
            if (flag) {
                placement1.at(i) = { x, y, pos };
            }
        } while (flag == false);
    }
}

InputHandler::InputHandler(){}

void InputHandler::gameboard_initialize(Gameboard& player1, ShipManager& manager1, std::vector<std::vector<int>>& placement1) {
    gameboard_creation();
    place_ships(manager1, placement1);
    player1 = this->player1;
    Printer printer;
    std::vector < std::vector <Cell> > users_gameboard_1 = (this->player1).getUsersGameboard();
    printer.printUsersGameboard(users_gameboard_1, (this->player1).getWidth(), (this->player1).getHeight());
}

void InputHandler::e_gameboard_initialize(Gameboard& player1, Gameboard& player2, ShipManager& manager1, ShipManager& manager2, std::vector<std::vector<int>>& placement2) {
    enemy_rise_gb(player1.getHeight(), player1.getWidth());
    place_opponent(manager1, manager2, placement2);
    player2 = this->player2;
}

void InputHandler::enemy_s_manager(ShipManager& manager1, ShipManager& manager2) {
    std::vector<int> sizes = { 1, 2, 3, 4 };
    if (this->nums.size() == 0) {
        std::vector<int> n;
        Ship* ship1 = manager1.getShipIdx(0);

        int length = ship1->getLength();
        int cur = 1;
        int count = 0;
        if (length != cur) {
            n.push_back(0);
            cur++;
        }
        for (int i = 0; i < manager1.getCapacity(); ++i) {
            ship1 = manager1.getShipIdx(i);

            if (length != ship1->getLength()) {
                n.push_back(count);
                count = 0;
                length = ship1->getLength();
                cur++;
            }
            if (length != cur) {
                n.push_back(0);
                cur++;
            }

            length = ship1->getLength();
            count++;
        }
        n.push_back(count);
        if (length < 5) {
            for (int i = length + 1; i < 5; i++) {
                n.push_back(0);
            }
        }

        this->nums = n;
    }

    this->manager2 = ShipManager(this->nums, sizes);
    manager2 = this->manager2;
}

void InputHandler::manager_initialize(ShipManager& manager1, ShipManager& manager2) {
    std::vector<int> sizes = { 1, 2, 3, 4 };

    bool flag = false;
    do {
        try {
            this->nums = create_num_vector();
            this->manager1 = ShipManager(nums, sizes);
            flag = true;
        }
        catch (LengthDiscrepancy& e) {
            std::cout << e.what();
            flag = false;
        }
        catch (SizeOfNumberUnderZero& e) {
            std::cout << e.what();
            flag = false;
        }
    } while (flag == false);
    manager1 = this->manager1;
    enemy_s_manager(manager1, manager2);
}

void
InputHandler::get_x_y(int &x, int &y) {
    while (true) {
        std::cout << "Input x and y: ";
        std::string input_x, input_y; // Храним ввод как строки
        std::cin >> input_x >> input_y;

        // Проверяем ввод для x
        try {
            x = std::stoi(input_x);
            if (x < 0) { // Проверка на отрицательное значение
                throw std::invalid_argument("x can't be lower than zero!\n");
            }
        } catch (const std::invalid_argument &) {
            std::cout << "Incorrect input for x\n";
            continue; // Запрашиваем ввод снова
        } catch (const std::out_of_range &) {
            std::cout << "x is tooooo big!\n";
            continue;
        }

        // Проверяем ввод для y
        try {
            y = std::stoi(input_y);
            if (y < 0) { // Проверка на отрицательное значение
                throw std::invalid_argument("y can't be lower than zero\n");
            }
        } catch (const std::invalid_argument &) {
            std::cout << "Incorrect input for y\n";
            continue; // Запрашиваем ввод снова
        } catch (const std::out_of_range &) {
            std::cout << "y is toooo big!\n";
            continue;
        }

        break; // Выходим из цикла, если оба ввода корректны
    }
}

void InputHandler::get_answer(int &answer) {
    std::string answ;
    while (true) {
        std::cout << "Enter answer(0 or 1): ";
        std::cin >> answ;
        // Проверяем ввод
        if (answ != "1" && answ != "0") {
            std::cout << "Error: incorrect input. Try again!\n";
        } else {
            answer = std::stoi(answ);
            break;
        }
    }
}