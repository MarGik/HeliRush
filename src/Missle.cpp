#include "Missle.h"

#include "Missle.h"

Missle::Missle()
{
    possition.setX(0);

}

Missle::Missle(Vector2D p){
    possition.setX(p.getX());
    possition.setY(p.getY());
    }

void Missle::setMissleP(Vector2D p){
    this->possition.setX(p.getX());
    this->possition.setY(p.getY());
}


Vector2D Missle::getMissleP(){
    Vector2D returned;
    returned.setX(this->possition.getX());
    returned.setY(this->possition.getY());
    return returned;
}

void Missle::updateMisslePosition(Vector2D direction){
    possition = possition + direction;
}

Missle::~Missle()
{
}

Vector2D Missle::HelicopterMissleSDL(){
    Vector2D x;
    x.setX(possition.getX()+30);
    x.setY(possition.getY() + 10);
    return x;
}
