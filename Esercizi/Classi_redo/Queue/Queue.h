#ifdef QUEUE_H
#define QUEUE_H

template <class T>
class Queue {
public:
    Queue();//notare la sintassi è Queue non Queue<T>
    bool is_empty() const;  //testa se la coda è vuota
    void add(const T&);     //aggiunge un item alla coda 
    T remove();          //rimuove un item alla coda
    ~Queue();
private: 
    //Notare la sintassi è QueueItem<T> e non QueueItem
    QueueItem<T>* primo;
    QueueItem<T>* ultimo; 
};

definizione esterna
template <class T>
Queue<T>::Queue() : primo(0) , ultimo(0) {}

//SEMPRE NEL QUEUE.h
template <class T>
bool Queue<T>::is_empty() const { return (primo == 0); }

template <class T>
void Queue<T>::add(const T& val) {
    QueueItem<T>* p = new QueueItem<T>(val);
    if(is_empty())
        primo = ultimo = p;
    else { //aggiunge in coda
        ultimo->next = p;
        ultimo = p;
    }
}

#include<iostream>
using std::cerr;
using std::endl;

template <class T>
T Queue<T>::remove() {
    if (is_empty()){
        cerr << "remove() su coda vuota" << endl;
        exit(1); //termina subito l'esecuzione e quell'uno è un messaggio di anomalia logica (int di ritorno del numero)
    }
    QueueItem<T>* p = primo;
    primo = primo->next;
    T aux = p->info;
    delete p;
    return aux;
}

template <class T>
Queue<T>::~Queue() {
    while(!is_empty()) remove();
}
#endif