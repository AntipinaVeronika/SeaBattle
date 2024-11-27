class CheatingAlert{
public:
    CheatingAlert()=default;
    const char* what(){
            const char* msg = "Whaaaat? You wanted to cheat? That's pretty pirate thing, but you got caught. Adios!\n";
            return msg;
    }
};