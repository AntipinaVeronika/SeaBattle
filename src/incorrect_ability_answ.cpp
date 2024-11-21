#include <string>

class IncorrectAbilityAnswer{
    std::string answer;
    std::string msg;
public:
    IncorrectAbilityAnswer( std::string answer ):answer(answer){}
    const char* what(){
        msg = "I do hope that was accident. You entered " + answer + '\n';
        return msg.c_str();
    }
};