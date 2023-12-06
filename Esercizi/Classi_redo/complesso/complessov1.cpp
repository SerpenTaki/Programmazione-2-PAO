#include <iostream>

//rappresentazione reale immaginario
class complesso {
private:
    double re, im;
public:
    void iniz_compl(double, double);
    double reale();
    double immag();
};

void complesso::iniz_compl(double r, double i) {re = r; im=i;}
double complesso::reale() {return re;}
double complesso::immag() {return im;}


#include<math.h> //libreria di funzioni matematiche
//rappresentazione polare
class complesso2{
private:
    double mod, arg;
public:
    void iniz_compl2(double, double);
    double reale2();
    double immag2();
};

void complesso2::iniz_compl2(double r, double i){
    mod = sqrt(r*r + i*i); arg = atan(i/r);
}

double complesso2::reale2() {return mod*cos(arg);}
double complesso2::immag2() {return mod*sin(arg);}