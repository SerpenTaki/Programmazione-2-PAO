# Funzione Static

````C++
class orario {
public:
	static orario OraDiPranzo(); //metodo statico
	//il modificatore const non ha senso per un metodo statico perchè il metodo OraDiPranzo non ha un oggetto di invocazione
	...
};

orario orario::OraDiPranzo(){
	return orario(13,15);
};
````

Esternamente alla classa si invoca il metodo statico premettendo al nome del metodo il nome della classe e l'operatore di scoping "`::`"
````C++
cout << "Si pranza alle" << orario::OraDiPranzo().Ore() << " e " << orario::OraDiPranzo().Minuti() << " minuti\n";
````

**ATTENZIONE**: nei metodi statici non ha senso il **this** [[Programmazione orientata agli oggetti#la keyword this]]

## Campi dati statici (o di classe)

L'inizializzazione dei campi dati statici si deve fare all'esterno della classe ed è **sempre** richiesta.

````C++
class orario{
public:
	...
	static int Sec_di_una_Ora;
	static int Sec_di_un_Giorno;
	...
};

//esternamente alla classe orario
int orario::Sec_di_una_Ora = 3600;
int orario::Sec_di_un_Giorno = 86400;
````

**Unica copia in memoria dei campi dati statici!!**

Se un membro di dati *statico* è di tipo *const* integrale o *const* enumerativo, la sua dichiarazione nella definizione della classe può specificare un *const-initializer* che deve essere un'espressione costante integrale.
````C++
class orario{
public:
	...
	static const int Sec_di_una_Ora = 3600;
	//legale vale solo per tipi integrali non vale per un double
	...
};
````

Spesso i campi dati statici sono costanti, perchè servono, tipo pi greco o logaritmi importanti. E quelli non sono lì per essere modificati..

**Esempio: contare gli oggetti istanziati**
````C++
#include<iostream>
using namespace std;
class C{
	int dato; //privato
public:
	C(int); //costruttore ad un argomento
	static int cont;//campo dati statico pubblico
};

int C::cont = 0; //inizializzazione campo dati statico

C::C(int n) {cont++; dato=n;} //definizione costruttore

int main(){
	C c1(1), c2(2);
	cout << C::cont; //stampa 2
}
````

[[classe orario#Metodo orario somma(orario)]]

## Static variable

Nella programmazione informatica, una **variabile _statica_** è una variabile che è stata allocata "staticamente", il che significa che **la sua durata (o "estensione") è _l'intera esecuzione del programma_**. Ciò è in contrasto con le variabili automatiche a vita più breve, la cui memoria è allocata e deallocata sullo stack delle chiamate, e con gli oggetti, la cui memoria è allocata e deallocata dinamicamente nella memoria heap.

[[Programmazione orientata agli oggetti#Tempo di vita delle variabili]]
