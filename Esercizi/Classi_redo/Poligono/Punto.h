#ifndef PUNTO_H
#define PUNTO_H
#include <iostream>
#include <math.h>

class punto {
private:
    double x, y;
public:
    double getX() const; // coordinata x
    double getY() const; // coordinata y
    // metodo statico che calcola la distanza tra 2 punti
    static double lung(const punto& p1, const punto& p2);
};


class poligono{
protected:
    int nvertici;
    punto* pp; //array dinamico di punti
public:
    //non è disponibile il costruttore di default
    poligono(int, const punto v[]); //v array ordinato di vertici
    ~poligono(); //distruttore profondo
    poligono(const poligono&);
    poligono& operator=(const poligono&); //assegnazione profonda
    double perimetro() const;
};



class rettangolo : public poligono{
public:
    rettangolo(const punto v[]) : poligono(4, v) {}
    double perimetro() const; //ridefinizione
    double area() const; //nuovo metodo
};

double rettangolo::perimetro() const{
    double base = punto::lung(pp[1], pp[0]);
    double altezza = punto::lung(pp[2], pp[1]);
    return (base * altezza);
}

class quadrato : public rettangolo{
public:
    quadrato(const punto v[]) : rettangolo(v) {}
    double perimetro() const; //ridefinizione
    double area() const; //ridefinizione
};

double quadrato::perimetro() const{
    double lato = punto::lung(pp[1], pp[0]);
    return (lato * 4);
}

double quadrato::area() const{
    double lato = punto::lung(pp[1], pp[0]);
    return (lato * lato);
}

class triangolo : public poligono{
public:
    triangolo(const punto v[]) : poligono(3, v) {}
    double area() const; //nuovo metodo
};

double triangolo::area() const{ //usa la formula di Erone
    double p = perimetro()/2;
    double a = punto::lung(pp[1], pp[0]), b=punto::lung(pp[2], pp[1]), c=punto::lung(pp[0],pp[2]);
    return std::sqrt(p*(p-a)*(p-b)*(p-c));
}

#endif