#include "Boss.h"

Boss::Boss()
{
    position.setX(1130);
    position.setY(250);

    for(unsigned int i = 0 ; i<10 ; i++){
        fired[i]=false;
    }
    life = 60;
    type_movement = 0;
}

Boss::~Boss()
{
    //dtor
}

Vector2D Boss::getPosition()const{
    return position;
}

void Boss::setPosition(Vector2D p){
    position.setX(p.getX());
    position.setY(p.getY());
}

unsigned int Boss::getLife()const{
    return life;
}

void Boss::setLife( int l){
   life = l;
}

void Boss::mouvement(){
    Vector2D* x = new Vector2D;
    // vers gauche
    if(type_movement == 0 ){
        x->setX(position.getX()-2);
        x->setY(position.getY());
    }
    // en haut et a gauche
    if(type_movement == 1){
        x->setX(position.getX()-1);
        x->setY(position.getY()-1);
    }
    //en bas et a gauche
    if(type_movement == 2){
        x->setX(position.getX()-1);
        x->setY(position.getY()+1);
    }
    //en haut
    if(type_movement == 3){
        x->setX(position.getX());
        x->setY(position.getY()-2);
    }
    //en bas
    if(type_movement == 4){
        x->setX(position.getX());
        x->setY(position.getY()+2);
    }
    // vers droit
    if(type_movement == 5){
        x->setX(position.getX()+2);
        x->setY(position.getY());
    }
    //en haut et a droit
    if(type_movement == 6){
        x->setX(position.getX()+1);
        x->setY(position.getY()-1);
    }
    //en bas et a droit
    if(type_movement == 7){
        x->setX(position.getX()+1);
        x->setY(position.getY()+1);
    }
    // verification si la position ne depasse le carre (500,0)(500,600)(1000,0)(1000,600)
    if(position.getY()<=0 || position.getY() > 500 || position.getX()>1150|| position.getX()<600){

        cout << position.getX() << "|" << position.getY() << "|\n";

         unsigned int randomize = rand()%8;
        if(type_movement != randomize) type_movement = randomize;
        cout << randomize << endl;
    }
    position.setX(x->getX());
    position.setY(x->getY());
    delete x;
}
//cherche la premiere occurance de la missle que n'est pas lance
int Boss::getNbMissle()const{
     int i=0;
    while(fired[i] && i<11){
        i=i+1;
    }
    if(i==10)i=-1;
    return i;
}

// renvoie l'etat de projectile numero i (lance ou non)
bool Boss::getFired(unsigned int i)const{
    return fired[i];
}

// si state == false  on change la position de projectile pour quelle sera pas vu sur l'ecran
void Boss::setFiredState(unsigned int i,bool state){
    if(!state){
        Vector2D x;
        x.setX(-150);
        x.setY(10);
        fired[i]=state;
        BossMissle[i].setMissleP(x);
    } else {
        fired[i] = state;
    }
}
//recupere la ieme Missle
Missle Boss::getMissle(unsigned int i)const{
    return BossMissle[i];
}

void Boss::setMisslePosBoss(unsigned int i){
    Vector2D * x = new Vector2D;
    x->setX(position.getX()+50);
    x->setY(position.getY()+70);
    BossMissle[i].setMissleP(*x);
    delete x;
}

void Boss::updateMisslePosition(unsigned int i){
     Vector2D* direction = new Vector2D;
        direction->setX(-2);
        direction->setY(0);
        if(fired[i])
            BossMissle[i].updateMisslePosition(*direction);
        if(BossMissle[i].getMissleP().getX()<-10) fired[i]=false;
        delete direction;
}

void Boss::fire(int curent){
    int i;
    i=getNbMissle();
    if(i>-1 && !fired[i] && curent % 700 == 0){
        setMisslePosBoss(i);
        fired[i]=true;
    }
}

bool Boss::getAlive()const{
    if(life>0) return true;
    else return false;
}

void Boss::setAlive(bool state){
    isAlive=state;
    if(!state){
        position.setX(1500);
        position.setY(0);
    }
}

