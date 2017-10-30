#ifndef HELICOPTER_H
#define HELICOPTER_H
#include "Vector2D.h"
#include "Missle.h"

#include <iostream>

using namespace std;

class Helicopter
{
    public:
        /*! constructeur */
        Helicopter();
        /*! destructeur */
        ~Helicopter();
        /*! returne la position courante d'helecopter*/
        Vector2D getPos()const;
        /*! change la position du helicopter */
        /** change la position du helicopter avec la position definie dans le Vector2D a*/
        void setPos(Vector2D a);

        int getScore()const;
        void setScore(int s);
        int getLives()const;
        void setLives(int l);
        void fire();
        bool state();
        void setMisslePosHeli(int nbMissle);
        //si il existe une missle libre on recoit sa position dans le  tableau
        // si non on recoit -1(error)
        int getNbMissle()const;
        // renvoie Missle si -1<i<10 si non -1
        Missle getHelicopterMissle(int i)const;
        bool getFired(int i)const;
        void setFired(int i);
        void updateHeliMissleP(int i);
        void setMissleFalse(int i);



    protected:

    private:
    Vector2D position;
    int lives;
    int score;
    Missle helicopterMissle[10];
    bool fired[10];

};

#endif // HELICOPTER_H
