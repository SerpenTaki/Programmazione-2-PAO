/*Definire una classe Vettore i cui oggetti rappresentano array di interi.
Vettore deve includere un costruttore di default, una operazione di concatenazione che restituisce
un nuove vettore v1+v2, una operazione di append v1.append(v2), l'overloading dell'uguaglianza,
dell'operatore di output e dell'operatore di output e dell'operatore di indicizzazione.
Deve inoltre includere il costruttore di copia profonda, l'assegnazione profonda e
 la distruzione profonda.*/

#include<iostream>

class Vettore{
    friend Vettore operator+(const Vettore&, const Vettore&); //Le dichiarazioni di amicizia si mettono appena sotto la classe
   // friend bool operator==(const Vettore& v1, const Vettore& v2);

private:
    int* a;
    unsigned int size;
    // Vettore vuoto IFF a==nullptr & size==0
    int* copia() const {
        int* aux = nullptr;
        if(size>0){
            aux = new int(size);
            for(unsigned int j=0; j<size; ++j) aux[j]=a[j];
        }
        return aux;
    }
public:
    //Vettore():a(nullptr), size(0) {}
    // conversione da unsigned int => Vettore
    Vettore(int val=0, unsigned int s=0): a(s==0 ? nullptr : new int[s]), size(s){
        for(unsigned int k=0; k<size; ++k) a[k]=val;
    }
    Vettore& operator=(const Vettore& v) {
        if(this != &v){
            delete[] a; //senza questa invocazione => GARBAGE
            a = v.copia();
            size = v.size;
        }
        return *this;
    }
    Vettore(const Vettore& v): a(v.copia()), size(v.size) {}
    ~Vettore(){ //Regola del 3 rimane solamente il distruttore
        delete[] a;
    }

    unsigned int getSize() const{
        return size;
    }

    void append(const Vettore& v){
        *this = *this + v;
    }

    int& operator[](unsigned int i) const{
        // nessun controllo per i nell'essere dentro il bound
        return a[i];
    }
    
};

Vettore operator+(const Vettore& v1, const Vettore& v2){
    Vettore v(v1.size+v2.size); //non dicendo nulla lui lo inizializza a zero
    for(unsigned int j=0; j<v.size; ++j){
        if(j<v1.size) v.a[j]=v1.a[j];
        else v.a[j] = v2.a[j-v1.size];
    }
    return v;
}

bool operator==(const Vettore& v1, const Vettore& v2){
    if(v1.getSize() != v2.getSize()) return false; //v1.size != v2.size
    // v1.size == v2.size
    bool eq = true;
    for(unsigned int i = 0; i < v1.getSize() && eq; ++i)
        eq = v1[i] == v2[i]; //invoco Vettore::operator[]
    return eq;
}
//#include<iostream>

std::ostream& operator<<(std::ostream& os, const Vettore& v){
    for(unsigned j=0; j<v.getSize(); ++j) os << v[j] << ' ';
    return os;
}

int main(){
    Vettore v1(4), v2(3,2), v3(5,-3);
    v1 = v2+v3;
    v2.append(v2);
    v3.append(v1);
    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v3 << std::endl;
}