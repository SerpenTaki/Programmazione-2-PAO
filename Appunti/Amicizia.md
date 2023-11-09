## Funzione amica
Nella programmazione orientata agli oggetti, una funzione amica, cioè "amica" di una determinata classe, è una funzione a cui viene dato lo stesso accesso dei metodi ai dati privati e protetti.

Una funzione amica è dichiarata dalla classe che ne concede l'accesso, quindi le funzioni amiche fanno parte dell'interfaccia della classe, come i metodi. Le funzioni amiche consentono una sintassi alternativa per l'uso degli oggetti, ad esempio f(x) invece di x.f(), o g(x,y) invece di x.g(y). Le funzioni amiche hanno le stesse implicazioni sull'incapsulamento dei metodi.

Un concetto simile è quello di classe amica.

````C++
//file bolletta.h
class bolletta{
	...
	//funzione esterna dichiarata friend
	friend ostream& operator<<(ostream&, const bolletta&);
	..
};

//nel file bolletta.cpp
ostream& operator<<(ostream& os, const bolletta& b){
	os << "TELEFONATE IN BOLLETTA" << endl;
	bolletta::nodo* p = b.first; //per "amicizia"!
	int i = 1;
	while(p){
		os << i++ << ")" << p->info << endl;
		p = p->next;
	}
	return os;
}
````

### Accesso per le classi annidate

**I membri di una classe annidata non hanno un accesso speciale ai membri di una classe racchiusa**, né alle classi o alle funzioni che hanno concesso l'amicizia a una classe racchiusa; devono essere rispettate le normali regole di accesso (clausola 11). **I membri di una classe racchiusa non hanno accesso speciale ai membri di una classe annidata**; devono essere rispettate le consuete regole di accesso (classe 11).

````C++
class E{
	int x;
	class B {};
	class I{
		B b; //error E::B is private
		int y;
		void f(E* p, int i){
			p->x = i; //error E::x is private
		}
	};
	int g(I*p){
		return p->y; //error I::y is private
	}
};
````

**Da C++11**
*Una classe annidata è un membro e come tale ha gli stessi diritti di accesso di qualsiasi altro membro.* I membri di una classe racchiusa non hanno accesso speciale ai membri di una classe annidata; devono essere rispettate le normali regole di accesso.
````C++
class E{
	int x;
	class B {};
	class I{
		B b; //OK: E::I can access E::B
		int y;
		void f(E* p, int i){
			p->x = i; //OK: E::I can access E::x
		}
	};

	int g(I* p){
		return p->y; //errore: I::y è privato
	}
};
````

**Nota Bene**: (come nella vita) la relazione di amicizia *non* è simmetrica e *non* è transitiva (vale per amicizia tra classi)

**_Iteratori_**: Funzionalità per scorrere ed accedere agli elementi di una collezione

##### Iteratori lez 15 slide 21

