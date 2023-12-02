#include <iostream>

using std::cout;
using std::endl;

class C {
    int dato; //privato
public:
    C(int); //costruttore ad un argomento NON DEFAULT
    static int conta; //campo dati statico pubblico
};

int C::conta = 0; //inizializzazione campo dati statico

C::C(int n) { conta++; dato=n;} //definizione costruttore

int main(){
    C c1(1), c2(2), c3(3), c4(4), c5(5);
    cout << C::conta; //stampa 5
}