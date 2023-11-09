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




