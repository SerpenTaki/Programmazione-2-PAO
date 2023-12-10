
#include "bolletta.h"
#include "telefonata.h"
#include "orario.h"

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

bolletta& bolletta::operator=(const bolletta& b){
    if(this != &b) { //operator != tra puntatori
        distruggi(first);
        first = copia(b.first);
    }
    return *this;
}

telefonata bolletta::Estrai_Una() {
    //PRECONDIZIONE
    nodo* p = first;
    first = first->next;
    telefonata aux = p->info; //costruttore di copia
    delete p;
    return aux;
}

bolletta::nodo* bolletta::copia(nodo* p){
    if(!p) return 0;
    nodo* primo = new nodo;
    //Invocazione del costruttore di default di nodo
    primo->info = p->info; //primo punta al primo nodo della copia della lista
    nodo* q = primo; //q punta all'ultimo nodo della lista finora copiata
    while (p->next){
        q->next = new nodo;
        p = p->next;
        q = q->next;
        q->info = p->info;
    }
    q->next = 0;
    return primo;
}

bolletta::nodo* bolletta::distruggi(nodo* p){

    //scorro tutta la lista deallocando ogni nodo
    nodo* q;
    while(p){
        q = p;
        p = p->next;
        delete q;
    }
}


//VERSIONI RICORSIVE DI COPIA E DISTRUGGI
/*
bolletta::nodo* bolletta::copia(nodo* p){
    if(!p) return 0;//caso base lista vuota
    else //Per induzione copia(p->next) è la copia della coda di p e quindi inserisco il primo nodo di p in testa alla lista copia(p->next)
    return new nodo(p->info, copia(p->next));
}

void bolletta::distruggi(nodo* p){
    //Caso Base: lista vuota, nulla da fare
    if (p){
        //passo induttivo:
        //per induzione distruggi(p->next) dealloca la coda di p e quindi
        //quindi rimane da deallocare solamente il primo nodo di p
        distruggi(p->next);
        delete p;
    }
}
*/

orario bolletta::Somma_Durate(bolletta b){
    orario durata; //costruttore di default di orario
    while (!b.Vuota()){
        //estrae dal primo nodo della lista
        telefonata t = b.Estrai_Una();
        durata = durata + t.Fine() - t.Inizio();
    } //vincolo: durata < 24 ore!
    return durata;
}