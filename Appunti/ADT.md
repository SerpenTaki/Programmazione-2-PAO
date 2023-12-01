
Un **Tipo di Dato Astratto** è un tipo di dato le cui istanze possono essere manipolate con modalità che dipendono esclusivamente dalla **_semantica_** del dato e non dalla sua **_implementazione_**.

*Tipo di dato le cui istanze possono essere modellate in base alle sue istanze e non in base all'implementazione, inoltre permette di distinguere l'interfaccia dalla sua implementazione.*

## Concetto 
**ADT = _valori + operazioni_**
- **Interfaccia** dell'ADT: metodi pubblici o operazioni proprie
- Rappresentazione interna dell'ADT **inaccessibile**
- Esempio di ADT: tipo primitivo `int`
- `struct` del C++ non rispetta il concetto di ADT *non essendoci nessun [[Information hiding]] posso operarci dentro e fare danni (che la funzione dedicata non farebbe)*

# come mai struct NON è una ADT
````C++
//Complessi.h

struct comp { double re, im;};

comp inizializzaComp(double, double);
double reale(comp);
double immag(comp);
comp somma(comp, comp);

/*!i complessi hanno 2 rappresentazioni polare ed immaginaria!*/

//Complessi.cpp
#include "complessi.h"

comp inizializzaComp(double re, double im){
	comp x;
	x.re = re; x.im = im;
	return x;
}

double reale(comp x){
	return x.re;
}

double immag(comp x){
	return x.im;
}

comp somma(comp x, comp y){
	comp z;
	z.re=x.re+y.re; z.im=x.im+y.im;
	return z;
}

````

![[Pasted image 20231003191451.png]]

- Concetto **OO** di **[[Classi]]** implementa gli ADT
- **Dichiarazione** dei membri della classe
	1. Campi dati
	2. Metodi
- **Definizione o implementazione** della classe
	- Definizione dei metodi

## Running example: [[classe orario]]