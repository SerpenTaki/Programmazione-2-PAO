[[Ereditarietà#Metodi virtuali]]

*Il late binding implica un overhead dinamico a run-time in termini di spazio e tempo*. Esempio fatto con un architettura basata su Intel Core i7 2,66ghz
```C++
class B{
public:
	virtual void f() {}
};

class D: public B {
public:
	void f() {/*overriding*/}
};

int main() {
	B* p = new D;
	long int i=0;
	//late binding
	for (; i<1000000000; i++) p->f(); // 2.845 sec
	//static binding
	for (; i<1000000000; i++) p->B::f();// 2.512 sec
}
```

Per ogni classe `C` che contiene almeno un metodo virtuale il compilatore crea anche una corrispondente tabella contenente gli indirizzi dei metodi virtuali di `C`(*quindi si tratta di puntatori a funzioni*) detta `vtable`. Inoltre per ogni oggetto di classe C il compilatore "*include*" anche un puntatore a funzione (detto *`vpointer`*) alla *vtable* di `C`. La selezione a run-time di quale metodo invocare in una chiamata polimorfa `p->m()`avviene seguendo tali strutture aggiuntive di puntatori.
```C++
class B{
public:
	FunctionPointer* vptr; //vpointer aggiunto dal compilatore
	virtual void m1() {}
	virtual void m2() {}
};

class D1: public B {
public:
	virtual void m1() {} //overriding 
};

class D2: public B {
public:
	virtual void m2() {} //overriding
};
```

Una **VMT** (*tabella dei metodi virtuali, tabella delle funzioni virtuali, tabella delle chiamate virtuali*) è un meccanismo utilizzato in un *linguaggio di programmazione* per supportare il *dispatch dinamico*.

Ogni volta che una classe definisce una *funzione virtuale*, la maggior parte dei compilatori aggiunge alla classe una variabile membro nascosta che punta a un array di puntatori a funzioni (*virtuali*) chiamato VTM *vtable*. Questi puntatori vengono utilizzati in fase di esecuzione per invocare le implementazioni delle funzioni appropriate, perché in fase di compilazione potrebbe non essere ancora noto se deve essere chiamata la funzione di base o una funzione derivata implementata da una classe che eredita dalla classe di base.

![[Pasted image 20231127155113.png]]

````C++
class B{
public:
	FunctionPointer* vptr; //vpointer aggiunto dal compilatore
	virtual void m0() {}
	virtual void m1() {}
	virtual void m2() {}
};

class D: public B{
public:
	virtual void m0() {} //overriding
	virtual void m2() {} //overriding
};
B* p;

p = &b;
p->m2();
//chiama la funzione all'indirizzo *((p->vptr)+2) cioè chiama B::m2()

p = &d;
p->m2();
//chiama la funzione all'indirizzo *((p->vptr)+2) cioè chiama D::m2()
````

**Back to `poligono`**

````C++
//file polv.h
#ifndef POLV_H
#define POLV_H

class punto {
private:
	double x, y;
public:
	punto(double a=0, double b=0): x(a), y(b) {}
	static double lung(const punto& p1, const punto& p2);
};

class poligono { //classe polimorfa
protected:
	int nvertici;
	punto* pp;
public:
	poligono(int n, const punto v[]);
	~poligono();
	poligono(const poligono& pol);
	poligono& operator=(const poligono& pol);
	//contratto: ritorno il perimetro del poligono di invocazione
	virtual double perimetro() const; //metodo virtuale
};
#endif
````
````C++
//file triv.h
#ifndef TRIV_H
#define TRIV_H
#include "polv.h"

class triangolo: public poligono{
public:
	triangolo(const punto v[]);
	//eredita perimetro()
	// contratto: ritorno l'area del triangolo di invocazione
	virtual double area() const; //nuovo metodo virtuale
};
#endif

//file triv.cpp
#include <iostream>
#include <math.h>
#include "triv.h"

tringolo::triangolo (const punto v[]) : poligono(3, v) {}

//formula di Erone
double triangolo::area() const{
	double a = punto::lung(pp[1], pp[0]);
	double b = punto::lung(pp[2], pp[1]);
	double c = punto::lung(pp[0], pp[2]); double p = (a + b + c)/2;
	return sqrt(p*(p-a)*(p-b)*(p-c));
}

//Contratto: stampa il perimetro del poligono *p
void stampa_perimetro(poligono* p){
	cout << "Il perimetro è " << p->perimetro() << endl; //chiamata polimorfa
}

//Contratto: stampa l'area del triangolo t
void stampa_area_triangolo(const triangolo& t){
	cout << "L'area è " << t.area() << endl; //chiamata polimorfa
}

int main(){}
````

Sia `D` una classe derivata da `B`. Consideriamo la seguente situazione:
````C++
D* pd = new D;
B* pb = pd; //pb ha tipo dinamico D*
delete pb;
````

```mermaid
classDiagram
direction RL
class sottooggettoB{
	- idCard: D-B
}
class Bstarp {
	- id: int
}
sottooggettoB "1" --o "1" Bstarp
````

## Distruttori Virtuali
*Mettendo virtual al distruttore della base diventano virtual anche quelli delle derivate, eliminando così l'oggetto in base al suo tipo dinamico*.
```
D* pd = new D;
B* pb = pd; //TD(pb) = D*
delete pb;
```
In questa situazione `delete pb;` richiama il distruttore della classe base `B` su un oggetto della classe derivata `D`. Si può evitare ciò dichiarando virtuale il distruttore della classe base `B`: in questo modo, tutti i distruttori delle classi derivate da `B` diventano automaticamente virtuali ottenendo quindi l'effetto che quando viene applicato l'operatore `delete`ad un puntatore alla classe base `B` il cui tipo dinamico è `D*`, per qualche sottoclasse `D`di `B`, viene effettivamente invocato il distruttore di `D`. Se il distruttore di `B` è virtuale allora tutti i distruttori delle classi derivate da `B` diventano automaticamente virtuali. Per una classe che contiene metodi virtuali è prassi e buona norma includere un distruttore virtuale, anche se per tale classe non dovesse essere strettamente necessario. Spesso si dichiara il distruttore virtuale e con corpo vuoto , rendendo quindi virtuale il distruttore standard. 

````C++
class B{
private:
	int* p;
public:
	B(int n, int v): p(new int[n]){
		for(int i=0; i<n; i++) p[i]=v;
	};
	virtual ~B() {delete[] p; cout<<"~B() ";}; //distruttore virtuale
};

class C: public B{
private:
	int* q;
public:
	C(int sizeB, int sizeC, int v): B(sizeB, v), q(new int[sizeC]) {
		for(int i=0; i<sizeC; i++) q[i]=v;
	};
	virtual ~C() {delete[] q; cout <<"~C() ";};
};

int main() {
	C* q = new C(4,2,18);
	B* p=q; //puntatore polimorfo
	delete p; //distruzione virtuale:invoca ~C()
}
// stampa: ~C() ~B()
//se ~B() non fosse virtuale verrebbe invocato solamente ~B() !!!!!!
````

# Classi base astratte
![[Pasted image 20231127183522.png]]
*Dichiaro l'esistenza di un contratto ma non lo implemento*

*Non esistono oggetti di una classe che contiene un metodo virtuale puro. Se esistesse e invocassi il metodo, che accade? il metodo non c'è. Esistono però come sottoggetti . Costruttori devono essere quindi considerati e modificati e verranno invocati in modo implicito*.

**Una classe è _astratta_ se ho un metodo virtuale puro. È importante capire dove serve e non forzarne l'uso**

In un linguaggio che supporta l'ereditarietà, una **classe astratta**, o *classe base astratta (ABC)*, è una classe che non può essere istanziata perché è etichettata come astratta o semplicemente specifica *metodi astratti*.

In alcune circostanza una classe `B`viene progettata solamente allo scopo di poter successivamente definire delle classi derivate da `B` e non per cercare e usare oggetti di `B`. In questa situazione una tale classe base `B` funziona da "*interfaccia comune*" per le classi derivate da `B`, ovvero `B` si limita a specificare la lista delle operazioni basilari che caratterizzano tutti i sottotipi di `B`, operazioni che in generale verranno realizzate in modo diverso da sottotipo a sottotipo.

Una classe composta solo da metodi virtuali è chiamata classe base astratta pura (o *base pura*) in C++ ed è anche conosciuta come interfaccia dagli utenti del linguaggio.

Una **classe concreta** è una classe che può essere *instanziata*, al contrario delle classi astratte, che non possono esserelo.

Un esempio di "*interfaccia*" potrebbe essere la classe *Shape* considerata nel contesto di *screen manager* che specifica l'esistenza di un metodo virtuale `draw()` che le classi derivate implementano in modi specifici.

````mermaid
flowchart TD
	A[Window] --> B{Shape2D}
	C[Icon] --> B
	D[PopUp] --> B
	E[Winfow3D] --> F{Shape3D}
	G[Icon3D] --> F
	H[PopUP3D] --> F
	B --> I{Shape}
	F --> I
````
//nell'esempio i virtual sono i rombi

Come la maggiorparte dei linguaggi orientati agli oggetti il C++, permette quindi di dichiarare un metodo virtuale senza definirne il corpo. Per avvisare il compilatore che il metodo non ha corpo basta aggiungere il marcatore "=0" alla fine della sua dichiarazione. In questo caso il metodo viene detto *metodo virtuale puro*.

il  metodo `G()` è dichiarato virtuale puro nella seguente classe `B` e quindi non deve essere definito.
```C++
class B {
..
	virtual void G() = 0;
...//Una classe che contiene un metodo virtuale puro è astratta
};
```

Quando una classe `B` contiene o eredita senza definirlo almeno un metodo virtuale puro, `B` viene detta *classe* (base) *astratta*. Il compilatore segnalerà un errore di compilazione in un tentativo di instanziare oggetti di una classe base astratta. Una sottoclasse `D` di una classe base astratta `B` si dice *concreta* se `D` implementa tutti i metodi virtuali puri di `B`. Gli oggetti di una classe base astratta `B` possono essere creati soltanto come sottooggetti di oggetti appartenti ad una sottoclasse concreta di `B`. Una classe astratta può comunque contenere dei costruttori, anzi tipicamente li contiene. Inoltre, è sempre possibile dichiarare puntatori e riferimenti a classi astratte. *(Per via del Polimorfismo)*.

Una **_Gerarchia di classi_** non deve necessariamente contenere delle classi astratte, ma spesso succede che nella fase di progettazione di una gerarchia si ravvisi l’opportunità di definire delle classi astratte nei primi livelli della gerarchia (quelli "più alti"). Ad esempio, considerando ancora l'esempio dello screen manager, la gerarchia potrebbe partire dalla classe base astratta `Shape` e potrebbero avere 2 sottoclassi di `Shape`ancora astratte come `Shape2D e Shape3D`, mentre dal terzo livello si potrebbe cominciare a definire delle sottoclassi concrete.

**Classi base astratte**:
1. Almeno un metodo virtuale puro
2. non si possono costruire oggetti
````C++
class B{ //classe base astratta
public:
	virtual void f() = 0;
};

class C: public B{}; //sottoclasse astratta

class D: public B { //sottoclasse concreta
public:
	virtual void f() {cout << "D::f() ";}
};

int main() {
	//C c; //illegale: "cannot declare c of type c..."
	D d; //Ok, D è concreta
	B* p; //OK, puntatore a classe astratta
	p = &d; //puntatore (super)polimorfo
	p->f(); //stampa D::f()
}
````
````C++
class poligono{ //classe astratta
protected:
	int nvertici;
	punto* pp;
public:
	poligono(int n, const punto v[]);
	~poligono();
	poligono(const poligono& pol);
	poligono& operator=(const poligono& pol);
	//contratto: ritorno il perimetro del poligono di invocazione
	virtual double perimetro() const; //metodo virtuale
	virtual double area() const =0; //metodo virtuale puro
};
#endif
````
##### distruttore virtuale puro
````C++
class Base{
// classe astratta
public:
	virtual ~Base()=0;
	// distruzione virtuale puro
};
Base::~Base() {} //definizione comunque obbligatoria!

int main() {
	Base b; // "cannot declare b of abstract type Base"
	Base* p = new Base; //"cannot allocate an object of abstract type Base"
}
````
````mermaid
flowchart TD
	A[Dirigente] --> B{Lavoratore}
	C[Rappresentante] --> B
	D[LavoratoreOre] --> B
````
````C++
class Lavoratore{//classe base astratta
public:
	virtual ~Lavoratore() {}
	Lavoratore(string s): nome(s) {};
	string getNome() const {return nome;};
	virtual double stipendio() const = 0; //virtuale pura
	virtual void printInfo() const {cout << nome;}; //virtuale
private:
	string nome;
};

class Dirigente : public Lavoratore{
private:
	double fissoMensile; //stipendio fisso
public:
	Dirigente(string s, double d = 0): Lavoratore(s), fissoMensile(d) {}

	virtual double stipendio() const{//implementazione
		return fissoMensile;
	}

	virtual void printInfo() const { //overriding
		cout << "Dirigente ";
		Lavoratore::printInfo(); //invocazione statica
	}
};

class Rappresentante : public Lavoratore{
private:
	double baseMensile; //stipendio base fisso
	double commissione; //commissione per pezzo venduto
	int tot; //pezzi venduti in un mese
public:
	Rappresentante(string s, double d=0, double e=0, int x=0): Lavoratore(s), baseMensile(d), commissione(e), tot(x) {}

	virtual double stipendio() const{//implementazioen
		return baseMensile + commissione*tot;
	}
	virtual void printInfo() const{//overriding
		cout << "Rappresentante "; Lavoratore::printInfo();
	};
};

class LavoratoreOre : public Lavoratore{
private:
	double pagaOraria;
	double oreLavorate;
public:
	LavoratoreOre(string s, double d=0, double e=0): Lavoratore(s), pagaOraria(d), oreLavorate(e) {}

	virtual double stipendio() const{ //implementazione
		if(oreLavorate <= 160) //nessuno straordinario
			return pagaOraria*oreLavorate;
		else //le ore straordinarie sono pagate il doppio
			return 160*pagaOraria+(oreLavorate-160)*2*pagaOraria;
	};
	virtual void printInfo() const {//overriding
		cout << "Lavoratore a ore "; Lavoratore::printInfo();
	};
};

//funzione esterna
void stampaStipendio(Const Lavoratore& x){
	x.printInfo(); //chiamata polimorfa
	cout << " in questo mese ha guadagnato " << x.stipendio() << " Euro.\n"; //chiamata (super)polimorfa
}

int main() {
	Dirigente d("Pippo", 4000);
	Rappresentante r("Topolino", 1000, 3, 250);
	LavoratoreOre l("Pluto", 15, 170);
	stampaStipendio(d);
	stampaStipendio(r);
	stampaStipendio(l);
}
/*STAMPA:
Dirigente Pippo in questo mese ha guadagnato 4000 Euro.
Rappresentante Topolino in questo mese ha guadagnato 1750 Euro.
Lavoratore a ore Pluto in questo mese ha guadagnato 2700 Euro.
*/
````

