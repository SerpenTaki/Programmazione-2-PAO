Il C++ è un linguaggio **_strongly typed_**: il programmatore è tenuto a specificare il tipo di ogni elemento sintattico che durante l'esecuzione denota un valore, ed il linguaggio garantisce che tale valore sia utilizzato in modo coerente con il tipo specificato (*e.s.* non è possibile eseguire una moltiplicazione tra un intero ed un puntatore).
Vi sono situazione rilevanti che non possono essere risolte mediante conversioni di tipo:
*Ad esempio se volessimo definire una funzione che calcoli il minimo tra 2 valori dobbiamo necessariamente definire una funzione diversa per ogni tipo di valori*: `int, float, orario, string`etc...
````C++
int min(int a, int b){
	return a < b ? a : b;
}
````
````C++
float min(float a, float b){
	return a < b ? a : b;
}
````
````C++
orario min (orario a, orario b){
	return a < b ? a : b;
}
````
````C++
string min(string a, string b){
	return a < b ? a : b;
}
````
Una soluzione attraente ma subdolamente pericolosa potrebbe essere la definizione di **macro** per il preprocessore
`#define min(a,b) ((a) < (b) ? (a) : (b))`
il preprocessore sostituisce:
`min(10,20)` con `10 < 20 ? 10 : 20`
`min(3.5,2.1)` con `3.5 < 2.1 ? 3.5 : 2.1`

Non abbiamo ottenuto una "vera funzione"
`min(++i,--j)`
verrebbe espansa dal preprocessore con:
`++i < --j ? ++i : --j`
e provocherebbe una doppia applicazione di ++ o --
````C++
int i = 3, j = 6;
cout << min(++i, --j);
//stampa 5
// NON stampa 4
````

La soluzione a questo problema consiste nell'usare un *template di funzione*, che assieme ai *template di classe* implementano in C++ l'idea del cosiddetto *polimorfismo parametrico*.

### Generic programming
La **programmazione generica** è uno stile di *programmazione informatica* in cui gli algoritmi sono scritti in termini di tipi *da specificare in seguito* che vengono poi *instanziati* quando necessario per tipi specifici forniti come *parametri*. 

# Template

_Un template di funzione è la descrizione di un metodo che il compilatore può usare per generare automaticamente istanze particolari di una funzione che differiscono per il tipo degli argomenti. Un template di funzione può essere sia una funzione globale che un metodo di classe_

I template sono una caratteristica del linguaggio di programmazione **C++** che consente alle funzioni e alle classi di operare con tipi *generici*. Ciò consente a una funzione o a una classe di lavorare su molti tipi di dati diversi senza essere riscritta per ciascuno di essi.

I template sono di grande utilità per i programmatori in C++, soprattutto se combinati con l'ereditarietà multipla e l'overloading degli operatori. La *Libreria standard del C++* fornisce molte funzioni utili all'interno di un quadro di modelli collegati.

Le principali ispirazioni per i template del C++ sono stati i moduli parametrizzati forniti da CLU e i generici forniti da Ada.
````C++
template <class T> //oppure: template <typename T>
// T è un parametro di tipo deve supportare l'operatore < per il tipo T (devo ridefinire <)
T min(Tipo a, T b){
	return a < b ? a : b;
}
````
Quindi:
````C++
int main(){
	int i, j,k;
	orario r,s,t;
	...
	//istanziazione implicita del template
	k = min(i,j);
	t = min(r,s);
	//oppure: istanziazione esplicita del template
	k = min<int>(i,j);
	t = min<orario>(r,s);
}
````
- I parametri di un template possono essere:
	- **Parametri di tipo**: preceduti da `class`o `typename`e che devono essere istanziati con un tipo qualsiasi
	- **Parametri valore _di qualche tipo_**: si possono istanziare con un valore costante del tipo indicato (*noto a compile-time*)
		- Un template *non è codice compatibile*: istanziazione **implicita** o **esplicita** di template di funzione
		- **Processo di deduzione degli argomenti** di un template nella istanziazione implicita (dove il *tipo di ritorno non si considera mai*)
**ATTENZIONE:** nell'istanziazione implicita il **tipo di ritorno** dell'istanza del template non viene *mai considerato nella deduzione degli argomenti* (essendo opzionale l'uso del valore ritornato)
````C++
int main(){
	double d; int i, j;
	...
	d = min(i,j); //istanzia int min(int, int)
					//e quindi usa la conversione
					//int => double "Promozione"
}
````
**L'algoritmo di deduzione degli argomenti di un template** procede esaminando tutti i parametri attuali passati al template di funzione da sinistra verso destra. Se si trova uno stesso parametro **T** del template che appare più volte come parametro di tipo, l'argomento del template dedotto per **T** da ogni parametro attuale deve essere **esattamente** lo stesso.
````C++
int main(){
	int i; double d, e;
	...
	e = min(d,i);
	// NON COMPILA
	//Si deducono 2 diversi argomenti del template: double e int
}
````
L'istanziazione dei parametri di tipo **deve essere univoca**.

Nell'algoritmo di deduzione degli argomenti sono ammesse **quattro tipologie di conversioni** dal tipo dell'argomento attuale al tipo dei parametri del template:
1. Conversione da l-value in r-value, i.e. da **`T&`** a **`T`**;
2. da array a puntatore, i.e. da **`T[]`** a **`T*`**
3. fa conversione di qualificazione costante, i.e. da **`T`** a **`const T`**;
4. conversione da r-value a riferimento costante, i.e. da r-value di tipo **`T`** a **`const T&`**
````C++
template <class T> void E(T x) {...};
template <class T> void F(T* p) {...};
template <class T> void G(const T x) {....};
template <class T> void H(const T& y) {....};

int main(){
	int i = 6; int& x = i;
	int a[3] = {4,2,9};
	E(x); //1. istanzia void E(int)
	F(a); //2. istanzia void F(int*)
	G(i); //3. istanzia void G(const int)
	H(7); //4. istanzia void H(const int&)
}
````

**Istanziazione esplicita** degli argomenti dei parametri del template di funzione. Nell'istanziazione esplicita è possibile applicare *qualsiasi conversione implicita* di tipo per i parametri attuali del template di funzione
````C++
int main(){
	int i; double d, e;...
	e = min<double>(d,i);
	//compila!!
	//istanzia. double min(double, double)
	//quindi converte implicitamente i da int a double
}
````
Un parametro di una funzione può essere un *riferimento ad un array statico.* In  questo caso, la dimensione costante dell'array è parte integrante del tipo del parametro e il compilatore controlla che la dimensione dell'array parametro attuale coincida con quella specificata nel tipo del parametro.
````C++
int min(int (&a)[3]){//array di 3 int
	int m = a[0];
	for(int i = 1; i<3; i++)
		if(a[i]<m) m=a[i];
	return m;
}

int ar[4]= {5,2,4,2};
cout << min(ar); //non compila!
````
````C++
template <class T, int size>//int size Parametro valore
T min(T (&a)[size]){
	T vmin = a[0];
	for(int i = 1; i<size; i++)
		if(a[i]<vmin) vmin=a[i];
	return vmin;
}

int main(){
	int ia[20];
	orario ta[50];
	...
	cout << min(ia);
	cout << min(ta);
	//oppure
	cout << min<int,20>(ia);
	cout << min<int,50>(ta);
}
````

## Modello di compilazione del template
La definizione di un template di funzione è solamente uno schema per la definizione di un numero potenzialmente infinito di funzioni. *Una definizione di template non può essere compilata in qualche forma di codice macchina che possa essere effettivamente definito.*
1) La definizione del template deve essere visibile all'utilizzatore del template?
2) Il file header del template cosa deve includere?
	- Solo la dichiarazione del template?
	- Sia la dichiarazione che la definizione?
3) Cosa si compila effettivamente?
### Compilazione per inclusione
*lo includo senza doverlo compilare*
Definizione del template in un "header file" che deve essere sempre incluso dal codice che necessita di istanziare il template.
Il compilatore usa quindi queste definizioni per generare il codice di tutte le istanze del template utilizzate nel file che sta compilando.
Non vi è quindi il concetto di compilazione separata di un template
**Problema 1**: No information hiding -> nessuna soluzione (*pazienza*)
- il file header contiene tutti i dettagli della definizione dei template. Tali dettagli risultano quindi visibili all'utente e ciò va quindi contro il principio di *information hiding*
**Problema 2:** Istanze multiple del template -> *Dichiarazioni esplicite di istanziazione*
- Se la stessa istanza di un template viene usata in più file compilati separatamente il codice per tale istanza viene generato più volte dal compilatore. *rallenta la compilazione*.
###### Dichiarazione esplicita
di istanziazione del template di funzione:
````C++
template <class Tipo>
Tipo min(Tipo a, Tipo b){
	return a < b ? a : b;
}
````
al tipo `int` ha la forma: `template int min(int,int);`

Forza il compilatore a generare il codice dell'istanza del template relativa al tipo `int`

### Compilazione per separazione
*Compila parzialmente il codice tipizzato attendendo per le parti non ancora conosciute* **DEPRECATO**
Dichiarazione del template separata dalla sua definizione. Parola chiave **export** non supportata dai compilatori. Compilatori Comeau ed icc (*Intel C++ compiler*) tra i pochissimi che supportavano **export**.
Il comitato C++11 ha deciso di rimuovere **export** dallo standard . Rimane una keyword riservata.

-> Nei file header vengono messe solo le dichiarazioni dei template mentre le definizioni vengono messe in un file "*compilato separatamente*".
````C++
//file "min.h"
template <class T>
T min(T a, T b);
//file "min.cpp"
export template <class T>
T min(T a, T b) { return a < b ? a : b; }
//file "main.cpp"
#include "min.h"
int main() {
	int i, j, k; orario r, s, t;
	...
	k = min(i,j);
	..
	t = min(r,s);
	...
}
````
# Template di classe
È essenzialmente la descrizione di un metodo (modello) che il compilatore può usare per generare automaticamente istanze particolare di una classe che differiscono per il tipo di alcuni membri, cioè campi dati, metodi o classi interne, propri della classe.

Se si vogliono usare sia code di interi che code di stringhe, si devono scrivere 2 definizioni distinte della classe e con 2 nomi diversi.
````C++
class QueueInt{
public:
	Queue();
	~Queue();
	bool empty() const;
	void add(const int&);
	int remove();
private:
	...
};

class QueueString{
public:
	Queue();
	~Queue();
	bool empty() const;
	void add(const string&);
	string remove();
private:
	...
};
````

**TEMPLATE DI CLASSE `Queue<T>`**
````C++
template <class T>
class Queue {
public:
	Queue();
	~Queue();
	bool empty() const;
	void add(const T&);
	T remove();
private:
...
};

Queue<int> qi;
Queue<bolletta> qb;
Queue<string> qs;
````
### Template di classe
- Parametri di tipo
- Parametri valore 
- Parametri tipo/valore con **possibili valori di default**
- Solo **istanziazione esplicita**
````C++
template <class Tipo = int, int size = 1024>
class Buffer{
...
};

Buffer<> ib; //Buffer<int,1024>
Buffer<string> sb; //Buffer<string,1024>
Buffer<string, 500> sbs; //Buffer<string, 500>
````
Completiamo il template `Queue<T>`
````C++
template <class T>
class QueueItem{//per ora classe esterna
public: //per ora tutto public
	QueueItem(const T&);
	T info;
	QueueItem* next;
};

template <class T>
class Queue{
public:
	Queue();
	~Queue();
	bool empty() const; //Queue e non Queue<T>
	void add(const T&);
	T remove();
private:
	QueueItem<T>* primo; //QueueItem<T>
	QueueItem<T>* ultimo; //e non QueueItem
};
````

Nella dichiarazione o definizione di un template (*di classe o di funzione*) possono comparire sia nomi di istanze di template di classe sia nomi di template di classe.
````C++
template<class T>
int fun(Queue<T>& qT, Queue<string> qs);
	//Queue<T> template di classe associato
	//Queue<string> istanza di template di classe
````
*Nota bene*: il compilatore genera una istanza di un template (*di classe o funzione*) **solo quando è necessario**. 
Ad esempio il compilatore non genera l'istanza `Queue<int>` quando incontra le 2 seguenti occorrenze del nome dell'istanza:
````C++
//basta una dichiarazione incompleta di template
template <class T> class Queue;

void Stampa(const Queue<int& q){
	Queue<int>* pqi = const_cast< Queue<int>* >(&q);
	...
}
````
Invece il compilatore è costretto a generare l'istanza del template di classe con
````C++
template <class T> class Queue{
	//definizione della classe necessaria
};

void Stampa(Queue<int> q){
	Queue<int> qi; //si genera per l'istanza Queue<int>
	//per la costruzione di default
}
````
il compilatore è pure costretto a generare l'istanza `Queue<int>` con
````C++
template <class T> class Queue{
	//definizione
};

void Stampa(const Queue<int>& q){
	Queue<int>* pqi = const_cast< Queue<int>* >(&q);
	pqi++;
	...
}
````
perchè l'istanza serve per calcolare la quantità `sizeof(Queue<int>)` di cui occorre incremetare il puntatore per eseguire `pqi++`

## Metodi di un template di classe
In un template di classe è possibile definire metodi inline
````C++
template <class T>
class Queue{
...
public:
	Queue() : primo(0), ultimo(0) {}
	...
};
````
La **definizione esterna** di un metodo in un template di classe richiede la seguente sintassi:
````C++
template <class T>
class Queue{
...
public:
	Queue();
	...
};

//definizione esterna
template <class T>
Queue<T>::Queue() : primo(0), ultimo(0) {}
````
Un metodo di un template di classe è un template di funzione.
Esso non viene istanziato quando viene istanziata la classe **ma se e soltanto se** il programma usa effettivamente quel metodo.

Completiamo la definizione del template  `Queue<T>`
````C++
// fiel Queue.h
#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class QueueItem{
public:
	//per gli scopi di Queue basta questo costruttore
	QueueItem(const T& val): info(val), next(0) {}
	T info;
	QueueItem* next;
};

template <class T>
class Queue{
public:
	Queue() : primo(0), ultimo(0) {}
	bool empty() const;
	void add(const T&);
	T remove();
	/*Attenzione: distruttore, costruttore di copia e assegnazione profondi*/	
	~Queue();
	Queue(const Queue&);
	Queue& operator=(const Queue&);
private:
	QueueItem<T>* primo; //primo el. della coda
	QueueItem<T>* ultimo; //ultimo el. della coda
};

//Sempre nel file Queue.h

template <class T>
bool Queue<T>::empty() const{
	return(primo==0);
}

template <class T>
void Queue<T>::add(const T& val){
	if(empty())
		primo = ultimo = new QueueItem<T>(val);
	else{//aggiunge in coda
		ultimo->next = new QueueItem<T>(val);
		ultimo = ultimo->next;
	}
}

//NEL FILE Queue.h
#include <iostream>
template <class T>
T Queue<T>::remove(){
	if(empty()){
		std::cerr << "remove() su coda vuota" << std::endl;
		exit(1); //BAD PRACTICE
	}
	QueueItem<T>* p = primo;
	primo = primo->next;
	T aux = p->info;
	delete p;
	return aux;
}

template <class T>
Queue<T>::~Queue(){//distruzione profonda
	while(!empty()) remove();
}
#endif
````

### Amicizie in template di classe
[[Amicizia#Amicizie in template di classe]]
## Campi dati statici in template di classe
*Naturalmente in un template di classe possono essere dichiarati campi dati e metodi statici.*
Aggiungiamo al template di classe `Queue`un campo dati statico intero che funzioni da contatore globale degli oggetti `QueueItem` presenti nelle liste di tutti gli oggetti di una *certa istanza* di `Queue`
````C++
template <class Tipo>
class Queue {
private:
	static int contatore;
	...
};
````
Pertanto ad ogni istanza di `Queue`è associato un campo statico `contatore`diverso. L'inizializzazione di un campo dati statico di un template di classe naturalmente deve essere esterna alla classe e deve rispettare la seguente sintassi:
````C++
template <class T>
int Queue<T>::contatore = 0;
````
Un campo dati statico è istanziato e quindi inizializzato dalla definizione del template **soltanto se viene effettivamente usato**. La mera definizione di un campo dati statico non provoca allocazione di memoria!!!!!!!!!!!!!!!
````C++
template<int I> //parametro valore
class C{
	static int numero;
public:
	C() {++numero;}
	C(const C& x) {++numero;}
	static void stampa_numero();
};

//inizializzazione parametrica del campo statico
template<int I>
int C<I>::numero = I;

template<int I>
void C<I>::stampa_numero()
{cout << "Valore statico: " << numero << endl;}

int main(){
	C<1> uno;
	C<2> due_a;
	C<3> due_b(due_a);
	C<1>::stampa_numero(); //stampa: 2
	C<2>::stampa_numero(); //stampa: 4
}
````
````C++
class A{
public:
	A(int x=0) {cout << x << "A() ";}
};

template<class T>
class C{
public:
	static A s;
};
template<class T>
A C<T>::s=A(); //stampa 0A()

int main(){
	C<double> c;
	C<int> d;
	C<int>::s = A(2);
}
//stampa: 0A() 2A()
//NOTA BENE: non stampa 0A() 0A() 2A() !!
````

# Friend e classi annidate
"Una classe annidata è un membro della classe contenitore e come tale ha *gli stessi diritti di accesso di qualsiasi altro membro*. I membri di una classe racchiusa non hanno *nessun accesso speciale ai membri* di una classe annidata; devono essere rispettate le normali regole di accesso". *La classe contenitore invece non ha privilegi speciali sulla classe annidata*
e le regole di accesso abituali specificano che:

"Un membro di una classe può accedere anche a tutti i nomi a cui la classe ha accesso...".

## Classi annidate in template di classe
Annidiamo nella parte privata del template di classe `Queue` la definizione del template di classe `QueueItem`
````C++
template <class T>
class Queue{
private:
	//template di classe annidato ASSOCIATO
	class QueueItem{
	public:
		QueueItem(const T& val);
		T info;
		QueueItem* next;
	};
	...
};
````
`QueueItem<T>` è un cosiddetto o *tipo implicito*, in quanto non è un tipo completamente definito ma dipende implicitamente dai parametri di tipo `Queue<T>`
Il C++ standard prevede che l'uso di tipi e di template di classe o di funzione che dipendono da un parametro di tipo debba essere disambiguato tramite la keyword `typename`(*per i tipi*) e `template`(*per i template sia di classe che di funzione*). In altri termini non è permesso l'uso implicito di tipi e di template che dipendono da parametri di tipo. Supponiamo ad esempio che un template di classe contenga classi annidate, template di classi annidati come segue:
[[STL#Vector]]

````C++
template <class T> class C{
public:
	class D{ //classe annidata
	public:
		T x; //tipo implicito per il compilatore anche se non lo uso
	};

	template <class U> class E{ //template di classe annidata
	public:
		T x;
		void fun1() {return;}
	};

	template <class U> void fun2() {//template di funzione
		T x; return;
	}
};
````
Allora l'uso dei nomi `D, E`e `fun2`che dipendono da un parametro di tipo, ad esempio nel seguente template di funzione `templateFun`, deve essere disambiguato come segue:
```C++
template <class T>
void templateFun(typename C<T>::D d){ //non è un tipo, dipende da T, tipo esplicito->typename
//C<T>::D è un uso di un tipo che dipende dal parametro T
	typename C<T>::D d2 = d;

/*
1. E<int> è un uso del template di classe annidata che dipende dal parametro T
2. C<T>::E<int> è un uso di un tipo che dipende dal parametro T
*/
	typename C<T>::template E<int> e;
	e.fun1();
//c.fun2<int> è un uso del template di funzione che dipende dal parametro T
	C<T> c;
	c.template fun2<int> ();
}
```
