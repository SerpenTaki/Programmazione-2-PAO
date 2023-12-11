#ifdef CONTENITORE_H
#define CONTENITORE_H

class contenitore{
friend class iteratore; //dichiarazione di amicizia
private:
    class nodo{
    public: //per convenienza nessuna influenza esterna
        int info;
        nodo* next;
        nodo(int x, nodo* p): info(x), next(p) {}
    };
    nodo* first; //puntatore al primo nodo della lista
public:
    class iteratore{
    friend class contenitore;//garantiamo l'accesso alla classe contenitore amica di iteratore
    private:
        contenitore::nodo* punt; // per amicizia
    public:
        bool operator==(iteratore i) const{
            return punt == i.punt;
        }
        iteratore& operator++() { //operator ++ postfisso
            if (punt) punt = punt->next; //potrebbe essere NULL
            return *this;
        }
    };
    /*la dichiarazione della classe iteratore deve precedere le dichiarazioni metodi
    che usano tale tipo nella loro segnatura*/
    contenitore(): first(0) {}
    void aggiungi_in_testa(int x) {first = new nodo(x,first);}
    iteratore begin() const;
    iteratore end() const;
    int& operator[] (iteratore) const; //non è con l'accesso che lo modifico
}

contenitore::iteratore contenitore::begin() const{
    iteratore aux;
    aux.punt = first; //per amicizia
    return aux;
}

contenitore::iteratore contenitore::end() const {
    
}
#endif