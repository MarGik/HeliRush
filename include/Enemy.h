#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Missle.h"
#include "Vector2D.h"
//#include <SDL.h>


using namespace std;
class Enemy
{
    public:
        Enemy();
        ~Enemy();

        Vector2D getPos () const;
        Missle getEnemyMissle ()const;
        bool getIsFired ()const;
        bool getIsAlive()const;

        void setPos (Vector2D pos);
        void setRandomPos();
        void setEnemyMissle (Missle m);
        void setIsAlive (bool state);
        void setIsFired(bool x);

        void fire (unsigned int curent);
        void movement();

    private:
        Vector2D position;
        Missle enemyMissle;
        unsigned int type_move;
        bool isAlive, isFired;
};

#endif // ENEMY_H
