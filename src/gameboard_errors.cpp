#include <string>
class PlacementError{
public:
    PlacementError(){}
    const char* what(){
        const char* msg = "You can't place your ship here!\n";
        return msg;
    }
};

class MissingAim{
    int x;
    int y;
    std::string msg;
public:
    MissingAim( int x, int y ):x(x),y(y){}
    const char* what(){
        msg = "Wow! That was... not close at all... Try again?.. You tried " + (std::to_string(x))+","+std::to_string(y)+"\n";
        return msg.c_str();
    }
};

class IncorrectBoardSize{
public:
    IncorrectBoardSize(){}
    const char* what(){
        const char* msg = "Width and height must be more than 0!\n";
        return msg;
    }
};