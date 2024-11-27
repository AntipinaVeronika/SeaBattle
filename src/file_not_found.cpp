class FileDoesNotExist{
public:
    FileDoesNotExist(){}
    const char* what(){
        const char* msg = "There is no current save:(\n";
        return msg;
    }
};