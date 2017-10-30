#ifndef BOSS_H
#define BOSS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Missle.h"
#include "Vector2D.h"
#include <iostream>

using namespace std;

class Boss
{
    public:
        Boss();
        ~Boss();
        Vector2D getPosition()const;
        void setPosition(Vector2D p);

        unsigned int getLife()const;
        void setLife( int l);

        void mouvement();
        bool getAlive()const;
        void setAlive(bool state);
        int getNbMissle()const;
        bool getFired(unsigned int i)const;
        void setFiredState(unsigned int i,bool state);
        Missle getMissle(unsigned int i)const;
        void setMisslePosBoss(unsigned int i);
        void updateMisslePosition(unsigned int i);
        void fire(int curent);



    protected:

    private:
        Vector2D position;
        Missle BossMissle[10];
        unsigned int life;
        unsigned int type_movement;
        bool fired[10];
        bool isAlive;

};

#endif // BOSS_H
