#include<iostream>
using std::cout;
using std::endl;

class B {
public:
	virtual void m(int x = 0) {cout << "B::m " << endl;}
};

class D : public B{
public:
	//è un overriding di B::m
	virtual void m(int x) {cout << "D::m " << endl;} //perdo il valore di default

	//Legale è un nuovo metodo in D e non un overriding di B::m
	virtual void m() {cout << "D::m() " << endl; }
};

int main(){
	B* p = new D;
	D* q = new D;
	p->m(2); //Stampa D::m e non B::m
	p->m(); //stampa D::m e non D::m()
	q->m(); //stampa D::m() e non D::m
}