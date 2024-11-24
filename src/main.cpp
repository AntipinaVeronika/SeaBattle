#include "../headers/game.h"

int main(){
    int res = 1;
    while( res ){
        Game new_game;
        res = new_game.start();
    }
    return 0;
}