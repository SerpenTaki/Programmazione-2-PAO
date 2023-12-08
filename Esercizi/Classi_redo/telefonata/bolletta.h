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
    bolletta& operator=(const bolletta&);
private:
    class nodo {
    public:
        nodo();
        nodo(const telefonata&, nodo*);
        telefonata info;
        nodo* next;
    };
    nodo* first;
    static nodo* copia(nodo*); //nodo che devo duplicare
    static nodo* distruggi(nodo*); //nodo che devo eliminare
};
#endif