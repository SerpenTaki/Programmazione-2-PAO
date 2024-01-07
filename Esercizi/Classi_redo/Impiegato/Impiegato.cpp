#include "Impiegato.h"
#include <iostream>

void stampaStipendio(Impiegato* p){
    p->print(); //chiamata polimorfa
    std::cout << " in questo mese ha guadagnato " << p->stipendio() << "Euro.\n"; //chiamata polimorfa
}