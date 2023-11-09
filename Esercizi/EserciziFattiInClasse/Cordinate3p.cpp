/*
Definire una classe Point i cui oggetti rappresentano punti nello spazio (x,y,z). Includere un costruttore di default,
un costruttore a 3 argomenti che inizializza un punto, selettori delle coordinate cartesiane, un metodo negate() che trasforma un punto nel suo negativo,
una funzione norm() che restituisce la distanza del punto dall'origine, l'overloading degli operatori di somma e di output. Separare interfaccia ed
implementazione della classe
*/
#include<iostream>
#include<math.h>
using namespace std;

//file Point.h
class Point{
private:
    double x, y, z;
public:
    // conversione da double => Point
    Point(double =0.0, double =0.0, double =0.0); //costruttore standard con 3 argomenti che sono inizializzati a 0.0
    //scrivere così per separare l'interfaccia dall'implementazione
    double getX() const;
    double getY() const; 
    double getZ() const;
    void negate();
    double norm() const;//non fa side effect perchè usa il punto in sola lettura
};

std::ostream& operator<<(std::ostream&, const Point&);

Point operator+(const Point&, const Point&);

//file Point.cpp

Point::Point(double a, double b, double c)//non c'è bisogno di ripetere i valori di default
{
    x=a; y=b; z=c;
}

double Point::getX() const{
    return x; //return  *this.x;
}

double Point::getY() const{
    return y;
}

double Point::getZ() const{
    return z;
}

void Point::negate(){
    x *= -1.0;
    y *= -1.0;
    z *= -1.0;
}

//#include<math.h>

double Point::norm() const{
    return sqrt(x*x + y*y + z*z);
}

//#include<iostream>
std::ostream& operator<<(std::ostream& os, const Point& p){
    return os << "(" << p.getX() << "," << p.getY() << "," << p.getZ() << ")";
}

Point operator+(const Point& a, const Point& b){
    return Point(a.getX()+b.getX(),a.getY()+b.getY(),a.getZ()+b.getZ());
}

int main(){
}