#include <string>
class IncorrectCommand{
    std::string command;
public:
    IncorrectCommand( std::string command ): command(command){}
    const char* what(){
        std::string mes = "IncorrectCommand! You entered " + command + '\n';
        const char* msg = mes.c_str();
        return msg;
    }
};