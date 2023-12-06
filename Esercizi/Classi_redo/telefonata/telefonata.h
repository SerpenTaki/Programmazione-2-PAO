//file telefonata.h
#ifndef TELEFONATA_H
#define TELEFONATA_H
#include <iostream>
#include "orario.cpp"

using std::ostream;

class telefonata {
public:
    telefonata(orario, orario, int);
    telefonata();
    orario Inizio() const;
    orario Fine() const;
    int Numero() const;

    bool operator==(const telefonata&) const; //const perchè non c'è modifica all'oggetto di invocazione
private:
    orario inizio, fine; //relazione has-a
    const int numero;
};


#endif