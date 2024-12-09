#include "observer.cpp"
#include <iostream>
class PrinterConsole : public IObserver {
public:
    void Update(const GameEvent& event) override {
        switch (event.type) {
            case EventType::Save:
                save_needed();
                break;
            case EventType::Load:
                load_needed();
                break;
            case EventType::Input:
                ask_coordinates();
                break;
            case EventType::LoadCompleted:
                game_loaded();
                break;
            case EventType::SaveCompleted:
                save_completed();
                break;
            case EventType::Start:
                greeting();
                break;
            case EventType::Win:
                congratulations();
                break;
            case EventType::Loss:
                dont_be_upset();
                break;
            case EventType::Crime:
                crime_and_punishment();
                break;
            case EventType::Ab:
                ability_needed();
                break;
            default:
                std::cout << "Something went wrong!\n";
                exit(0);
        }
    }
        
    void
    congratulations(){
        std::cout << "Congratulations! Now let's continue that adventure! Next round!\n";
    }
        
    void
    dont_be_upset(){
        std::cout << "Errr.... Better luck next time?\n";
    }

    void
    ask_coordinates(){
        std::cout << "Where do you want to hit?\n";
    }

    void
    ability_needed(){
        std::cout << "Do you want to use ability? 1/0\n";
    }

    void
    greeting(){
        std::cout << "Hola chico nuevo!\n";
        std::cout << "Or do we have a sea wolf here?\n";
        std::cout << "Perhaps it's time to find out!\n";
        std::cout << "Time to scrub the deck, tie some sailor knots, and catch a fair wind!\n";
        std::cout << "Good luck, sailor!\n";
        std::cout << "------------------------------------------------------------------------\n\n";
    }

    void
    crime_and_punishment(){
        std::cout << "But still - no ability is being activated now\n";
    }

    void
    save_start(){
        std::cout << "Saving in process!\n";
    }

    void
    save_completed(){
        std::cout << "Saved!\n";
    }

    void
    loading(){
        std::cout << "Loading...\n";
    }

    void
    game_loaded(){
        std::cout << "Load is done!\n";
    }

    void
    load_needed(){
        std::cout << "Do you want to load game? (1/0)\n";
    }

    void
    save_needed(){  
        std::cout << "Do you want to save the game? (1/0)\n";
    }
};