#include "Game.h"

Game::Game()
{
   gameOver=false;
}

Game::~Game()
{
    //dtor
}

void Game::setGameOver(bool a){
    gameOver = a;
}

bool Game::getGameOver()const{
    return gameOver;
}

void Game::pressA(){
    Vector2D* pos = new Vector2D;
    *pos = myHelicopter.getPos();
    if(pos->getX()-1<0){
            myHelicopter.setPos(*pos);
    }else {
        pos->setX(pos->getX() - 1);
        myHelicopter.setPos(*pos);
    }
    delete pos;
}

void Game::pressW(){
    Vector2D* pos = new Vector2D;
    *pos = myHelicopter.getPos();
    if(pos->getY()-1<0){
            myHelicopter.setPos(*pos);
    }else {
        pos->setY(pos->getY() - 1);
        myHelicopter.setPos(*pos);
    }
    delete pos;
}

void Game::pressD(){
    Vector2D* pos = new Vector2D;
    *pos = myHelicopter.getPos();
    if(pos->getX()+1>1000){
        myHelicopter.setPos(*pos);
    }else {
        pos->setX(pos->getX() + 1);
        myHelicopter.setPos(*pos);
    }
    delete pos;
}

void Game::pressS(){
    Vector2D* pos = new Vector2D;
    *pos = myHelicopter.getPos();
    if(pos->getY()+1>600){
            myHelicopter.setPos(*pos);
    }else {
        pos->setY(pos->getY() + 1);
        myHelicopter.setPos(*pos);
    }
    delete pos;
}

void Game::pressSpace(){
    myHelicopter.fire();
}

void Game::verifyPosition(int j, bool & li){
Vector2D En;
    for(int i = 0;i<10;i++){
        En=myEnemy[j].getPos();
        if(myHelicopter.getFired(i)){
            if(En.getX()<=myHelicopter.getHelicopterMissle(i).getMissleP().getX()+30){
                if(En.getX()+100>=myHelicopter.getHelicopterMissle(i).getMissleP().getX())
                    if(En.getY()<=myHelicopter.getHelicopterMissle(i).getMissleP().getY()+10){
                        if(En.getY()+100>=myHelicopter.getHelicopterMissle(i).getMissleP().getY()){
                            isHit(-1,j, li);
                            myHelicopter.setMissleFalse(i);
                            myEnemy[j].setRandomPos();

                        }
                    }
                }
            }
        }

    if(myEnemy[j].getIsFired()){
        if(myHelicopter.getPos().getX()+100 >= myEnemy[j].getEnemyMissle().getMissleP().getX() && myHelicopter.getPos().getX() <= myEnemy[j].getEnemyMissle().getMissleP().getX()){
            if(myHelicopter.getPos().getY()<=myEnemy[j].getEnemyMissle().getMissleP().getY() && myHelicopter.getPos().getY()+100>=myEnemy[j].getEnemyMissle().getMissleP().getY()+50){
                isHit(1,j,li);
                myEnemy[j].setIsFired(false);

            }
        }
    }

    // test if the helicopter touches the enemy
    if(myHelicopter.getPos().getX()+100 >= myEnemy[j].getPos().getX()
       && myHelicopter.getPos().getX() <= myEnemy[j].getPos().getX()
       && myHelicopter.getPos().getY() <=myEnemy[j].getPos().getY()
       && myHelicopter.getPos().getY()+100 >=myEnemy[j].getPos().getY()) {
        isHit(-1,j, li);
        isHit(1,j, li);
        myEnemy[j].setIsAlive(false);
        myEnemy[j].setRandomPos();
       }
}

void Game::verifyPositionBossHeli(bool & li){

    for(int i = 0;i<10;i++){

        if(myHelicopter.getFired(i)){
            if(myBoss.getPosition().getX()<=myHelicopter.getHelicopterMissle(i).getMissleP().getX()+30){
                if(myBoss.getPosition().getX()+200>=myHelicopter.getHelicopterMissle(i).getMissleP().getX())
                    if(myBoss.getPosition().getY()<=myHelicopter.getHelicopterMissle(i).getMissleP().getY()+10){
                        if(myBoss.getPosition().getY()+200>=myHelicopter.getHelicopterMissle(i).getMissleP().getY()){
                            isHit(0,i, li);
                            myHelicopter.setMissleFalse(i);
                            myBoss.setLife(myBoss.getLife() -1);
                        }
                    }
                }
            }
            if(myBoss.getFired(i)){
                if(myHelicopter.getPos().getX()+100>=myBoss.getMissle(i).getMissleP().getX()){
                    if(myHelicopter.getPos().getX()<=myBoss.getMissle(i).getMissleP().getX()+50){
                        if(myHelicopter.getPos().getY()<=myBoss.getMissle(i).getMissleP().getY()){
                            if(myHelicopter.getPos().getY()+100>=myBoss.getMissle(i).getMissleP().getY()+50){
                                myBoss.setFiredState(i,false);
                                isHit(2,i, li);
                            }
                        }
                    }
                }
            }
        }
}



void Game::isHit(int i,int j, bool & li){
    if(i == 1){
        li= false;
        myHelicopter.setLives(myHelicopter.getLives()-1);
        if(myHelicopter.getLives()<1) gameOver = true;
    }
    if(i== -1){
        li= true;
        myHelicopter.setScore(myHelicopter.getScore()+50);
        myEnemy[j].setIsAlive(false);
    }
    if(i==0){
        //li=true;
        myBoss.setLife(myBoss.getLife()-1);
        if(myBoss.getLife()<1) {
            myHelicopter.setScore(myHelicopter.getScore()+10000);
            myBoss.setAlive(false);
        }
    }
    if(i==2){
    myHelicopter.setLives(myHelicopter.getLives()-3);
    gameOver = true;
    }

}

Boss Game::getBoss()const{
    return myBoss;
}

Helicopter Game::getHelicopter()const{
    return myHelicopter;
}

Enemy Game::getEnemy(int i)const{
    return myEnemy[i];
}



void Game::updateHeliMisslePos(int i){
    myHelicopter.updateHeliMissleP( i);
}

void Game::updateBossMisslePos(int i){
    myBoss.updateMisslePosition(i);
}

void Game::autoPlayBoss(int curent){
    if(myBoss.getAlive()){
        // si le boss a encore de vie il fait de mouvements sur l'ecran et aussi lance des projectiles
        myBoss.mouvement();
        myBoss.fire(curent);
        } else {

            Vector2D * posB = new Vector2D;
            posB->setX(1500);
            posB->setY(0);
            myBoss.setPosition(*posB);
            delete posB;
        }
}


void Game::autoPlayEnemy( int curent,int i){

    if(myEnemy[i].getIsAlive() && myEnemy[i].getPos().getX()>-100 ){
        //in dependenta de nr de enemi de scazut timpul de asteptare
         myEnemy[i].movement();
        if(myEnemy[i].getPos().getY()<=myHelicopter.getPos().getY()+100 && myEnemy[i].getPos().getY()+100>=myHelicopter.getPos().getY() && myEnemy[i].getPos().getX()>=myHelicopter.getPos().getX()+100){
            //daca egal atunci plaseaza projectile
            myEnemy[i].fire(curent);
            } else {
             // daca nu atunci misca cu 1 proiectilul
             if(myEnemy[i].getIsFired()){
                myEnemy[i].fire(curent);
                }
            }
        }//se poate de facut mai bine prin pointeri :))
        else if(!myEnemy[i].getIsAlive() || myEnemy[i].getPos().getX()<-99 || myEnemy[i].getPos().getY()<-99 || myEnemy[i].getPos().getY()>700){
                myEnemy[i].setRandomPos();
    }

}

void Game::moveLastEnemyAlive(int curent){
   for(int i = 0 ; i < 10; i++){
    if(myEnemy[i].getIsAlive()){

        Vector2D p;
        p.setX(1500);
        p.setY(0);
        myEnemy[i].setPos(p);
        cout << myEnemy[i].getIsFired()<<endl;
        myEnemy[i].getEnemyMissle().setMissleP(p);
        myEnemy[i].setIsFired(false);
    }
   }
}


bool Game::enemyAlive(){
    int i = 0;
    while(!myEnemy[i].getIsAlive() && i<10){
        i++;
    }
    if(i<10)return true;
    else return false;
}

void Game::autoPlayMultipleEnemy( int curent,unsigned int score){
    if(curent % 5 == 0){
    if(score >= 0 && score<200){
        autoPlayEnemy(curent,0);
    } else if(score >= 200 && score<700){
        for(int i = 0;i<3;i++){
                autoPlayEnemy(curent,i);
            }
    }/*else if(score >= 700 && score<1800){
        for(int i = 0;i<5;i++){
                autoPlayEnemy(curent,i);
            }
        }
        else if(score >= 1800 && score<7000){
        for(int i = 0;i<7;i++){
                autoPlayEnemy(curent,i);
            }
        }else if(score >= 7000 && score<15000){
        for(int i = 0;i<10;i++){
                autoPlayEnemy(curent,i);
            }
        }*/
        else if(score>= 700 && score < 30000){
            autoPlayBoss(curent);
            if(enemyAlive())
            moveLastEnemyAlive(curent);}
    }


}

