#include<iostream>
#include "Nodo.h"
using std::cout;
using std::endl;

int main(){
    AlbBinRic<int> a;
    a.Insert(3); a.Insert(2); a.Insert(3);
    a.Insert(1); a.Insert(6); a.Insert(5);
    cout << a;

    cout << "minimo: " << AlbBinRic<int>::Valore(a.Minimo()) << endl; // minimo: 1
    cout << "massimo: " << AlbBinRic<int>::Valore(a.Massimo()) << endl; // massimo: 6

    cout << "successore minimo: " << AlbBinRic<int>::Valore(a.Succ(a.Minimo())) << endl; //successore minimo: 2
    cout << "predecessore massimo: " << AlbBinRic<int>::Valore(a.Pred(a.Massimo())) << endl; // predecessore massimo: 5

    if(a.Find(2)) cout << "il valore " << 2 << " è presente" << endl; // Il valore 2 è presente
}