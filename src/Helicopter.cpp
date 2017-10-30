#include "Helicopter.h"

Helicopter::Helicopter()
{
    lives = 3;
    score = 0;

    for (int i = 0 ; i < 10 ; i++)
        fired[i]=false;
}

Helicopter::~Helicopter()
{

}

Vector2D Helicopter::getPos()const{
    return position;
}

void Helicopter::setPos(Vector2D a){
    position = a;
}

int Helicopter::getScore()const{
    return score;
}

void Helicopter::setScore(int s){
    score = s;
}

int Helicopter::getLives()const{
    return lives;
}

void Helicopter::setLives(int l){
    if(lives > 0)lives = l;
}

void Helicopter::fire(){
    int i;
    i=getNbMissle();

    if(i>-1){
        setMisslePosHeli(i);
        fired[i]=true;
    }
}

void Helicopter::setMisslePosHeli(int nbMissle){
    Vector2D x;
    x.setX(position.getX()+50);
    x.setY(position.getY()+70);
    helicopterMissle[nbMissle].setMissleP(x);

}

int Helicopter::getNbMissle()const{
    int i=0;
//cherche la premiere occurance de false
    while(fired[i] && i<=.9){
       cout << fired[i]<< " " << i <<endl;
        i=i+1;
    }
    if(i==10)i=-1;
    return i;
}

Missle Helicopter::getHelicopterMissle(int i)const{
   return helicopterMissle[i];
}

bool Helicopter::getFired(int i)const{

    return fired[i];
}

void Helicopter::setFired(int i){
    fired[i]=true;
}

void Helicopter::updateHeliMissleP(int i){
        Vector2D* direction = new Vector2D;
        direction->setX(2);
        direction->setY(0);
        if(getFired(i))
            helicopterMissle[i].updateMisslePosition(*direction);
        if(helicopterMissle[i].getMissleP().getX()>1100)
                                                  fired[i]=false;
        delete direction;
}

void Helicopter::setMissleFalse(int i){
    Vector2D x;
    x.setX(-150);
    x.setY(10);
    fired[i]=false;
    helicopterMissle[i].setMissleP(x);
}
