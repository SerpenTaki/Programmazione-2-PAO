I metodi della classe `orario` che abbiamo considerato finora sono stati pensati per operare su di uno specifico oggetto, l'oggetto di invocazione. Quindi scriviamo
````C++
orario adesso(14,33);
cout << adesso.Minuti();
````
intendiamo stampare i minuti dello specifico oggetto `adesso`. Potremmo avere l'esigenza che la classe `orario` ci fornisca un valore `OraDiPranzo` di tipo `orario` che sia sempre lo stesso, una specie di costante della classe `orario`. Per ottenere ciò potremmo definire un metodo costante `OraDiPranzo()` che ritorna un oggetto della classe `orario`.
````C++
class orario{
public:
	orario OraDiPranzo() const;
	...
};

orario orario::OraDiPranzo() const {return orario(13,15);}
````
Notiamo che in questo modo per stampare `OraDiPranzo` abbiamo bisogno di qualche oggetto di tipo Orario da usare come oggetto di invocazione anche se tale oggetto non verrà comunque usato dal metodo `OraDiPranzo()`.
````C++
const orario inutile;
cout << "Si pranza alle " << inutile.OraDiPranzo().Ore() << " e " << inutile.OraDiPranzo().Minuti() << "minuti";
````
# Funzione Static
La dichiarazione `static` permette di associare sia metodi che campi dati all'intera classe invece che a singoli oggetti della classe. **Dichiareremo `static` quando l'azione del metodo è indipendente dall'oggetto di invocazione**, *cioè quando l'oggetto d'invocazione non è necessario per la definizione del metodo*
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
Esternamente alla classe si invoca il metodo statico premettendo al nome del metodo il nome della classe e l'operatore di scoping "`::`". *Ho bisogno della classe che lo ospita, usando l'operatore di scoping*.
````C++
cout << "Si pranza alle" << orario::OraDiPranzo().Ore() << " e " << orario::OraDiPranzo().Minuti() << " minuti\n";
````

**ATTENZIONE**: nei metodi statici non ha senso il **this** [[Programmazione orientata agli oggetti#la keyword this]]

## Campi dati statici (o di classe)
- Nelle implementazioni degli altri metodi della classe i metodi dichiarati `static` si possono comunque invocare senza l'operatore di scoping `classe::`.
- Anche un campo dati di una classe può essere dichiarato `static`. Quando viene costruito un oggetto di una classe non viene allocata memoria per i suoi campi dati statici.
	- La memoria per i campi dati statici è unica per tutti gli oggetti ed è allocata una volta per tutte all'inizio

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
