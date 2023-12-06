#include "bolletta.h"

//otare il costruttore di default per il campo dati info
bolletta::nodo::nodo() : next(0) {}

bolletta::nodo::nodo(const telefonata&t, nodo* s) : info(t), next(s) {};

bool bolletta::Vuota() const {return first == 0; }

void bolletta::Aggiungi_Telefonata(telefonata t) {
    first = new nodo(t,first); //aggiunge in testa alla lista
}

void bolletta::Togli_Telefonata(telefonata t){
    nodo* p = first, *prec = 0;
    while( p && !(p->info == t)){
        prec = p;
        p = p->next;
    } //p==0 oppure p punta al nodo da rimuovere
    if (p) {
        if(!prec) //p punta al primo nodo
            first = p->next;
        else // p punta al nodo successivo al primo
            prec->next = p->next;
        delete p; //ricordarsi di deallocare
    }
}

telefonata bolletta::Estrai_Una() {
    //PRECONDIZIONE
    nodo* p = first;
    first = first->next;
    telefonata aux = p->info; //costruttore di copia
    delete p;
    return aux;
}