#include "Nodo.h"

template <class T>
Nodo<T>* AlbBinRic<T>::Find(T v) const{
    return FindRic(radice, v);
}

template <class T>
Nodo<T>* AlbBinRic<T>::FindRic(Nodo<T>* x, T v){
    if(!x) return x; //caso base: albero vuoto
    if(x->info == v) return x; //caso base: v è nella radice
    if (v < x->info) //cerca ricorsivamente nel sottoalbero sinistro
        return FindRic(x->sinistro, v);
    else
        return FindRic(x->destro, v);
}

/*
L'idea dell'algoritmo che calcola il valore massimo di un albero binario di ricerca è la seguente:
- Il valore massimo è memorizzato nella foglia più a destra
*/

template <class T>
Nodo<T>* AlbBinRic<T>::Massimo() const{
    if (!radice) return 0;
    return MassimoRic(radice);
}

template <class T>
Nodo<T>* AlbBinRic<T>::MassimoRic(Nodo<T>* x){
    if (!(x->destro)) return x;
    else return MassimoRic(x->destro);
}

// Naturalmente il minimo è duale al massimo

template <class T>
Nodo<T>* AlbBinRic<T>::Minimo() const{
    if (!radice) return x;
    else return MinimoRic(radice);
}

template <class T>
Nodo<T>* AlbBinRic<T>::MinimoRic(Nodo<T>* x){
    if (!(x->sinistro)) return x;
    else return MinimoRic(x->sinistro);
}


/*
L'idea dell'algoritmo che calcola il successore è la seguente:
-> se il nodo puntato da x ha sottoalbero destro x_d allora il successore di x è il minimo di x_d
-> se il sottoalbero destro di x è vuoto allora il successore di x è antenato di x più giovane di cui x è discendente sinistro
*/

template <class T>
Nodo<T>* AlbBinRic<T>::Succ(Nodo<T>* x) const{
    if (!x) return 0;
    if (x->destro) return MinimoRic(x->destro);
    //caso x->destro == 0
    while(x->padre && x->padre->destro == x) x = x->padre;
    return x->padre;
}

template <class T>
Nodo<T>* AlbBinRic<T>::Pred(Nodo<T>* x) const{
    if (!x) return 0;
    if (x->sinistro) return MassimoRic(x->sinistro);
    while(x->padre && x->padre->sinistro == x) x = x->padre;
    return x->padre;
}

/*
L'idea dell'algoritmo per inserire un valore v nell'albero T è la seguente:
- Se T è vuoto inserisco v come radice, altrimenti
- Se T=(r,Ts,Td) e v<r allora inserisco v in Ts, mentre se v>r allora inserisco v in Td
*/

template <class T>
void AlbBinRic<T>::Insert(T v) {
    if (!radice) radice = new Nodo<T>(v);
    else InsertRic(radice, v);
}

template <class T>
void AlbBinRic<T>::InsertRic(Nodo<T>* x, T v){
    if(v < x->info)
        if (x->sinistro == 0) x->sinistro = new Nodo<T>(v, x);
        else InsertRic(x->sinistro, v);
    else
        if (x->destro == 0) x->destro = new Nodo<T>(v,x);
        else InsertRic(x->destro, v);
}

template <class T>
ostream& operator<<(ostream& os, const AlbBinRic<T>& A){
    os << A.radice << endl; //stampa di Nodo<T>*
    return os;
}

