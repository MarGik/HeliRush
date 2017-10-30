#ifndef SDL_CLASS_H
#define SDL_CLASS_H
#include "Game.h"
//#include "Texture.h"
//#include <SDL.h>
//#include <SDL_ttf.h>
//#include <SDL_image.h>
//#include <SDL_mixer.h>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

//class gerant les textures avec leur rectangles
class Texture
{
    public:
        Texture();
        ~Texture();
        void setRectangle(int w,int h,int x,int y);
        const SDL_Rect* getRectangle() ;
        void CreateTextFromSurf(SDL_Renderer* r,SDL_Surface* s);
        SDL_Texture* getTexture()const;
        void QuitTexture();
    protected:

    private:
    SDL_Rect myRect;
    SDL_Texture* myTexture;

};

// class gerant la graphique du jeu
class SDL_class
{
    public:
        SDL_class();
        ~SDL_class();
        void initGame();
        int menuLoop();
        void gameLoop();
        void freeTexture();
        void QUIT();



    protected:

    private:
    SDL_Surface* gSurface;
    Texture tBackground;
    Texture tHelicopter;
    Texture tEnemy[10];
    Texture tEnemyMissle[10];
    Texture tTabHeliMissle[10];
    Texture tLifeHeli[3];
    Texture tScore;
    Texture tBoss;
    Texture tBossMissle[10];

    Texture play;
    Texture quitGame;
    Game myGame;
    SDL_Renderer* renderer;
    SDL_Window* myWindow;

    //The music that will be played
    Mix_Music *gMusic;
    //The sound effects that will be used
    Mix_Chunk *gMissle;
    Mix_Chunk *gExplosion;

};

#endif // SDL_CLASS_H
