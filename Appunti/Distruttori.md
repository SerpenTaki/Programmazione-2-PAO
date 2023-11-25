Nella programmazione orientata agli oggetti, un **_distruttore_ è un _metodo_ che viene invocato meccanicamente appena prima che la memoria dell'oggetto venga rilasciata**. Può accadere quando il suo ciclo di vita è legato all'ambito e l'esecuzione esce dall'ambito, quando è incorporato in un altro oggetto il cui ciclo di vita termina, o quando è stato allocato dinamicamente e viene rilasciato esplicitamente. Il suo scopo principale è quello di liberare le risorse (allocazioni di memoria, file o socket aperti, connessioni a database, lock di risorse, ecc.) che sono state acquisite dall'oggetto durante la sua vita e/o di cancellarlo da altre entità che possono mantenere riferimenti ad esso.

# Distruttore Standard
È sempre disponibile il **distruttore standard**: invoca il "*distruttore*" per tutti i campi dati della classe, **nell'ordine inverso** alla loro dichiarazione `~`
(*come se gli dovessi togliere da una pila praticamente....*)

**È accettabile il distruttore standard nella classe bolletta? NO**

Distruttore della classe [[Telefonata e Bolletta]]:
````C++
class bolletta{
public:
	..
	~bolletta(); //distruzione profonda....
	...
}

//first punta alla testa della lista
bolletta::˜bolletta() {distruggi(first);}
````

## Le regole di invocazione dei distruttori
- per gli **oggetti di classe statica**, al termine del programma (all'uscita dalla funzione principale `main()`)
- per gli **oggetti di classe automatica** definiti in un blocco, all'uscita dal blocco in cui sono definiti. In particolare, ciò vale per i parametri formali della funzione
- per gli **oggetti dinamici** (*allocati sullo heap*), quando viene invocato l'operatore di `delete` su un puntatore ad essi.
- Per gli oggetti che sono **campi dati** di un oggetto `x`, quando `x` viene distrutto
- Gli **oggetti con lo stesso tempo di vita**, tipicamente oggetti definiti nello stesso blocco oppure oggetti statici di una classe, vengono distrutti nell'ordine inverso a quello in cui sono stati creati

In particolare, il distruttore viene invocato:
1. sui **parametri** di una funzione **passati per valore** all'uscita dalla funzione
2. sulle **variabili locali** di una funzione all'uscita dalla funzione
3. **Sull'oggetto anonimo ritornato per valore** da una funzione non appena esso sia stato usato (*se qualche ottimizzazione prolunga il tempo di vita dell'oggetto anonimo ritornato significa che non viene invocato il distruttore*)

## Comportamento del distruttore

Supponiamo che la lista ordinata dei campi dati di una classe `C` sia $x1,..,xn$. Quando viene distrutto un oggetto di tipo `C`, viene invocato automaticamente il distruttore della classe `C`, standard oppure ridefinito, con il seguente comportamento:
1. innanzitutto viene eseguito il corpo del distruttore della classe `C`, se questo esiste
2. Vengono quindi richiamati i distruttori per i campi dati nell'ordine inverso alla loro lista di dichiarazione, cioè $xn,...,x1$. Per un campo dati di tipo non classe (cioè primitivo o derivato) viene semplicemente rilasciata la memoria (È il *distruttore standard* dei tipi non classe) mentre per i tipi classe viene invocato il distruttore standard oppure ridefinito.

==**_Distruttore Standard_**==: semplicemente ha il corpo vuoto. Quindi il distruttore standard di una classe `C` si limita a richiamare i distruttori per i campi dati di `C` in ordine inverso di dichiarazione.

Il distruttore di `bolletta` richiama il metodo statico privato

````C++
bolletta::distruggi(nodo* p){
	if(p){
		distruggi(p->next);
		delete p;
	}
}
````

che a sua volta esegue l'operatore `delete` su tutti gli elementi della lista.

**Cosa succede**:
1. L'istruzione `delete p;` provoca l'invocazione del *distruttore della classe `nodo`*, e poichè esso non è stato ridefinito viene richiamato il distruttore standard di `nodo`.
2. Il distruttore standard della classe `nodo`, cioè `info` e `next`, i rispettivi distruttori. Il campo puntatore `next` viene semplicemente deallocato, mentre per il campo `info` viene invocato il distruttore della classe `telefonata`, e siccome neanche esso è stato ridefinito verrà richiamato il distruttore standard di `telefonata`
3. Il distruttore standard della classe `telefonata` dealloca l'intero `numero` e richiama il distruttore della classe `orario` per i campi `inizio` e `fine`, che sarà quindi il distruttore standard di `orario`.
4. Il distruttore standard della classe `orario` dealloca il campo dati intero `sec`.

Modo più elegante: ridefinire il distruttore della classe `nodo` in modo che esso provveda a distruggere l'oggetto puntato da `next`

````C++
bolletta::nodo::˜nodo()
//invocazione automatica distruttore di telefonata
//deallocazione automatica puntatore next
{
	if (next != 0)
		delete next; //chiamata ricorsiva
}
````
In questo modo il distruttore `bolletta` diventa:
`bolletta::˜bolletta() { if(first) delete first; }`


# La regola del 3 (C++)

La **regola del tre** è una regola empirica del C++ (prima del C++11) che sostiene che se una classe definisce uno qualsiasi dei seguenti elementi, probabilmente dovrebbe definirli esplicitamente tutti e tre:
- distruttore
- costruttore di copia
- operatore di assegnazione di copia
````
int arrayStatico[5] = {3,2,-3};
int* arrayDinamico = new int[5];
arrayDinamico[0] = 3;
*(arrayDinamico+1) = 2;
delete[] arrayDinamico;
````

**ARRAY DI OGGETTI**
- Array statici e dinamici
- Costruzione di array
- Distruzione di array

````C++
class C{
public:
	int i;
	C(int x = 3) : i(x) {}
	˜C() {cout << i << "˜C";}
};

int main(){
	C a[4] = {C(1), C(), C(8)};
	//distruzione oggetti anonimi, stampa: 8˜C 3˜C 1˜C
	cout << a[0].i << a[2].i << a[3].i <<endl;
	//stampa: 1383	
}
// all'usita stampa: 3˜C 8˜C 3˜C 1˜C
````

## Back to information hiding
[[Information hiding]]

**Come nascondere la parte privata**
````C++
class C {
public:
	//parte pubblica
private:
	//parte privata
};
````
Vogliamo nascondere fisicamente la parte privata della dichiarazione di `C` all'utente finale

````C++
// file C_handle.h
class C_handle{
public:
	//parte pubblica
private:
	class C_privata; //dichiarazione incompleta
	C_privata* punt; //solo punt. e ref. per dichiarazione incompleta
}
````
Nell'implementazione separata di `C_handle` sarà definita la classe `C_privata` contenente la parte privata di C
````C++
// file C_handle.cpp
class C_handle::C_privata{
	//parte privata
};
````

**Dichiarazioni incomplete**
Una classe **`C`** può dichiarare ed usare puntatori e reference ad una classe `D` che viene meramente dichiarata. Si tratta di una cosidetta *dichiarazione incompleta* della classe `D`
````C++
class D; //dichiarazione incompleta

class C{
	D* p; //campo dati
	D* m(); //tipo di ritorno
	void n(...,D*,...); //parametro
	D& f(...);
	...
};

class D {
... //definizione della classe
};
````
**ATTENZIONE**: In una classe `C` una dichiarazione che la classe `D` è amica di `C` funge anche da dichiarazione incompleta di `D`.

````C++
//File orario.h
#ifndef ORARIO_H
#define ORARIO_H
#include <iostream>
using std::ostream;

class orario{
public:
	orario (int =0, int =0, int =0);
	int Ore() const;
	int Minuti() const;
	int Secondi() const;
	void AvanzaUnOra();
private:
	class orario_rappr;
	orario_rappr* punt; //oggetti allocati sullo heap
};
osteeam& operator<<(ostream&, const orario&);
#endif

//file orario.cpp
#include "orario.h"

class orario::orario_rappr{
public:
	int sec;
}; //basta il costruttore di default standard

orario::orario(int o, int m, int s) : punt(new orario_rappr){
	if(o<0 || o>24 || m<0 || m>60 || s<0 || s>60)
		punt->sec = 0;
	else punt->sec 0 o*3600 + m*60 +s;
}

int orario::Ore() const{
	return punt->sec / 3600;
}

int orario::Minuti() const{
	return (punt->sec - (punt->sec / 3600)*3600) / 60;
}

int orario::Secondi() const{
	return punt->sec % 60;
}

void orario::AvanzaUnOra(){
	punt->sec = (punt->sec + 3600) % 86400;
}

ostream& operator<<(ostream& os, const orario& t){
	return os << t.Ore() << ':' << t.Minuti() << ':' << t.Secondi();
}
````
Con questa tecnica si possono verificare problemi di interferenza!
````C++
orario t1(17,11,27), t2;
cout << t1 << ' ' << t2 << endl;
// stampa: 17:11:27 0:0:0
t2 = t1; //stesso puntatore punt in t2 e t1
cout << t1 << ' ' << t2 << endl;
//stampa: 18:11:27 18:11:27
````
Sarà quindi necessario ridefinire adeguatamente assegnazione, costruttore di copia e distruttore di `orario`
````C++
ostream& operator<<(ostream& os, bolletta b){
	//NOTA BENE: b passato per valore
	os << "TELEFONATE IN BOLLETTA" << endl;
	int i = 1;
	while (!b.Vuota()) {
		os << i << ') ' << b.Estrai_Una() << endl;
		i++;
	}
	return os;
}
````

[[Amicizia]]

# Distruttore standard nelle classi derivate



