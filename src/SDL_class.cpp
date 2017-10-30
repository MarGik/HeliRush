#include "SDL_class.h"
//code du class Texture
Texture::Texture()
{
    myRect.h=0;
    myRect.w=0;
    myRect.x=0;
    myRect.y=0;
    myTexture=NULL;
}

Texture::~Texture()
{

}

void Texture::setRectangle(int w,int h,int x,int y){
    myRect.h=h;
    myRect.w=w;
    myRect.x=x;
    myRect.y=y;
}

const SDL_Rect* Texture::getRectangle(){
    return &myRect;
}

void Texture::CreateTextFromSurf(SDL_Renderer* r,SDL_Surface* s){
    myTexture=SDL_CreateTextureFromSurface(r,s);
    if(myTexture==NULL){
        cout << "error at creation of texture from surface\n";
        exit(1);
    }
}

SDL_Texture* Texture::getTexture()const {
    return myTexture;
}

void Texture::QuitTexture(){
    SDL_DestroyTexture(this->myTexture);

}





// code du class SDL_class
SDL_class::SDL_class()
{
    gMusic = NULL;
    gMissle = NULL;
    gExplosion = NULL;

}

SDL_class::~SDL_class()
{
    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
    Mix_Quit();

    //Free the sound effects
    Mix_FreeChunk( gMissle );
    Mix_FreeChunk( gExplosion );

}

void SDL_class::freeTexture(){
    tBackground.QuitTexture();
    tHelicopter.QuitTexture();
    tBoss.QuitTexture();
    play.QuitTexture();
    quitGame.QuitTexture();
//    tScore.QuitTexture();
    for(unsigned int i =0 ; i<10;i++){
        tTabHeliMissle[i].QuitTexture();
        tEnemy[i].QuitTexture();
        tEnemyMissle[i].QuitTexture();
        tBossMissle[i].QuitTexture();
        if(i<3) tLifeHeli[i].QuitTexture();
    }


}

void SDL_class::QUIT(){

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(myWindow);
    renderer = NULL;
    myWindow = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void SDL_class::initGame(){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)==-1){
        cout<<"error SDL_INIT main!..."<<endl;
        exit(1);
    }
    // on verifie si on a bien initialiser TTF
    if( TTF_Init()!=0){
        cout<<"error TTF_init"<<endl;
        exit(1);
    }
     //Initialize PNG loading
     int imgFlags = IMG_INIT_PNG;
     if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
     printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
       exit(1);
       }
    //initialising myWindow
    myWindow=SDL_CreateWindow("Vertiliotik",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1100,700,SDL_WINDOW_SHOWN );
    if(myWindow == NULL){
        printf("error creation window %s\n",SDL_GetError());
        exit(1);
    }
    //initialising renderer
    renderer=SDL_CreateRenderer(myWindow,-1,SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
            printf("error creating renderer %s\n",SDL_GetError());
            exit(1);
    }
     //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

    }
}

int SDL_class::menuLoop(){
    bool quit = false;
    int value;
    //SDL_SetRenderDrawColor(renderer,100,100,100);
    gSurface = IMG_Load("data/play.png");
    if(gSurface==NULL) quit = true;
    play.CreateTextFromSurf(renderer,gSurface);
    play.setRectangle(300,200,400,100);
    SDL_FreeSurface(gSurface);


    gSurface = IMG_Load("data/background.png");
    if(gSurface == NULL) quit = true;
    tBackground.CreateTextFromSurf(renderer,gSurface);
    SDL_FreeSurface(gSurface);

    gSurface = IMG_Load("data/quitGame.png");
    if(gSurface==NULL) quit = true;
    quitGame.CreateTextFromSurf(renderer,gSurface);
    quitGame.setRectangle(300,200,400,400);
    SDL_FreeSurface(gSurface);

    SDL_Event  event;

      while(!quit){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                quit = true;
                }
            switch (event.type ) {
                case SDL_MOUSEBUTTONDOWN:
                    if(event.motion.x>400 && event.motion.x<700 && event.motion.y>100 && event.motion.y<300 ){
                        return 1;
                    }else if(event.motion.x>400 && event.motion.x<700 && event.motion.y>400 && event.motion.y<600 ){
                        return 0;
                    }
                    break;
                default:
                 break;
            }
        }
        SDL_RenderCopy(renderer,tBackground.getTexture(),NULL,NULL);
        SDL_RenderCopy(renderer,play.getTexture(),NULL,play.getRectangle());
        SDL_RenderCopy(renderer,quitGame.getTexture(),NULL,quitGame.getRectangle());
        SDL_RenderPresent(renderer);
    }



}

void SDL_class::gameLoop(){
    bool quit=false;

    if(menuLoop()==0) quit = true;


    SDL_RenderClear(renderer);
    SDL_Event  event;

     //Load music
    gMusic = Mix_LoadMUS( "music/soundtrack.wav" );
    if( gMusic == NULL ){
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
     //Load sound effects
    gMissle = Mix_LoadWAV( "music/missle.wav" );
    if( gMissle == NULL ){
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    gExplosion = Mix_LoadWAV( "music/explosion.wav" );
    if( gExplosion == NULL ){
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    //Play the music
    Mix_PlayMusic( gMusic, -1 );

    gSurface = IMG_Load("data/vertaliot.gif");
    if(gSurface==NULL) quit = true;
  tHelicopter.CreateTextFromSurf(renderer,gSurface);
    tHelicopter.setRectangle(100,100,myGame.getHelicopter().getPos().getX(),myGame.getHelicopter().getPos().getY());
    SDL_FreeSurface(gSurface);
    // seting up helicopter missles
    gSurface = IMG_Load("data/missle.png");
    if(gSurface == NULL) quit=true;
    for(int i = 0; i<10; i++){
        tTabHeliMissle[i].CreateTextFromSurf(renderer,gSurface);
        tTabHeliMissle[i].setRectangle(60,40,myGame.getHelicopter().getHelicopterMissle(i).getMissleP().getX(),myGame.getHelicopter().getHelicopterMissle(i).getMissleP().getY());
    }
    SDL_FreeSurface(gSurface);

    //seting up enemy missle
    gSurface = IMG_Load("data/missleE.png");
    if(gSurface == NULL) quit = true;
    for(int i = 0; i<10 ; i++){
        tEnemyMissle[i].CreateTextFromSurf(renderer,gSurface);
        tEnemyMissle[i].setRectangle(10,10,myGame.getEnemy(i).getEnemyMissle().getMissleP().getX(),myGame.getEnemy(i).getEnemyMissle().getMissleP().getY());
        tBossMissle[i].CreateTextFromSurf(renderer,gSurface);
    }
    SDL_FreeSurface(gSurface);

    gSurface = IMG_Load("data/alien.png");
    if(gSurface == NULL) quit = true;
    for(int i = 0;i<10;i++){
        tEnemy[i].CreateTextFromSurf(renderer,gSurface);
        tEnemy[i].setRectangle(100,100,myGame.getEnemy(i).getPos().getX(),myGame.getEnemy(i).getPos().getY());
        // inserstion d'image de projectile pour missle boss


    }
    SDL_FreeSurface(gSurface);

    gSurface = IMG_Load("data/life.png");
    if(gSurface == NULL) quit = true;
    for(int i = 0;i<3;i++){
        tLifeHeli[i].CreateTextFromSurf(renderer,gSurface);
        tLifeHeli[i].setRectangle(50,50,i*50,650);
    }
    SDL_FreeSurface(gSurface);


    gSurface = IMG_Load("data/myBoss.png");
    if(gSurface==NULL) quit = true;
    tBoss.CreateTextFromSurf(renderer,gSurface);
    SDL_FreeSurface(gSurface);



    int score = 0;
    string text;

    // timing
    unsigned int curent = SDL_GetTicks();
    unsigned int newtime = 0;
    // timing for enemy
    ostringstream convert;
    SDL_Color Red = {255,0,0};
    TTF_Font* gFont = TTF_OpenFont("font/lazy.ttf",50);


    while(!quit){
        while(SDL_PollEvent(&event)){
        if(event.type==SDL_QUIT){
            quit = true;}
        else if (event.type == SDL_KEYDOWN) {              // Si une touche est enfoncee
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_SPACE:
					if(curent > newtime +300){
                    Mix_PlayChannel( -1, gMissle, 0 );
					myGame.pressSpace();
					newtime = curent;
					}
					curent = SDL_GetTicks();
					                    // car Y inverse
					break;
                case SDL_SCANCODE_9:
                    //If there is no music playing
                    if( Mix_PlayingMusic() == 0 )
                    {
                        //Play the music
                        Mix_PlayMusic( gMusic, -1 );
                    }
                    //If music is being played
                    else
                    {
                        //If the music is paused
                        if( Mix_PausedMusic() == 1 )
                        {
                            //Resume the music
                            Mix_ResumeMusic();
                        }
                        //If the music is playing
                        else
                        {
                            //Pause the music
                            Mix_PauseMusic();
                        }
                    }
                        break;

                case SDL_SCANCODE_0:
                    //Stop the music
                    Mix_HaltMusic();
                    break;
                default:
					 break;
            }
        }
    }
    //getting score

        convert << score;
        text=convert.str();
        convert.str("");

        SDL_Surface * myText = NULL;
        myText = TTF_RenderText_Solid(gFont,text.c_str(),Red);

        if(myText==NULL) quit = true;




        tScore.CreateTextFromSurf(renderer,myText);
        if(score < 10) tScore.setRectangle(25,50,0,0);
        if(score >= 10 && score < 100) tScore.setRectangle(50,50,0,0);
        if(score >= 100 && score < 1000) tScore.setRectangle(75,50,0,0);
        if(score >= 1000 && score <10000) tScore.setRectangle(100,50,0,0);
        if(score >= 10000 && score <100000) tScore.setRectangle(125,50,0,0);
        SDL_FreeSurface(myText);

        score = myGame.getHelicopter().getScore();


            //constroling the helicopter
        if(curent > newtime +500){
                        myGame.pressSpace();
                        newtime = curent;
                        }
                        curent = SDL_GetTicks();

        const Uint8* keyPressed = SDL_GetKeyboardState(NULL);

        if(keyPressed[SDL_SCANCODE_ESCAPE]){
            quit = true;
        }else if(keyPressed[SDL_SCANCODE_UP]&&keyPressed[SDL_SCANCODE_RIGHT]){
            myGame.pressW();
            myGame.pressD();
            tHelicopter.setRectangle(100,100,myGame.getHelicopter().getPos().getX(),myGame.getHelicopter().getPos().getY());
        }else if(keyPressed[SDL_SCANCODE_UP]&&keyPressed[SDL_SCANCODE_LEFT]){
            myGame.pressW();
            myGame.pressA();
            tHelicopter.setRectangle(100,100,myGame.getHelicopter().getPos().getX(),myGame.getHelicopter().getPos().getY());
        }else if (keyPressed[SDL_SCANCODE_DOWN]&&keyPressed[SDL_SCANCODE_LEFT]){
            myGame.pressS();
            myGame.pressA();
            tHelicopter.setRectangle(100,100,myGame.getHelicopter().getPos().getX(),myGame.getHelicopter().getPos().getY());
        }else if (keyPressed[SDL_SCANCODE_DOWN]&&keyPressed[SDL_SCANCODE_RIGHT]){
            myGame.pressS();
            myGame.pressD();
            tHelicopter.setRectangle(100,100,myGame.getHelicopter().getPos().getX(),myGame.getHelicopter().getPos().getY());
        }else if(keyPressed[SDL_SCANCODE_UP]){
            // si on presse UP l'helicopter change position avec un pixel en haut
            myGame.pressW();
            tHelicopter.setRectangle(100,100,myGame.getHelicopter().getPos().getX(),myGame.getHelicopter().getPos().getY());
        } else if(keyPressed[SDL_SCANCODE_LEFT]){
            myGame.pressA();
            tHelicopter.setRectangle(100,100,myGame.getHelicopter().getPos().getX(),myGame.getHelicopter().getPos().getY());

        } else if(keyPressed[SDL_SCANCODE_DOWN]){
            myGame.pressS();
            tHelicopter.setRectangle(100,100,myGame.getHelicopter().getPos().getX(),myGame.getHelicopter().getPos().getY());


        } else if(keyPressed[SDL_SCANCODE_RIGHT]){
            myGame.pressD();
            tHelicopter.setRectangle(100,100,myGame.getHelicopter().getPos().getX(),myGame.getHelicopter().getPos().getY());
        }

        if(myGame.getGameOver()) quit = true;
        curent = SDL_GetTicks();



        myGame.autoPlayMultipleEnemy(curent,score);

        tBoss.setRectangle(200,200,myGame.getBoss().getPosition().getX(),myGame.getBoss().getPosition().getY());
        bool  li ;
        li = false;
        for(int i = 0;i<10;i++){

            myGame.verifyPosition(i,li);
            myGame.verifyPositionBossHeli(li);
            if(li){Mix_PlayChannel( -1, gMissle, 0 );}
            if(myGame.getEnemy(i).getIsAlive()){
                tEnemy[i].setRectangle(100,100,myGame.getEnemy(i).getPos().getX(),myGame.getEnemy(i).getPos().getY());
            }
        }


        SDL_RenderCopy(renderer,tBackground.getTexture(),NULL,NULL);

        for (int i = 0 ; i < 10 ; i++){
            if(myGame.getHelicopter().getFired(i)){
                    // affichage des projectiles lance par le joueur
            tTabHeliMissle[i].setRectangle(50,20,myGame.getHelicopter().getHelicopterMissle(i).getMissleP().getX(),myGame.getHelicopter().getHelicopterMissle(i).getMissleP().getY());
            SDL_RenderCopy(renderer,tTabHeliMissle[i].getTexture(),NULL,tTabHeliMissle[i].getRectangle());
            myGame.updateHeliMisslePos(i);
            }
            if(myGame.getEnemy(i).getIsFired()){
                    // affichage des projectile lance a part de enemy
            tEnemyMissle[i].setRectangle(50,50,myGame.getEnemy(i).getEnemyMissle().getMissleP().getX(),myGame.getEnemy(i).getEnemyMissle().getMissleP().getY());
            SDL_RenderCopy(renderer,tEnemyMissle[i].getTexture(),NULL,tEnemyMissle[i].getRectangle());
            }
            if(myGame.getBoss().getFired(i)){
                tBossMissle[i].setRectangle(100,100,myGame.getBoss().getMissle(i).getMissleP().getX(),myGame.getBoss().getMissle(i).getMissleP().getY());
                SDL_RenderCopy(renderer,tBossMissle[i].getTexture(),NULL,tBossMissle[i].getRectangle());
                myGame.updateBossMisslePos(i);
            }

        // affichage d'enemy sur l'ecran
        SDL_RenderCopy(renderer,tEnemy[i].getTexture(),NULL,tEnemy[i].getRectangle());
        }

        SDL_RenderCopy(renderer,tHelicopter.getTexture(),NULL,tHelicopter.getRectangle());
        SDL_RenderCopy(renderer,tBoss.getTexture(),NULL,tBoss.getRectangle());

        for(int i = 0;i<3;i++){
            if(i<myGame.getHelicopter().getLives()){
                SDL_RenderCopy(renderer,tLifeHeli[i].getTexture(),NULL,tLifeHeli[i].getRectangle());
            }
        }
        SDL_RenderCopy(renderer,tScore.getTexture(),NULL,tScore.getRectangle());

        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(tScore.getTexture());
    }
    freeTexture();
    TTF_CloseFont(gFont);
    gFont = NULL;
}
