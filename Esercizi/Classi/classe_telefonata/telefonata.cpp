#include "telefonata.hpp"

telefonata::telefonata(orario i, orario f, std::string n) : inizio(i), fine(f), numero(n) {
    // inizio = i;
    // fine = f;
    // numero = n;
}   

telefonata::telefonata() : numero(0) {
    // numero = 0;
}   // non serva defire i campi dati orario perche vengono costruiti di default

orario telefonata::Inizio() const{ return inizio;}

orario telefonata::Fine() const { return fine;}

std::string telefonata::Numero() const { return numero;}

bool telefonata::operator==(const telefonata& t) const {
    return (inizio == t.inizio && fine == t.fine && numero == t.numero); 
}

std::ostream& operator<<(std::ostream& s, const telefonata& t){
    return s << "INIZIO " << t.Inizio() << " FINE " << t.Fine() <<  " NUMERO CHIAMATO " << t.Numero();
}