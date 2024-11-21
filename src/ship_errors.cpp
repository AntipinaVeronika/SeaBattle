#include <string>

class IncorrectShipSize{
    int length;
    std::string msg;
public:
    IncorrectShipSize( int length ):length(length){}
    const char* what(){
        msg = "Ship can have 1 - 4 length. You entered" + std::to_string( length )+'\n';
        return msg.c_str();
    }
};