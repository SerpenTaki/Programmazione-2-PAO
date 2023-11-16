/*Definire una classe Vettore i cui oggetti rappresentano array di interi.
Vettore deve includere un costruttore di default, una operazione di concatenazione che restituisce
un nuove vettore v1+v2, una operazione di append v1.append(v2), l'overloading dell'uguaglianza,
dell'operatore di output e dell'operatore di output e dell'operatore di indicizzazione.
Deve inoltre includere il costruttore di copia profonda, l'assegnazione profonda e la distruzione profonda.*/
#include<iostream>

class Vettore{
private:
    int* a;
    unsigned int size;
    // Vettore vuoto IFF a==nullptr & size==0
public:
    //Vettore():a(nullptr), size(0) {}
    Vettore(int val=0, unsigned int s=0): a(s==0 ? nullptr : new int[s]), size(s){
        for(unsigned int k=0; k<size; ++k) a[k]=val;
    }
};


int main(){
    Vettore v1(4), v2(3,2), v3(5,-3);
    v1 = v2+v3;
    v2.append(v2);
    v3.append(v1);
    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v3 << std::endl;
}