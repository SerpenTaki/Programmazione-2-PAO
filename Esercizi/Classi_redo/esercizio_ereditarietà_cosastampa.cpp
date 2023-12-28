#include<iostream>
#include<string>

using std::cout;
using std::endl;
using std::string;

class B{
public:
    virtual int f() { cout << "B::f()\n"; return 1;}
    virtual void f(string s) {cout << "B::f(string)" <<endl;}
    virtual void g() {cout << "B::g()" << endl;}
};

class D1 : public B {
public:
    //overriding di un metodo virtuale non sovraccaricato
    void g() {cout << "D1::g()" << endl;}
};

class D2 : public B {
public:
    //overriding di un metodo virtuale sovraccaricato
    int f() {cout << "D2::f()" <<endl; return 2;}
};
/*
class D3 : public B {
public:
    //NON È possibile modificare il tipo di ritorno
    void f() {cout << "D3::f()\n";} //ILLEGALE
};
*/
class D4 : public B {
public:
    //Lista di argomenti modificata:
    //è una ridefinizione e non un overriding
    int f(int) {cout << "D4::f()" << endl; return 4;}
};

int main(){
    string s = "ciao"; D1 d1; D2 d2; D4 d4;
    int x = d1.f(); //B::f()
    d1.f(s); //B::f(string)
    x = d2.f(); //D2::f() 
    //d2.f(s); //Illegale "no matching function"
    x = d4.f(1); //D4::f()
    //x= d4.f(); //Illegale
    //d4.f(s); //Illegale
    B& br = d4; //Cast implicito
    //br.f(1); //br non è di tipo D4 quindi dichiarazione illegale
    br.f(); // B::f()
    br.f(s); // B::f(string)
}