#ifndef RAZ_H
#define RAZ_H
#include <iostream>

class Raz{

    private:

    int numeratore;
    int denominatore;   // denominatore diverso da 0
    // rappresentazione multiple per piu razionali 

    public:
    // convertitore inplicito da int n a Raz: n viene convertito a tipo Raz
    Raz(int n = 0, int d = 1) : numeratore(n), denominatore(d == 0 ? 1 : d) {}

    Raz inverso() const{ // se si inverte 0 si ottiene un random
        return Raz(denominatore, numeratore);
    }

    // convertitore Raz double
    operator double() const{
        return (numeratore * 1.0) / (denominatore * 1.0);
    }

    Raz operator+(const Raz &r) const{
        return Raz(numeratore * r.denominatore + denominatore * r.numeratore, denominatore * r.denominatore);
        // n1/d1 + n2/d2 = ( n1*d2 + n2 * d1)/d1*d2
    }

    // Raz operator+(const int &r) const{
    //     return Raz(numeratore + denominatore * r, denominatore * r);
    //     // n1/d1 + n2/d2 = ( n1 + n2 * d1)/d1
    // }

    Raz operator*(const Raz &r) const{
        return Raz(numeratore * r.numeratore, denominatore * r.denominatore);
    }

    Raz operator++(int){
        Raz aux(*this);
        // numeratore += denominatore ;
        // 2 scelte
        *this = *this + Raz(1);
        // oppure
        // *this = this->operator+(1);

        return aux;
    } // ++ postfisso

    Raz& operator++() {
        numeratore += denominatore ;
        return *this;
    } // ++ prefisso

    bool operator==(const Raz& r) const {
        // moltiplicazione tra interi (si perde precisione convertendo a double)
        return numeratore*r.denominatore == r.numeratore*denominatore;
    }

    static Raz unTerzo() {
        return Raz(1,3);
    }

};


std::ostream& operator<<(std::ostream &o, const Raz& r);


#endif