#include"Impiegato.h"
#include"Impiegato.cpp"
#include <iostream>

using std::cout;
using std::endl;

int main() {
    Dirigente d("Paperino", 4000);
    Rappresentante r("Topolino", 1000, 3, 250);
    LavoratoreOre l("Pluto", 15, 170);
    stampaStipendio(&b); stampaStipendio(&r); stampaStipendio(&l);
    
}