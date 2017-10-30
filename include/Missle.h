#ifndef MISSLE_H
#define MISSLE_H



#include "Vector2D.h"

class Missle
{
    public:
        /*! Constructeur par default*/
        Missle();
        /*! Constructuer avec les variables v et p */
        /**
        *   \param p,s de type Vector2D
        *    p->possition
        *    s->speed
        */
        Missle(Vector2D p);
        /*! destructeur */
        ~Missle();
        void setMissleP(Vector2D p);
        Vector2D getMissleP();
        /*! change la position du projectil lancee par raport a la vitesse */
        void updateMisslePosition(Vector2D direction);

        Vector2D HelicopterMissleSDL();



    protected:

    private:

        Vector2D possition;


};

#endif // MISSLE_H
