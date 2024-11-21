class EmptyQueue{
public:
    EmptyQueue(){}
    const char* what(){
        const char* msg = "There are no abilities available!\n";
        return msg;
    }
};