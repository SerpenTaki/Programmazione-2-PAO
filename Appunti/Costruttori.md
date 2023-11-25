````C++ 
orario mezzanotte;
mezzanotte.secc = 0; //Errore: sec è privato
````
Sarà mezzanotte o no?

Un **Costruttore** di una classe è un tipo speciale di funzione che viene chiamata per creare un oggetto. Prepara il nuovo oggetto per l'uso spesso ha degli argomenti che usa per costruire quell'oggetto.

**NB:** I costruttori sono dichiarati nella parte pubblica di una classe e hanno il nome della classe
````C++
class orario{
public:
	orario();//costruttore senza parametri detto costruttore di default
	...
};

orario::orario(){//definizione del costruttore di default
	sec = 0;
}

orario mezzanotte; //viene invocato il costruttore di default

cout << mezzanotte.Ore() << endl; //stampa 0
````

Si possono definire più costruttori purchè differiscano nella lista dei parametri, ovvero nel numero e/o tipo dei parametri. Si fa quindi **overloading** dell'identificatore del metodo che ha lo stesso nome della classe
[[classe orario]]
````C++
class orario{
public:
	orario(); //costruttore di default
	orario(int, int); //costruttore ore-minuti
	orario(int, int, int); // ore-minuti-secondi
	...
};
````

````C++

orario::orario() { //costruttore di default
	sec = 0;
};

orario::orario(int o, int m) {
	if ( o < 0 || o > 23 || m < 0 || m > 59)
		sec = 0;
	else sec = o * 3600 + m * 60;
};

orario::orario(int o, int m, int s){
	if ( o < 0 || o > 23 || m < 0 || m > 59 || s < 0 || s > 59)
		sec = 0;
	else sec = o * 3600 + m * 60 + s;
};

//Esempi uso dei costruttori
orario adesso_preciso(14,25,47);
	//usa il costruttore ore-minuti-secondi
orario adesso(14,25)
	//usa il costruttore ore-minuti
orario mezzanotte;
	//usa il costruttore senza parametri default
orario mezzanotte2; 
	//usa il costruttore senza parametri
orario troppo(27,25);
	//usa il costruttore ore-minuti

cout << adesso_preciso.Secondi() << endl; //stampa 47
cout << adesso.Minuti() << endl; //stampa 25
cout << mezzanotte.Ore() << endl; //stampa 0
cout << troppo.Ore() << endl; //stampa 0

````

*Esiste un modo alternativo per invocare i costruttori*:
````C++
orario adesso_preciso = orario(14,25,47);
orario adesso = orario(14,25);
orario mezzanotte = orario();
//sconsigliato fare questo lavoro perchè provoca la chiamata del costruttore di copia
````

In C e C++ possiamo inizializzare le variabili in 2 modi
````C
int x = 15;
int x(15);
````

Si tratta in questo caso di invocazioni del **COSTRUTTORE DI COPIA**.

Il **COSTRUTTORE DI COPIA** definisce le azione performate dal compilatore quando si copia una classe oggetto.

Viene invocato un costruttore anche quando si crea dinamicamente un oggetto sullo **heap** con la `new` e si cancella con `delete`.

````C++
orario* ptr = new orario;
orario* ptr1 = new orario(14,25);

cout << ptr->Ore() << endl; //stampa 0
cout << ptr1->Ore() << endl; //stampa 14
````

[[classe orario]]

## Costruttore Standard

````C++
class orario{
public:
	//nessuna definizione di costruttori
	...
};

orario o; //OK viene invocato il costruttore standard di default ma con un valore indefinito
````

````C++
class orario{
public:
	orario(int, int); //solo costruttore ore-minuti
	... //attenzione manca il costruttore standard se ne viene chiamato un altro
	//PS: al 99% delle volte "sempre" serve il costruttore di default
};

orario o; //ERRORE: manca un costruttore di default
````

Assegnazione e costruzione sono 2 cose diverse ad esempio
````C++
int x= y; //costruzione
x=y;//assegnazione
````

Altro esempio
````C++
orario adesso(11,25); //costruttore ore-minuti
orario copia; //costruttore di default
copia = adesso; //assegnazione
orario copia1 = adesso; //costruttore di copia analogo a int x 0 y;

orario copia2(adesso); //costruttore di copia analogo a int x(y);
````

### Costruttori come convertitori di tipo

**Costruttore**: `C(T)`
**Conversione implicita:** `T => C`
````C++
orario s; //invocazione del costruttore di default
s = 8; //viene assegnato 8
//MAI CONFONDERRE L'ASSEGNAZIONE CON IL COSTRUTTORE DI COPIA
````

Con l'assegnazione `s = 8;` succede che:
1. viene invocato il costruttore `orario(int)` con parametro attuale 8 che crea un **_oggetto anonimo temporaneo_** della classe `orario`
2. l'oggetto temporaneo viene assegnato all'oggetto `s`
3. viene "deallocato" l'oggetto temporaneo
````C++
orario s,t;
s = 8; //OK: equivale a s = orario(8)
t = 8+12; //OK: equivale a t = orario(8+12)
````

### Argomenti di default nelle funzioni

````C++
void F(double x, int n=3, string s); //ILLEGALE!!!
//i valori alla destra del valore a cui è stato assegnato il default devono avere anche loro un valore di default

void G(double x, int n=3, string s = "ciao");//ok

G(3.2); //OK: G(3.2,3,"ciao");
G(); //NO
G(3,3); //OK: G(3,3,"ciao");
G(3,3,"pippo"); //OK: G(3,3,"pippo");
 

orario::orario(int o = 0, int m = 0, int s = 0){
	if(o<0 || o>23 || m<0 || m>59 || s<0 || s>59)
		sec =0;
	else
		sec = o * 3600 + m *60 + s;
};

````

Costruttore a 0,1,2 e 3 parametri.
Agisce anche come convertitore di tipo da `int` a `orario`.

````C++
class orario{
	//costruttore a tre parametri con argomenti default
	orario(int =0, int =0, int =0);
	int ore(); //selettore delle ore
	int minuti(); //selettore dei minuti
	int secondi(); //selettore dei secondi
private:
	int sec;
};

//attenzione alle sintassi
orario::orario(int o, int m, int s){
	if(o<0 || o>23 || m<0 || m>59 || s<0 || s>59) sec=0;
	else sec = o*3600 + m*60 +s;
}

int orario::ore() {return sec/3600;}
int orario::minuti() {return (sec/60)%60;}
int orario::secondi() {return sec%60;}
````
esempi:
````C++
#include<iostream>
#include "orario.cpp"
using namespace std::cout;
using namespace std::endl;

int main(){
	orario s;
	s = 6; //equivale a: s = orario(6,0,0)
	cout << s.ore() << ':' << s.minuti() << ':' << s.secondi() << endl;
	orario t = 5+2*2; //equivale a: orario t = orario(5+2*2,0,0)
	cout << t.ore() << ':' << t.minuti() << ':' << t.secondi() << endl;
	orario e(12, 45); //equivale a: orario r(12,45,0)
	cout << r.ore() << ':' << r.minuti() << ':' << r.secondi() << endl;
	orario a; //equivale a: orario a(0,0,0)
	cout << a.ore() << ':' << a.minuti() << ':' << a.secondi() << endl;
	orario b(7);
	cout << b.ore() << ':' << b.minuti() << ':' << b.secondi() << endl;
}
````

## Operatori espliciti di conversione
In una classe C, operatore di conversione C => T
````C++
class orario{
public:
	operator int() {return sec;}//orario => int
	...
};

orario o(14,37);
int x = o; //OK: viene richiamato implicitamente il metodo int() su o
````
##### Parola chiave explicit
````C++
class orario{
public:
	explicit orario(int); //costruttore esplicito con un solo parametro
	...
};

orario o = 8; //ERRORE: non viene richiamato implicitamente il costruttore 
				// orario(8)
````
la parola chiave explicit **blocca** la conversione a volte è utile.

[[classe orario]] aggiungiamo 2 metodi pubblici con side effects

# Costruttore di Copia
Il costruttore di copia **`C(const C&)`** viene **invocato automaticamente** nei seguenti 3 casi:
1. Quando un oggetto viene dichiarato ed inizializzato con un altro oggetto della stessa classe come nei seguenti 2 casi:
````C++
orario adesso(14, 30);
orario copia = adesso; //inizializza copia
orario copia1(adesso); //inizializza copia1
````
2. Quando un oggetto viene **passato per valore** come parametro di una funzione, come in:
`ora = ora.Somma(DUE_ORE_E_UN_QUARTO);`
dove `Somma` è la funzione:
````C++
orario orario::Somma(orario o) const{
	orario aux;
	aux.sec = (sec + o.sec) % 86400;
	return aux;
}
````
3. Quando una funzione **ritorna per valore** tramite l'istruzione `return` un oggetto, come in
`return aux;` nella funzione precedente

==**ATTENZIONE AL CASO 3**==

Il compilatore g++ di **default** compie la seguente ottimizzazione:

"Lo standard C++ consente a un'implementazione **_di omettere la creazione di un temporaneo che viene utilizzato solo per inizializzare un altro oggetto dello stesso tipo_**. Specificando questa opzione si disabilita questa ottimizzazione e si obbliga g++ a chiamare il costruttore di copia in tutti i casi".

L'ottimizzazione è sottile: dice che ogni qualvolta si dovrebbe creare un oggetto temporaneo "*inutile*" usato solamente per inizializzare un nuovo oggetto dello stesso tipo, il temporaneo non viene creato.

_La specifica di tale ottimizzazione non è completamente deterministica e quindi a **fini didattici** spesso non considereremo tale ottimizzazione_ quindi:
` g++ -fno-elide-constructors` disabilita questa ottimizzazione nel compilatore.

````C++
C fun(C a) {return a;}

int main(){
	C c;
	fun(c); // 2 invocazione del costr. di copia

	C y = fun(c);
	//g++ => 2 sole invocazioni del costr. di copia e non 3!

	C z; z = fun(c);
	//2 invocazioni del costr. di copia

	fun(fun(c));
	//g++ => 3 sole invocazioni del costr. di copia e non 4!
}
````


[[classe orario#Funzionalità di stampa per oggetti orario]]

## Comportamento del costruttore
Consideriamo una classe **C** con campi dati $x1,...,x_k$ di qualsiasi tipo, possibilmente qualche altra classe. L'**ordine dei campi dati** è determinato dall'ordine in cui essi appaiono nella definizione della classe **C**. 

Supponiamo di definire nella classe **C** un qualsiasi costruttore come segue:
`C(tipo_1,..., Tipo_n) {//codice}`
Il comportamento di tale costruttore è il seguente:
1. Per ogni campo dati $x_j$ di **tipo non classe** $T_j$ (_ovvero di tipo primitivo o derivato_), viene allocato un corrispondente spazio in memoria per contenere un valore di tipo $T_j$ ma il valore viene lasciato indefinito;
2. Per ogni campo dati $x_i$ di **tipo classe** $Ti$ viene invocato il costruttore di default $Ti()$;
3. Alla fine, viene eseguito il **`codice`** del corpo del costruttore

**NB**: i punti 1 e 2 vengono eseguiti per tutti i campi dati $x1,...,x_k$ seguendo il loro ordine di dichiarazione.

````C++
class C{
private:
	int x;
public:
	C() {cout<< "C0 "; x=0;}
	C(int k) {cout << "C1 "; x=k;}
};
class D{
private:
	C c;
public:
	D d;
	C c2;
};

int main(){
	E x; cout << "UNO\n";
	D y; cout << "DUE\n";
	E* p = &x; cout << "TRE\n";
	D& a = y; cout << "Quattro";
}
````

aggiornamento...

In una classe **C** con lista ordinata di campi dati $x1,...,x_k$, un costruttore con lista di inizializzazione per i campi dati $x_i1,...,x_ij$ è definito tramite:
`C(T1,....,Tn): xi1(...),..., xij(...) {\\codice};`

Il comportamento del costruttore è:
1. Ordinatamente per ogni campo dati $xi (1 \leq i \leq k)$ viene richiamato un costruttore:
	- o esplicitamente tramite una chiamata ad un costruttore **xi(..)** definita nella lista di inizializzazione
	- oppure implicitamente (non appare nella lista di inizializzazione) tramite una chiamata al costruttore di default **xi()**
2. Quindi viene eseguito il codice del costruttore

**NOTA BENE**
1. Naturalmente, parliamo di costruttori e costruttori di copia anche per campi dati di tipo non classe (*primitivo o derivato*): la lista di inizializzazione può includere inizializzazione anche per questi campi dati.
2. La chiamata implicita al costruttore di default standard per un campo dati di tipo non classe, come al solito, alloca lo spazio in memoria ma lascia indefinito il valore.
3. L'ordine in cui vengono invocati i costruttori, esplicitamente o implicitamente, è sempre determinato dalla lista ordinata dei campi dati, qualsiasi sia l'ordine delle chiamate nella lista di inizializzazione.
## Invocazione esplicita del costruttore di copia
per il campo dati _costante_ `numero`.
`telefonata::telefonata() : numero(0) {}` LEGALE!! numero di telefono vuoto

È possibile richiamare esplicitamente un costruttore per qualsiasi campo dati:

```
telefonata::telefonata(orario i, orario f, int n) //costruttore di copia standard
							: inizio(i), fine(f), numero(n) {} //lista di inizializzazione
```

![[Pasted image 20231030190014.png]]
![[Pasted image 20231030190045.png]]
**ATTENZIONE SPRECO DI MEMORIA** da rigettare usiamo la terza ver
![[Pasted image 20231030190150.png]]

###### Ridefinizione costruttore di copia
[[Container#Copia superficiale]]
[[Container#Copie profonde]]

Definiamo una funzione esterna `orario Somma_Durate(bolletta b)` che restituisca la somma delle durate delle telefonata in `b`.
````C++
orario Somma_Durate(bolletta b){// NOTA: b passato per valore
	orario durata; // costruttore di default di orario
	while (!b.Vuota()){
		//estrae dal primo nodo della lista
		telefonata t = b.Estrai_Una();
		durata = durata + t.Fine() - t.Inizio();
	} //vincolo: durata < 24 ore!
	return durata;
}
````
La funzione esterna `Chiamate_A` rimuove dalla `bolletta b` passata per riferimento tutte le telefonate a `num` e restituisce una nuova bolletta contenente le telefonate tolte.
````C++
bolletta Chiamate_A(int num, bolletta& b){
	bolletta selezionate, resto; //oggetti locali
	while(!b.Vuota()){
		telefonata t = b.Estrai_Una();
		if(t.Numero() == num)
			selezionate.Aggiungi_Telefonata(t);
		else
			resto.Aggiungi_Telefonata(t);
	}
	b = resto; //overloading di operator= in bolletta
	return selezionate;
}
````
![[Pasted image 20231102172038.png]]
![[Pasted image 20231102172048.png]]
![[Pasted image 20231102172104.png]]
**Problema**:
1. Memoria di `resto` e `selezionate` non è deallocata
2. `return selezionate`: oggetto ritornato costruito di copia, la memoria non viene deallocata

#### Le copie profonde sono una soluzione ottimale?
-> Soluzione costosa, inaccettabile, *a volte inutile*

## Reference counting
Il conteggio dei riferimenti è una tecnica di memorizzazione del numero di *referenze, puntatori o maniglie* a una risorsa come un oggetto, un blocco di memoria, uno spazio su disco o un'altra risorsa. Può anche riferirsi, più specificamente, a un algoritmo di garbage collection che utilizza questi conteggi di riferimento per deallocare gli oggetti che non sono più referenziati. 

![[Pasted image 20231118172442.png]]

SI incapsula in una classe il puntatore `nodo*` e si ridefinisce assegnazione, costruttore di copia e distruttore. Si definisce un cosidetto *smart pointer*. Gli smart pointer dovranno essere dotati di una interfaccia pubblica che permetta all'utente di utilizzarli come fossero puntatori ordinari.

### Smart pointer
Un **puntatore intelligente** è un *tipo di dati astratto* che simula un *puntatore*, fornendo al contempo caratteristiche aggiuntive, come la *gestione automatica della memoria* o il *controllo dei limiti*. Tali caratteristiche hanno lo scopo di ridurre i bug causati dall'uso improprio dei puntatori, pur mantenendo l'efficienza. I puntatori intelligenti di solito tengono traccia della memoria a cui puntano e possono anche essere usati per gestire altre risorse, come le connessioni di rete e gli handle dei file. I puntatori intelligenti sono nati nel linguaggio di programmazione C++ 11.

# Costruttori nelle classe derivate
La lista di inizializzazione di un costruttore di una classe `D` derivata direttamente da `B` in generale può contenere invocazioni di costruttori per i campi dati (propri) di `D` e l'invocazione di un costruttore della classe base `B`.

L'esecuzione di un tale costruttore di `D` avviene nel seguente modo:
1. Viene sempre e comunque invocato per primo un costruttore della classe base `B`, o esplicitamente o implicitamente il costruttore di default di `B` quando la lista di inizializzazione non include una invocazione esplicita;
2. Successivamente, secondo il comportamento già noto, viene eseguito il costruttore "proprio" di `D`, ossia vengono costruiti i campi dati propri di `D`;
3. Infine viene eseguito il corpo del costruttore.

In particolare, se nella classe derivata `D` si omette qualsiasi costruttore allora, come al solito, è disponibile il **costruttore di default standard** di `D`. Il suo comportamento è quindi il seguente:
1) Richiama il costruttore di default di B;
2) Successivamente si comporta come il costruttore di default "proprio" di `D`, ossia richiama i costruttori per tutti i campi dati di `D`
````C++
dataora::dataora(): giorno(1), mese(1), anno(2000) {}

dataora d;
cout d.Ore(); //stampa: 0
cout d.Giorno(); //stampa: 1
````
È naturale definire il seguente costruttore con parametri per la classe derivata `dataora`
````C++
dataora::dataora(int a, int me, int g, int o, int m, int s) : orario(o,m,s), giorno(g), mese(me), anno(a) {}
````
````C++

````