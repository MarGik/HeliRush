#include "./include/SDL_class.h"

int main(int argc, char* argv[]){
    SDL_class sd;
    sd.initGame();
    sd.gameLoop();
    sd.QUIT();


    return 0;
}
