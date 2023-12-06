#ifndef BOLLETTA_H
#define BOLLETTA_H
#include "telefonata.h"

class bolletta {
public:
    bolletta() : first (0) {}; //definizione inline
    bool Vuota() const;
    void Aggiungi_Telefonata(telefonata);
    void Togli_Telefonata(telefonata);
    telefonata Estrai_Una();
private:
    class nodo {
    public:
        nodo();
        nodo(const telefonata&, nodo*);
        telefonata info;
        nodo* next;
    };
    nodo* first;
};
#endif