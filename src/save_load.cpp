#include "keeper.cpp"

class SaveLoad{
private:
    std::fstream strict;

    void
    insecure_save( GameState* state ){
        SaveKeeper keep = SaveKeeper(state);
        // keep.save();
    }

    void
    prepare(){
        SecretAgent agent_007;
        if( strict.is_open()){
            int control_sum = agent_007.getSum();
            int current_sum = 0;
            strict >> current_sum;
            if( current_sum != control_sum ){
                throw CheatingAlert();
            }
        }else{
            throw CheatingAlert();
        }
    }

public:
    SaveLoad(){
        strict.open("check.txt");
        if( !strict.is_open() )
            throw FileDoesNotExist();
    }
    ~SaveLoad(){
        strict.close();
    }

    void
    save( GameState* state ){
        insecure_save( state );

        SecretAgent agent_007;
        if( strict.is_open()){
            int control_sum = agent_007.getSum();
            strict << control_sum;
        }else{
            exit(0);
        }
    }

    void
    load( GameState* state ){
        try{
            prepare();
        }
        catch( CheatingAlert& e ){
            std::cout << e.what();
            exit(0);
        }
        LoadKeeper keep = LoadKeeper(state);
        //keep.load();
    }
};