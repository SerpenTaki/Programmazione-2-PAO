#ifndef TELEFONATA_H
#define TELEFONATA_H
#include <iostream>

#include "../classe_orario/orario.hpp"

class telefonata{
    private:
    orario inizio, fine;        //relazione has-a
    std::string numero;
    public:

    telefonata(orario, orario, std::string);
    telefonata();
    orario Inizio() const;
    orario Fine()const;
    std::string Numero() const;
    bool operator ==(const telefonata &) const;

};

std::ostream& operator<<(std::ostream&, const telefonata&);


#endif