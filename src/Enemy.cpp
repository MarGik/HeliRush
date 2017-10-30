#include "Enemy.h"

Enemy::Enemy()
{
    position.setX(1150);
    position.setY(rand()%401);
    type_move = rand() % 3;
    isAlive=true;
    isFired = false;
}

Enemy::~Enemy()
{
    //dtor
}

Vector2D Enemy::getPos()const {
    return position;
 }
Missle Enemy::getEnemyMissle()const {
    return enemyMissle;
}
bool Enemy::getIsFired ()const {
    return isFired;
}

void Enemy::setPos(Vector2D p) {
    position=p;
}
void Enemy::setEnemyMissle(Missle m) {
    enemyMissle = m;
}
void Enemy::setIsAlive(bool state) {
    isAlive = state;
}

void Enemy::fire (unsigned int curent){
    if(!isFired && curent % 700 == 0) {
        isFired=true;
        Vector2D posNormaliser;
        posNormaliser.setX(position.getX()+10);
        posNormaliser.setY(position.getY()+20);
        enemyMissle.setMissleP(posNormaliser);
        }
        if(isFired && enemyMissle.getMissleP().getX()>-100){
            Vector2D t;
            t.setX(enemyMissle.getMissleP().getX()-3);
            t.setY(enemyMissle.getMissleP().getY());
            enemyMissle.setMissleP(t);
            }else{
            isFired = false;
        }
}


void Enemy::movement()
{   Vector2D* x = new Vector2D;
    unsigned int randomize = rand()%3;
    if(type_move == 0){
        x->setX(getPos().getX()-2);
        x->setY(getPos().getY());
        if(position.getY()<=0 || position.getY() >= 601){
            if(type_move != randomize)
            type_move = randomize;
             else type_move = rand()%3;
        }
    }
    if(type_move == 1){
        x->setX(getPos().getX()-1);
        x->setY(getPos().getY()-1);

        if(position.getY()<=0 || position.getY() >= 601){
            if(type_move != randomize)
            type_move = randomize;
            else type_move = rand()%3;
        }
    }
    if(type_move == 2){
        x->setX(getPos().getX()-1);
        x->setY(getPos().getY()+1);
        if(position.getY() <= 0 || position.getY() >= 601){
            if(type_move != randomize)
            type_move = randomize;
            else type_move = rand()%3;
        }
    }
    setPos(*x);
    delete x;

}

bool Enemy::getIsAlive()const{
    return isAlive;
}

void Enemy::setRandomPos(){
    srand(time(NULL));
    int y =rand()%600 + 1;
    type_move = rand() % 3;
    position.setX(1150);
    position.setY(y);
    isAlive = true;
}

void Enemy::setIsFired(bool x){
    isFired=x;
}

