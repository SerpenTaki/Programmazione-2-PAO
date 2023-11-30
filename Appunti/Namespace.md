Nella programmazione modulare c'è un problema *inquinamento dello spazio dei nomi*. Ovvero di variabili e nomi di funzioni. **I nomi sono _Estremamente Importanti_ quindi _vanno_ scelti bene**.

````C++

//file Complex.h
struct Complex {
...//implementazione1
};

double module(Complex);
//end file


//qualche altro file
#include "Complex.h"

//dichiarazione illegale
struct Complex {
... //implementazione2
}

void f(..){
//vorrebbe usare entrambi i complex (sia cartesiano che polare)
//È un altro tipo di problema di inquinamento dei nomi
}

````

Il meccanismo dei **Namespace** (*non disponibile in C)* permette di incaspulare dei nomi che altrimenti inquinerebbero il namespace globale

````C++

//file Lib_UNO.h
namespace Spazio_UNO {
	struct Complex{};
	void f(Complex c){};
};

//file Lib_due
namespace Spazio_DUE {
	struct Complex{};
	void g(Complex c){};
};

//main

#include "Lib_UNO.h"
#include "Lib_due.h"

void funzione() {
	Spazio_UNO::Complex var1; Spazio_UNO::f(var1);
	Spazio_DUE::Complex var2; Spazio_DUE::g(var2);
	Spazio_DUE::g(var1); //ERRORE IN COMPILAZIONE QUI!!!! ERRORE DI TIPO
	//g richiede il tipo di complex di spazio 2 non un altra variabile
	//il C++ è fortemente tippato quindi attenzione
}
````

Operatore di **scoping** : `namespace::nome_dichiarazione;`

Dato che potrebbe risultare scomodo riutilizzare tante volte l'operatore di _scoping_ possiamo applicare diverse soluzioni:

1. Soluzione  **_Alias_ di namespace**

````C++

#include "lib_uno.h"
#include "lib_due.h"

namespace UNO = Spazio_UNO;
namespace DUE = Spazio_DUE;

void funzione(){
	UNO::Complex var1; UNO::f(var1);
	DUE::Complex var2; DUE::g(var2);
}
````

2. Soluzione **Dichiarazione d'uso**
	rende visibile in un namespace una singola dichiarazione.

````C++
#include "lib_UNO.h"
#include "lib_DUE.h"

using Spazio_UNO::Complex;
using Spazio_DUE::g;

void funzione(){
Complex var1; Spazio_UNO::f(var1);
Spazio_DUE::Complex var2; g(var2);
}
//Possiamo usare ciò che ci serve

//ESEMPIO 2
#include <iostream>
using std::cout;
using std::endl;

int main(){
 cout << "Ciao!" << endl; //compila perfettamente
}
````

3. Soluzione **Direttiva d'uso**
	`using namespace` È una cannonata non consigliata per rendere i nomi dichiarati visibile, meglio una dichiarazione d'uso.
````C++
#include "lib_UNO.h"

using namespace Spazio_UNO; //apro il recinto rendo visibili tutti i nomi del namespace Spazio_UNO

void funzione(){
Complex var1; f(var1);
}//È una cannonata
````

Le componenti di tutte le librerie del C++ standard sono dichiarate in un namespace chiamato `std`. 
````C++
#include <iostream>

int main(){
	cout << "hello" << endl;
}
//non compila
// 'cout' undeclared
// 'endl' undeclared
````
