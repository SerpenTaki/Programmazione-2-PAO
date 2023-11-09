````C++
//Complesso.cpp

class complesso {
private:
	double re, im; //reale immaginario nella parte privata
public:
	void inizializza(double, double);
	double reale();
	double immag();
};

void complesso::inizializza(double r, double i)
{ re = r; im = i; }

double complesso::reale()
{ return re; }

double complesso::immag()
{ return im; }

````
````C++

//complesso2.cpp 
#include <math.h>
//rappresentazione polare: modulo mod e argomento arg

class complesso_pol{
private:
	double mod, arg;
public:
	void inizializza (double, double);
	double reale();
	double immag();
};

void complesso_pol::inizializza(double r, double i)
{ mod = sqrt(r*r + i*i); arg = atan(i/r); }

double complesso_pol::reale()
{ return mod*cos(arg); }

double complesso_pol::immag()
{ return mod*sin(arg); }

````