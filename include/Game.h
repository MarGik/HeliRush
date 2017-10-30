#ifndef GAME_H
#define GAME_H
#include "Helicopter.h"
#include "Enemy.h"
#include "Boss.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Game
{
    public:
        Game();
       ~Game();
       bool getGameOver()const;
       void setGameOver(bool a);
       //mouvement d'helicopter
       void pressW();
       void pressD();
       void pressS();
       void pressA();
       //lancement du projectil
       void pressSpace();

        bool enemyAlive();
       void isHit(int i,int j, bool & li);
       void verifyPosition(int j, bool & li);

       Helicopter getHelicopter()const;
       Enemy getEnemy(int  i)const;

       void setHelicopter(Helicopter h);

       void updateHeliMisslePos(int i);
       void autoPlayEnemy( int curent,int i);

       void autoPlayMultipleEnemy( int curent,unsigned int score);
        void autoPlayBoss(int curent);
        Boss getBoss()const;
        void updateBossMisslePos(int i);
        void verifyPositionBossHeli(bool & li);
        void moveLastEnemyAlive(int curent);
    protected:

    private:
    Helicopter myHelicopter;
    Enemy myEnemy[10];
    Boss myBoss;
    bool gameOver;
};

#endif // GAME_H
