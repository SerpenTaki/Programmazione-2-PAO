#include "orario_handle.h"

class orario_handle::orario_rappr{
public:
    int sec;
}; //basta il costruttore di default standard

orario_handle::orario_handle(int o, int m, int s) : punt(new orario_rappr){
    if(o < 0 || o > 24 || m < 0 || m > 60 || s < 0 || s > 60)
        punt->sec = 0;
    else
        punt->sec = o*3600 + m*60 + s;
}

int orario_handle::Ore() const { return punt->sec / 3600; }

int orario_handle::Minuti() const {
    return (punt->sec - (punt->sec / 3600)*3600) / 60;
}

int orario_handle::Secondi() const { return punt->sec % 60; }

void orario_handle::AvanzaUnOra() {
    punt->sec = (punt->sec + 3600) % 86400;
}

ostream& operator<<(ostream& os, const orario_handle& t){
    return os << t.Ore() << ':' << t.Minuti() << ':' << t.Secondi();
}