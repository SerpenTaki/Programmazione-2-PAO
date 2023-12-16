#ifndef NODO_H
#define NODO_H
#include<iostream>
using std::ostream;
//dichiarazione incompleta di AlbBinRic
template <class T> class Nodo;

//dichiarazione incompleta di operator<<
template <class T>
ostream& operator<<(ostream&, Nodo<T>*);

template <class T>
class Nodo{
    friend class AlbBinRic<T>; //classe friend associata
    //funzione friend associata
    friend ostream& operator<< <T>(ostream&, Nodo<T>*);
private:
    T info;
    //notare il costruttore privato
    Nodo *sinistro, *destro, *padre;
    Nodo(const T& v, Nodo* p=0, Nodo* s=0, Nodo* d=0) : info(v), padre(p), sinistro(s), destro(d) {}
};

template <class T>
ostream& operator<<(ostream& os, Nodo<T>* p){
    if(!p) os << '@'; //caso base
    else os << "(" << p->info << "," << p->sinistro << "," << p->destro << ")"; //passo ricorsivo
    return os;
}

//dichiarazione di operator<<
template<class T>
ostream& operator<<(ostream&, AlbBinRic<T>&);

template <class T>
class AlbBinRic{
friend ostream& operator<< <T>(ostream&, const AlbBinRic<T>&);
public:
    AlbBinRic() : radice(0) {}
    Nodo<T>* Find(T) const;
    Nodo<T>* Minimo() const;
    Nodo<T>* Massimo() const;
    Nodo<T>* Succ(Nodo<T>*) const;
    Nodo<T>* Pred(Nodo<T>*) const;
    void Insert(T);
    static T Valore(Nodo<T>* p) {return p->info;}
private:
    Nodo<T>* radice; //puntatore alla radice
    //metodi privati di utilità
    static Nodo<T>* FindRic(Nodo<T>*, T);
    static Nodo<T>* MinimoRic(Nodo<T>*);
    static Nodo<T>* MassimoRic(Nodo<T>*);
    static void InsertRic(Nodo<T>*, T);
};

#endif