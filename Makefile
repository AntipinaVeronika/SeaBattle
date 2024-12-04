# Папки для исходников и заголовков
SRC_DIR = ./src
HEADER_DIR = ./headers

# Список всех объектов
OBJS = main.o ship.o ship_manager.o gameboard.o game.o IAbilities.o input_handler.o message_printer.o printer.o s_manager_errors.o ship_errors.o ability_manager.o empty_queue_error.o game_state.o cheating_alert.o file_not_found.o save_load.o keeper.o

# Компилятор
CXX = g++
CXXFLAGS = -I$(HEADER_DIR)

# Цель по умолчанию
all: main

# Компиляция исполняемого файла
main: $(OBJS)
	g++ $(OBJS)

save_load.o: $(SRC_DIR)/save_load.cpp keeper.o
	g++ -c $(SRC_DIR)/save_load.cpp

keeper.o: $(SRC_DIR)/keeper.cpp
	g++ -c $(SRC_DIR)/keeper.cpp

file_not_found.o: $(SRC_DIR)/file_not_found.cpp
	g++ -c $(SRC_DIR)/file_not_found.cpp

cheating_alert.o: $(SRC_DIR)/cheating_alert.cpp
	g++ -c $(SRC_DIR)/cheating_alert.cpp

game_state.o: $(SRC_DIR)/game_state.cpp $(HEADER_DIR)/game_state.h file_not_found.o cheating_alert.o
	g++ -c $(SRC_DIR)/game_state.cpp

empty_queue_error.o: $(SRC_DIR)/empty_queue_error.cpp
	g++ -c $(SRC_DIR)/empty_queue_error.cpp

ability_manager.o: $(SRC_DIR)/ability_manager.cpp $(HEADER_DIR)/ability_manager.h 
	g++ -c $(SRC_DIR)/ability_manager.cpp

game.o: $(HEADER_DIR)/game.h $(SRC_DIR)/game.cpp printer.o $(HEADER_DIR)/ability_manager.h ship_manager.o file_not_found.o cheating_alert.o save_load.o
	g++ -c $(SRC_DIR)/game.cpp

IAbilities.o: $(SRC_DIR)/IAbilities.cpp $(HEADER_DIR)/IAbilities.h $(HEADER_DIR)/message_printer.h $(HEADER_DIR)/input_handler.h
	g++ -c $(SRC_DIR)/IAbilities.cpp

input_handler.o: $(SRC_DIR)/input_handler.cpp $(HEADER_DIR)/input_handler.h printer.o gameboard_errors.o ship_errors.o s_manager_errors.o
	g++ -c $(SRC_DIR)/input_handler.cpp

message_printer.o: $(HEADER_DIR)/message_printer.h $(SRC_DIR)/message_printer.cpp
	g++ -c $(SRC_DIR)/message_printer.cpp

printer.o: $(SRC_DIR)/printer.cpp $(HEADER_DIR)/printer.h
	g++ -c $(SRC_DIR)/printer.cpp

s_manager_errors.o: $(SRC_DIR)/s_manager_errors.cpp
	g++ -c $(SRC_DIR)/s_manager_errors.cpp

ship_errors.o: $(SRC_DIR)/ship_errors.cpp
	g++ -c $(SRC_DIR)/ship_errors.cpp

gameboard_errors.o: $(SRC_DIR)/gameboard_errors.cpp
	g++ -c $(SRC_DIR)/gameboard_errors.cpp

main.o: $(SRC_DIR)/main.cpp
	g++ -c $(SRC_DIR)/main.cpp

ship_manager.o: $(SRC_DIR)/ship_manager.cpp $(HEADER_DIR)/ship_manager.h ship.o
	g++ -c $(SRC_DIR)/ship_manager.cpp

gameboard.o: $(SRC_DIR)/gameboard.cpp $(HEADER_DIR)/gameboard.h ship.o
	g++ -c $(SRC_DIR)/gameboard.cpp

ship.o: $(HEADER_DIR)/ship.h $(SRC_DIR)/ship.cpp
	g++ -c $(SRC_DIR)/ship.cpp

# Очистка
clean:
	rm -rf *.o main