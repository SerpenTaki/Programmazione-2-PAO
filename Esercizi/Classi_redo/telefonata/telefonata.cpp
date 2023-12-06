//file telefonata.cpp
#include "telefonata.h"

telefonata::telefonata(orario i, orario f, int n)
                        : inizio(i), fine(f), numero(n) {}

telefonata::telefonata() : numero(0) {}
//attenzione tutti gli altri campi di tipo orario sono inizializzati vengono inizializzati tramite il costruttore di default

orario telefonata::Inizio() const { return inizio; }

orario telefonata::Fine() const { return fine; }

int telefonata::Numero() const { return numero; }

bool telefonata::operator==(const telefonata& t) const {
    return inizio == t.inizio && fine == t.fine && numero == t.numero;
}

ostream& operator<<(ostream& s, const telefonata& t) {
    return s << "INIZIO " << t.Inizio() << " FINE " << t.Fine() << " NUMERO CHIAMATO " << t.Numero();
}