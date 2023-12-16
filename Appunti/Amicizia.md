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

````C++
class contenitore{
private:
	class nodo{
	public: //per convenienza nell'esempio
		int info;
		nodo* next;
		nodo(int x, nodo* p): info(x), next(p) {}
	};
	nodo* first; //puntatore al primo nodo della lista
public:
	contenitore() : first(0) {}
	void aggiungi_in_testa(int x) {first = new nodo(x,first);}
}
````

Classe `iteratore` i cui oggetti rappresentano degli indici ai nodi degli oggetti della classe `contenitore`
````C++
class iteratore{
private:
	contenitore::nodo* punt; //nodo puntato dall'iteratore
public:
	bool operator==(const iteratore& i) const{
		return punt == i.punt;
	}
	bool operator!=(const iteratore& i) const{
		return punt != i.punt;
	}
	iteratore& operator++(){ //operator++ prefisso
		if (punt) punt = punt->next; 
		return *this;
	}
	/*se it punta all'ultimo nodo, da ++it non si torna indietro
	nessun costruttore per il momento*/
};
````

**Problema:** nodo ed i suoi membri non sono accessibili dall'esterno

````C++
class contenitore{
// friend class iteratore; //non necessaria da C++03
private:
	class nodo{
	...
	};
	nodo* first;
public:
	class iteratore{ //classe annidata nella parte pubblica
	private:
		contenitore::nodo* punt;
		...
	};
	contenitore();
	void aggiungi_nodo(int);
}
````

````C++
class contenitore{
private:
	class nodo{...};
	nodo* first;
public:
	class iteratore{ //necessaria
		friend class contenitore; //dichiarazione di amicizia
		...
	}; //ATTENZIONE, va definita prima dei metodi che la usano
	...
	iteratore begin() const; //costruttore di iteratore
	iteratore end() const; //costruttore di iteratore
	//operatore di subscripting
	int& operator[] (const iteratore&) const;
};
````

````C++
contenitore::iteratore contenitore::begin() const{
	iteratore aux; //costruttore di default standard
	aux.punt = first; //per amicizia ho accesso a punt
	return aux;
}

contenitore::iteratore contenitore::end() const{
	iteratore aux;
	aux.punt = 0; //per amicizia
	return aux;
}

int& contenitore::operator[](const contenitore::iteratore& it) const{
	return it.punt->info; //per amicizia, nessun controllo su it.punt
}
````

Possiamo ora utilizzare gli iteratori della classe contenitore come nel seguente esempio di funzione esterna:

````C++
int somma_elementi(const contenitore& c){
	int s=0;
	for(contenitore::iteratore it=c.begin(); it!=c.end(); ++it)
		s += c[it];
	return s;
}
````

Dichiarazione della classe `iteratore`:

````C++
class iteratore{
	friend class bolletta;
public:
	bool operator==(const iteratore&) const;
	bool operator!=(const iteratore&) const;
	iteratore& operator++(); //++prefisso
	iteratore operator++(int); //++postfisso
private:
	bolletta::nodo* punt;
};
//notare che non ci sono costruttori espliciti
````

Metodi `begin()` ed `end()` e l'overloading dell'operatore di indicizzazione `[]`

````C++
class bolletta{
public:
	...
	iteratore begin() const;
	iteratore end() const;
	telefonata& operator[] (const iteratore&) const,
	//tipo di ritorno per riferimento
	...
private:
	...
};
````

[[Overloading#Overloading operator->]]

# Amicizie in template di classe
**Dichiarazione nel template di classe `C` di una classe o funzione _friend non template_**
````C++
class A {... int fun(); ....};

template<class T>
class C{
	friend int A::fun();
	friend class B;
	friend bool test();
}
````
La classe `B`, la funzione `test()` e il metodo `A::fun()` della classe `A` sono `friend` di **tutte le istanza** del template di classe `C`.

**Dichiarazione nel template di classe `C` di un template di classe `A`  o di funzione `fun` _friend associato_**
````
template <class U1, ...., class Uk> class A;
template <class V1, ...., class Vj> void fun(...);
template <class T1, ...., class Tn> class C {
	friend class A<....,Tj,....>;
	friend void fun<...,Tj,....>(...);
};
````
````C++
template<class T> class A {... int fun(); ...};
template<class T> class B { ... };

//dichiarazione incompleta del template di classe C
template<class T1, class T2> class C;

//dichiarazione del template di funzione test
// associato a C
template<class T1, class T2> bool test(C<T1,T2>);

template<class T1, class T2> class C{
	friend int A<T1>::fun();
	friend class B<T2>;
	friend bool test<T1,T2>(C);
};
````
Ad ogni istanza del template di classe C rimane associata come amica una ed una sola istanza dei template di classe `B`

**Dichiarazione nel template di classe `C` di un template di classe o di funzione _friend non associato_**
````C++
template<class T>
class C {
	template<class Tp> //amicizia con template
	friend int A<Tp>::fun(); //di metodo

	template<class Tp> //amicizia con template
	friend class B; //di classe

	template<class Tp> //amicizia con template
	friend bool test(C<Tp>) //di funzione
};
````
Alcuni compilatori pre-standard non supportavano quest'ultima tipologia di dichiarazioni `friend`. Il compilatore GNU `g++` supporta i template di classe e di funzione friend non associati.

È naturale associare ad ogni istanza di `QueueItem` una sola istanza amica della classe `Queue`, ovvero quella associata.
````C++
template <class T>
class QueueItem{
	friend class Queue<T>;
private:
	T info;
	QueueItem* next;
	QueueItem(const T& val) : info(val), next(0) {}
};
````

````
template <class T>
ostream& operator<<(ostream&, const Queue<T>&);
````
Di quali amicizie abbiamo bisogno?
````C++
template<class T>
ostream& operator<<(ostream& os, const Queue<T>& q){
	os << "(";
	QueueItem<T>* p = q.primo; //amicizia con Queue
	for(; p!=0; p = p->next) //amicizia con QueueItem
		os << *p << " "; //operator<< per il tipo Queueitem
	os << ")" << endl;
	return os;
}
````
Dobbiamo quindi dichiarare `operator<<` come funzione amica associata sia della classe `Queue` che della classe `Queueitem`
````C++
template <class T>
class Queue{
	friend ostream& operator<< <T> (ostream&, const Queue<T>&);
	...
};

template <class T>
class QueueItem {
	friend osteam& operator<< <T> (osteam&, const Queue<T>&);
	...
};
````

Inoltre, dobbiamo definire `operator<<` per il template di classe `QueueItem`.
````C++
template <class T>
ostream& operator<<(ostream& os, const QueueItem<T>& qi){
	os << qi.info; //amicizia con QueueItem!
					//NB: richiede operator<< sul tipo T
	return os;
}
````
Dobbiamo quindi dichiarare la funzione esterna `operator<<` di `QueueItem` come amica associata della classe `QueueItem`
````C++
template <class T>
class QueueItem{
	friend ostream& operator<< <T>(ostream&, const QueueItem<T>&);
	...
};
````

[[Template#Campi dati statici in template di classe]]
