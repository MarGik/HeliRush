#ifndef VECTOR2D_H
#define VECTOR2D_H


class Vector2D
{
    public:
    /*! Constructeur par default*/
        Vector2D();
    /*! Desctructeur par default*/
        ~Vector2D();
    /*! Constructeur  x=a et y=b*/
        Vector2D(int a,int b);
        int getX() const;
        int getY() const;
        void setX(int a);
        void setY(int b);

    protected:

    private:
    /** les coordones de vecteur */
    int x,y;
};


        Vector2D operator+ ( const Vector2D& a, const Vector2D& b);

        Vector2D operator* (const float lambda , const Vector2D& b);

        bool operator==(const Vector2D& a, const Vector2D& b);

#endif // VECTOR2D_H
