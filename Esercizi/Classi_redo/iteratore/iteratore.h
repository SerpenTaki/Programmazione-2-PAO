#ifdef ITERATORE_H
#define ITERATORE_H

class iteratore{
private:
    contenitore::nodo* punt; //nodo puntato dall'iteratore
public:
    bool operator==(iteratore i) const{
        return punt == i.punt;
    }
    iteratore& operator++() { //operator ++ postfisso
        if (punt) punt = punt->next; //potrebbe essere NULL
        return *this;
    }
};

#endif