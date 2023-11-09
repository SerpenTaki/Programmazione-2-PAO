#include "bolletta.hpp"

bolletta::nodo::nodo() : next(0) {}

bolletta::nodo::nodo(const telefonata& t, nodo* s) : info(t), next(s) {}

bolletta::bolletta(): first(0) {}

bolletta::bolletta(const bolletta& b): first(copia(b.first)) {}

bool bolletta::Vuota()const {
    return first == 0;
}

void bolletta::Aggiungi_Telefonata(const telefonata& t){
    first = new nodo(t, first);
}

void bolletta::Togli_Telefonata(const telefonata& t){
    nodo *p = first , *prec = nullptr;

    // if(p) = if(p != nullptr) == if( p != 0) significa se p non vuoto
    while (p && !(p->info == t) )
    {
        prec = p;
        p = p->next;

    }
    if (p)  // non vuoto
    {
        if (prec == nullptr)    // se volgio togliere il primo nodo della lista
        {
            first = p->next;
        }else{                  // se non è il primo nodo della lista
            prec->next = p->next;       // prec next punta al nodo successivo cosi che p venga tolto dalla lista
        }
        delete p;        // BISOGNA cancellare il nodo p altrimenti errore gravissimo(memoria non deallocata)
    }
}

// ritorna una telefonata della lista e la cancella dalla lista
telefonata bolletta::Estrai_Una(){
    //PRECONDIZIONE : bolletta non vuota
    nodo* p = first;
    first = first->next;
    telefonata aux = p->info;
    delete p;
    return aux;
}

int bolletta::size() const{
    int count = 0;
    nodo *p = first;

    while (p)
    {
        count++;
        p = p->next;
    }
        return count;
}

void bolletta::print() const{
    nodo* p = first;
    int i = 1;
    while (p)
    {
        std::cout << i << ") " << p->info << std::endl;
        p = p->next;
        i++;
    }
}

// IMPLEMENTAZIONE COPIA DISTRUGGI ITERATIVA (piu efficente)

bolletta::nodo* bolletta::copia(nodo* p) {
    if(!p) return 0;        // nel caso sia vuota 
    nodo *primo = new nodo(p->info, 0);      //  allocazione del primo nodo alla lista linkata
    nodo *q = primo;

    while (p->next) // non è vuota
    {
        p = p->next;
        q->next = new nodo(p->info, 0);
        q = q->next;
    }
    return primo;

}

void bolletta::distruggi(nodo* p){
    if (p !=nullptr)
    {
        nodo *q = p;
        while (p != nullptr)
        {
            p = p->next;
            delete q;
            q = p;
        }
    }   
}

// IMPLEMENTAZIONE COPIA DISTRUGGI RICORSIVA (meno efficente, più elegante )

// bolletta::nodo* bolletta::copia(nodo* p) {
//     if (!p) return 0;
    
//     return new nodo(p->info, copia(p->next));    
// }

// void bolletta::distruggi(nodo* p){
//     if (p)
//     {
//         distruggi(p->next);
//         delete p;
//     }
    
// }


bolletta& bolletta::operator=(const bolletta& b){
    if (this != &b) // se sto cercando di eguagliare due bollette con la stessa cella di memoria
    {
        distruggi(first);
        first =copia(b.first);
    }
    return *this;
}


