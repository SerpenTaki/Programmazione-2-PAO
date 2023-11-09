#ifndef BOLETTA_H
#define BOLLETTA_H
#include "../classe_telefonata/telefonata.hpp"
#include <iostream>

class bolletta{
    public:
    bolletta();
    bolletta(const bolletta &);
    bool Vuota() const;
    void Aggiungi_Telefonata(const telefonata&);
    void Togli_Telefonata(const telefonata&);
    telefonata Estrai_Una();


    int size() const;
    void print()const;


    // senza definizione di operatore= la copia sarebbe una shallow copy e non una deep copy
    bolletta& operator=(const bolletta& y);

    private:

    // è possibile annidare altri tipi allinterno di tipi (inner class)
    // vogliamo che al di fuori di bolletta non sia accessibile il tipo nodo

    class nodo{
        public:     // viene protetto comunque dal private di bolletta
            nodo();
            nodo(const telefonata&, nodo*);
            telefonata info;
            nodo* next;
    };
    nodo* first;

    static nodo* copia(nodo*);
    static void distruggi(nodo*);

};

#endif