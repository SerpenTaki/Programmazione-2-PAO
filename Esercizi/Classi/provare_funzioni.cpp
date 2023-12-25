#include<iostream>


using std::cout;
using std::endl;

class B {
protected:
    int x;
public:
    B() : x(2) {}
    void print() { cout << x << endl; }
};

class D : public B{
private:
    double x;
public:
    D() : x(3.14) {}
    void print() { cout << B::x << endl; }
    void printAll() {cout << B::x << ' ' << x << endl;}
};

int main(){
    B b; D d;
    b.print();
    d.print();
    d.printAll();
}