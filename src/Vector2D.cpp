#include "Vector2D.h"

Vector2D::Vector2D()
{
    x=0;
    y=0;
}

Vector2D::Vector2D(int a=0,int b=0){
    x=a;
    y=b;
}

Vector2D::~Vector2D()
{
    //dtor
}

int Vector2D::getX() const{
    return this->x;
}

int Vector2D::getY() const{
    return this->y;
}

void Vector2D::setX(int a){
    x=a;
}

void Vector2D::setY(int b){
    y=b;
}

Vector2D operator+(const Vector2D& a,const Vector2D& b){
    Vector2D add(0.0,0.0);
    add.setX(a.getX()+b.getX());
    add.setY(a.getY()+b.getY());

    return add;

}

Vector2D operator*(const float lambda , const  Vector2D& b){
    Vector2D mult(0,0);
    mult.setX(lambda*b.getX());
    mult.setY(lambda*b.getY());
    return mult;
}

bool operator==(const Vector2D& a, const Vector2D& b){
    if(a.getX()==b.getX() && a.getY() == b.getY()){
        return true;
    }
    return false;
}
