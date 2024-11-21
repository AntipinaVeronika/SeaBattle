#include <string>

class LengthDiscrepancy{
    int sizes_length;
    int nums_length;
    std::string msg;
public:
    LengthDiscrepancy( int a, int b ): sizes_length(a), nums_length(b){}
    const char* what(){
        msg = "You entered " + std::to_string(sizes_length) + "sizes and " + std::to_string(nums_length) + "nums. Discrepancy!\n";
        return msg.c_str();
    }
};

class SizeOfNumberUnderZero{
    int num;
    std::string msg;
public:
    SizeOfNumberUnderZero( int num ):num(num){}
    const char* what(){
        msg = "OOps! You want me to add " + std::to_string(num) + "ships!\n";
        return msg.c_str();
    }
};