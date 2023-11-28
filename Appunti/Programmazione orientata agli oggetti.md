Un programma è costituito da:
- **Algoritmi**
- **Dati** su cui operano gli algoritmi

Quando l'accento è posto sugli **Algoritmi** si parla di *programmazione procedurale*.
Invece quando è posto sui **Dati** si parla *programmazione ad oggetti*. 

I dati sono raccolti in campi **_fields_** mentre le funzioni sono conosciute come **metodi**. 

#### Come definiamo un linguaggio di programmazione un linguaggio ad oggetti?

quando permette di implementare 3 meccanismi usando la sintassi nativa del linguaggio:
1. **Incapsulamento** -> separazione della interfaccia di una classe dalla corrispondente implementazione.
2. **Ereditarietà** -> permette di definire delle classi a partire da altre già definite
3. **Polimorfismo** -> "multiforme" permette di scrivere un *client* che può servirsi di oggetti di classi diverse, ma dotati di una stessa _interfaccia_ comune;

**Le classi permettono di realizzare il concetto generale di [[ADT]]

# C++
Permette di integrare ed estendere i 2 paradigmi procedurale e ad oggetti:
- I _template_ di funzione
- I _template_ di classe
- _Gestione delle eccezioni_
#### Le principali caratteristiche del C++
- Compilato (non interpretato come Java)
- Tipizzazione forte statica (_Strongly **Typed**_)
- No garbage collector (Java lo possiede)
- Standardizzato (ANSI, COMP CERT compilatore di C un approccio verificato C standardizzato)
- General-purpose e molto diffuso (Adobe SW, Mozilla SW, MySQL, Microsoft SW, Google Chromium, Games...)
- Efficienza
- Operatori e loro overloading
- Librerie

# Hello world in C++


```C++
#include <iostream>

using namespace std;

int main(){
	cout << "Hello World" << endl;
}//compila correttamente con g++

// si può fare di meglio per evitare l'inquinamento dei nomi

int main(){
	std::cout << "Hello World" << endl;
}
```

La seconda versione non usa il namespace ma usa l'operatore `::` di scoping.
La seconda versione è migliore perchè? [[Namespace]]

### Come funziona la locazione degli oggetti
![[Pasted image 20231004163407.png]]
![[Pasted image 20231004163548.png]]
I metodi sono in comune per tutti gli oggetti, Una copia in memoria dei metodi per tutti gli oggetti. 
### la keyword this


``this`` identifica un puntatore speciale che contiene l'indirizzo dell'istanza della classe che ha invocato il metodo.

Possiamo "esplicitare" il parametro implicito `this` nella dichiarazione del metodo `secondi()` e nella sua chiamata:

````C++
//la definizione 
int orario::Secondi() { return sec % 60; }
//esplicitando il parametro this diventerebbe
int orario::Secondi(orario* this) {return (*this).sec % 60; }

//mentre la chiamata
int s = mezzanotte.Secondi();
//esplicitando il parametro implicito diventerebbe
int s = Secondi(&mezzanotte);

````
`this` è una keyword. Dereferenziazione `*this` nel corpo di un metodo. Ad esempio:
![[Pasted image 20231004164607.png]]

A volte l'utilizzo esplicito del puntatore `this` diviene necessario nella definizione di qualche metodo.
````C++
class A {
private:
	int a;
public:
	A f();
}

A A::f(){
	a = 5;
	return *this;
}
````

[[Information hiding]]

[[Costruttori]]


## Compilazione

![[Pasted image 20231023143328.png]]

All'utilizzatore basta fornire il file "**`orario.h`**" da includere in "**`main.cpp`**" per la compilazione ed il file "**`orario.o`**" da aggiungere al codice compilato di "**`main.cpp`**" affinchè il linker generi l'eseguibile.

````C++
g++ main.cpp orario.o // compila main.cpp e lo linka con orario.o
````

##### Il makefile
Il **make** è una *utility*, sviluppata sui *sistemi operativi* della famiglia UNIX, ma disponibile su un'ampia gamma di sistemi che automatizza il processo di creazione di *file* che dipendono da altri file, risolvendo le *dipendenze* e invocando *programmi* esterni per il lavoro necessario.

Consiste di alcune regole così descritte:
````
TARGET : DEPENDENCIES ...
COMMAND
````

Di solito TARGET è il nome dell'eseguibile o del file oggetto da ricompilare ma può essere anche un azione  (es.**`clean`** ). È una sorta di identificatore dell'azione da compiere: alla chiamata **`bash$ make clean`** verrà eseguito il TARGET **`clean`**.

Le DEPENDENCIES sono usate come input per generare l'azione TARGET e di solito sono più di una. Più genericamente vengono citati i file o le azioni cioè i TARGET, da cui dipende il completamento dell'azione TARGET.

Un COMMAND è invece il comando da eseguire; può essere più di uno e di solito si applica sulle DEPENDENCIES

![[Pasted image 20231024152111.png]]

# Integrated Development Environment
In Informatica un **ambiente di sviluppo integrato** ovvero un IDE, rispettivamente ambiente integrato di progettazione e ambiente integrato di debbugging è un software che in fase di programmazione aiuta i programmatori nello sviluppo del codice sorgente di un programma. Lo aiuta segnalando gli errori di sintassi del codice direttamente in fase di stesura, oltre a una serie di strumenti e funzionalità di supporto alla fase di sviluppo e di debugging

#### Valgrind
È uno strumento *open source* per il *debug* di problemi di memoria, la ricerca di *memory leak* e il *profiling* del software. È stato sviluppato come una versione distribuibile e modificabile di *Purify* per Linux ma è divenuto una infrastruttura per la creazione di strumenti di analisi dinamica come la profilazione ed il controllo dei programmi.

# Object lifetime

Nella programmazione orientata agli oggetti (OOP), **il _ciclo di vita_ di un oggetto è il tempo che intercorre tra la sua creazione e la sua _distruzione_.** Le *regole per il ciclo di vita degli oggetti variano in modo significativo da un linguaggio all'altro*, in alcuni casi da un'implementazione all'altra di un determinato linguaggio, e il ciclo di vita di un particolare oggetto può variare da un'esecuzione all'altra del programma.

- C++ no garbage collector: il programmatore ha il controllo totale della memoria
- gli altri linguaggi hanno un algoritmo che decide, quindi non hai il controllo della memoria

In alcuni casi, il tempo di vita di un oggetto coincide con il tempo di vita di una variabile che ha quell'oggetto come valore (sia per le variabili statiche che per quelle automatiche), **ma in generale il tempo di vita di un oggetto non è legato al tempo di vita di una variabile**. In molti casi - e per impostazione predefinita in molti linguaggi orientati agli oggetti, in particolare quelli che utilizzano la garbage collection (GC) - gli oggetti sono allocati sull'heap e la durata di vita degli oggetti non è determinata dalla durata di vita di una determinata variabile: il valore di una variabile che contiene un oggetto corrisponde in realtà a un riferimento all'oggetto, non all'oggetto stesso, e la distruzione della variabile distrugge solo il riferimento, non l'oggetto sottostante.

**In C++ ci sono 3 tipi di variabili**
1. Globali 
2. Locali 
3. [[Static#Static variable]]

### Tempo di vita delle variabili
1. Variabili di classe automatica (**_Call stack_ la loro vita è decisa e regolata da loro durante le chiamate di funzione**)
2. Variabili di classe statica (**_Memoria statica_**)
	- campi dati statici (PAO)
	- Variabili globali (P1, ma deprecate praticamente)
	- variabili statiche in corpo di funzione (*cattiva pratica*)
3. Variabili dinamiche (**_Heap_** "_mucchio_" _muore con la delete_)

[[Distruttori]]

### Conversioni di tipo
- Conversioni **implicite** (coercions)
- Conversioni **esplicite**
- Conversioni **predefinite** dal linguaggio
- Conversioni **definite dall'utente**
- Conversioni **con/senza perdita** di informazione (*narrow/wide conversions*)

An expression **e** is said to be **_implicitly convertible_** to **T** if and only if **T** can be copy-initialized from **e** that is, the declaration **`T t=e`** can be complied.

#### Operatori di conversione esplicita
- `static_cast`
- `const_cast`
- `reinterpret_cast`
- `dynamic_cast`

````
//CONVERSIONI IMPLICITE "SAFE" (castless conversion)
T& => T // e non viceversa int& x = 5
T[] => T*     int[2] a={3,1}; int* p = a;
T* => void* //generic pointer: int* p=&x; void* q=p;
T => const T   int x=5; const int y=x;
const NPR => NPR //NPR = Tipo NON Puntatore o Riferimento
					//In particolare: C* const => C*
const int x= 5; int y = x;
int* const p = &z; int* q = p;


T* => const T*  int*p = &x; const int* q=p;
T => const T&   int x= 4; const int& r=x;
//TRA TIPI PRIMITIVI

bool => int
float => double => long double
char => short int => int => long
unsigned char => ... => unsigned long
````
````C++
//Esempio di narrowing conversion
double d = 3.14;
int x = static_cast<int>(d);
//Esempio di wide conversion (coercion)
char c = 'a';
int x = static_cast<int>(c);
//Esempio di conversione T* => void*
void* p;
p=&d;
//per la conversione di void* serve uno static_cast
double* q = static_cast<double*>(p);
````

##### Const_cast

`const_cast<Type> (puntatore/riferimento)`

`const_cast` permette di convertire *un puntatore o un riferimento* ad un tipo `const T` ad un puntatore o riferimento a `T` (quindi perdendo l'attributo `const`)

````C++
const int i = 5;
int* p = const_cast<int*> (&i);

void F(const C& x){
	x.metodoCostante();
	const_cast<C&>(x).metodoNonCostante();
}

int j=7;
const int* q = &j; //OK, cast implicito
````

##### Reinterpret_cast
`reinterpret_cast <T*> (puntatore)`
`reinterpret_cast` si limita a reinterpretare a basso livello la sequenza di bit con cui è rappresentato il valore puntato da `puntatore` come fosse un valore di tipo `T`. Questo tipo di cast è particolarmente pericoloso
````C++
Classe C;
int* p = reinterpret_cast<int*>(&c);
const char* a = reinterpret_cast<const char*>(&c);
string s(a);
cout << s;
````

## Lo standard C++
Prevede la definizione di:
- Template di classi collezione: **contenitori**
- Template di funzione: **algoritmi generici**
-> Possibile trovarla su cplusplus.com
-> Documentazione [[STL]] by cppreference.com

## Evoluzione del programmatore C++
-> Una versione migliore del C
-> Il secondo passo è OOP object based C++
- Rimanere bloccati qui perchè ci arrivi troppo velocemente 
- Non rimanere bloccato qui perchè perdi il lato migliore del linguaggio che è il vero arrivo verso l'OOP. Con le funzioni virtuali
-> Concetto di virtual function
- Se non le usi non hai capito l'OOP
- Non c'è nulla come le funzioni virtuali nella programmazione procedurale

# Perchè i metodi virtuali
[[Virtual Method Table]]
A questo punto potreste avere una domanda: "*Se questa tecnica è così importante, e se fa sempre la chiamata di funzione 'giusta', perché è un'opzione? Perché ho bisogno di conoscerla?".

La risposta fa parte della filosofia fondamentale del C++: "Perché non è altrettanto efficiente".
Alcuni linguaggi OO hanno adottato l'approccio secondo cui il binding tardivo è talmente intrinseco all'OOP che dovrebbe avvenire sempre, non dovrebbe essere un'opzione e l'utente non dovrebbe saperlo.

Per questo motivo, la parola chiave **virtual** viene fornita per ottimizzare l'efficienza.
# SOLID (object-oriented design)
Nella *programmazione informatica*, **SOLID (Single Responsibility Open-closed, Liskov substitution, Interface segregation and Dependency Inversion)** è un *acronimo mnemonico* introdotto da Micheal Feathers. Sta per cinque principi fondamentali dell'OOP e del *design*. I principi, se applicati insieme, mirano a rendere più probabile che un *programmatore* crei un sistema facile da **mantenere** e da estendere nel tempo.

#Mantenibilità
#Estensibilità

**S**
- Single responsibility principle
	- A class should have only a single responsibility
**O**
- Open/closed principle
	- Open for extension, but closed for modification
	- Alistair Cockburn: Indentify points of predicted variation and create a stable interface around them...
**L**
- Liskov substitution principle
	- Replace objects with instances of their subtypes without altering the correctness of that program
**I**
- Interface segregation principle
	- Many client-specific interfaces are better than one general-purpose interface
**D**
- Dependency inversion principle
	- Abstractions should not depend on details
	- Don't depend on anything concrete
		- Work with interfaces

fff