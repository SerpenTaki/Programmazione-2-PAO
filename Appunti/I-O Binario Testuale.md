I/O mediante l'astrazione di dispositivo di I/O detta "**stream** *sequenza (non limitata) di celle ciascuna contenente un byte*"
````mermaid
flowchart TD
A[Input Source] --> B{C++ program}
B --> C[Output Sink]
````
**Formati di dato interno**:
- Text: char
- int, float, double etc..
**Formati di dato esterno:**
- Testo secondo diverse codifiche (US-ASCII, ISO-8859-1,UTF-8, UTF-16 etc)
- Binario (bit crudi)

- La posizione dellle celle di uno stream **parte da 0**
- I/O effettivo avviene tramite un **buffer** associato allo stream
- Uno stream può trovarsi nello stato di **end-of-file**

Uno stream può trovarsi in 8($=2^3$) stati di funzionamento diversi. Lo stato è un intero in [0,7] rappresentato dal campo dati `state` della classe base `ios` che corrisponde al numero binario `bad fail eof` dove bad, fail e eof sono dei bit (0 e 1) di stato:
- `eof==1` <-> Lo stream è nella posizione di *end-of-file*.
- `fail==1`<-> La precedente operazione sullo stream è fallita: si tratta di un *errore senza perdita di dati*, normalmente è possibile continuare. Ad esempio, ci si aspettava in `int` e si trova invece un `double`.
- `bad==1` <-> la precedente operazione sullo stream è fallita con perdita dei dati: è un **errore fatale/fisico**, normalmente non è possibile continuare. Ad esempio, cerco di accedere ad un file o ad una network connection inesistenti
### La classe ios
`ios` (derivata da `ios_base`) è la *classe base astratta "virtuale"* della gerarchia che permette di controllare lo ==stato di funzionamento di uno stream==. Per quanto concerne lo stato di uno stream, la dichiarazione della classe `ios` è la seguente:
````C++
class ios: public ios_base {
	int state;
public:
	enum io_state {goodbit=0, eofbit=1, failbit=2, badbit=4};
	int good() const; //ritorna 1 se lo stato è good
	int eof() const; //ritorna il bit eof
	int fail() const; //ritorna il bit fail
	int bad() const; //ritorna il bit bad
	int rdstate() const; //ritorna lo stato come int in [0,7]
	void clear(int i=0); //setta lo stato i
	...
};
````
### La classe istream
Gli oggetti della sottoclasse `istream` rappresentano **stream di input**. `cin` è un oggetto di `istream` che rappresenta lo standard input.
## Gerarchia di classi per l'I/O
*//i rombi rappresentano la classe virtuale, in questo caso le classi `istream e ostream` sono collegate a `ios` tramite virtual derivation*
````mermaid
flowchart TD
	A[fstream] --> B[iostream]
	C[stringstream] --> B
	B --> D[istream]
	B --> E[ostream]
	F[ifstream] --> D
	G[istringstream] --> D
	H[ofstream] --> E
	I[ostringstream] --> E
	D --> L{ios}
	E --> L
````
`istream` include l'overloading dell'operatore di input `operator>>` per i tipi primitivi e per gli array di caratteri.
````C++
class istream: public virtual ios {
public:
	// metodi interni (con istream di invocazione)
	istream& operator>>(bool&);
	istream& operator>>(int&);
	istream& operator>>(double&);
	...
};
//funzioni esterne in std:
istream& std::operator>>(istream&, char&); //byte
istream& std::operator>>(istream&, char*); //stringhe
````
Tutti gli operatori di input **ignorano le spaziature** (cioè spazi, tab, enter) presenti prima del valore da prelevare. Quando una **operazione di input fallisce `fail==1` non viene effettuato alcun prelievo** dallo stream e la variabile argomento di `operator>>` non subisce modifiche.
###### Example
`operator>>(double& val)` preleva dallo istream di invocazione una sequenza di caratteri che rispetta la sintassi dei litterali di `double` e converte tale sequenza nella rappresentazione numerica di `double` assegnandolo  a `val`. Se la sequenza di caratteri non soddisfa la sintassi prevista per il `double`, l'operazione è nulla e l'istream va in uno stato di errore recuperabile:
`fail==1 e bad==0`

Definire un overloading di `operator>>` per qualche *classe `C`* significa dare un significato alla conversione *sequenza di byte => oggetto di C*. Cioè significa fare del **parsing** di una sequenza di byte di input secondo le regole di rappresentazione sintattica degli oggetti di C.
#### Parsing:
è un processo che analizza un flusso continuo di dati in ingresso. Un **parser** è un programma che esegue questo compito.
`oprator>>(isttream& is, char* s)` preleva dallo istream `is` una sequenza di caratteri fino ad incontrare il carattere spazio, a questa sequenza viene aggiunto in coda il carattere nullo (*codice ASCII 0*) e viene quindi fatta puntare dal puntatore `s`. 
-> Quando una operazione di input fallisce (fail=1) non viene effettuato alcun prelievo dallo stream e la variabile di `operator>>` non subisce modifiche.
###### Parsing di un oggetto nel piano reale rappresentato testualmente in forma cartesiana
````C++
class Punto{
	friend istream& operator>>(istream&, Punto&);
	//legge nel formato (x1,x2): rappresentazione testuale di Punto
private:
	double x, y;
};

//algoritmo di parsing
istream& operator>>(istream& in, Punto& p) {
	char cc; in >> cc; //std::operator>>(istream&, char&)
	if (cc=='q') return in; //carattere q per uscire
	if (cc != '(')) { in.clear(ios::failbit); return in;}
	else {
		in >> p.x; //istream::operator>>(double&)
		if(!in.good()) { in.clear(ios::failbit); return in;}
		in >> cc;
		if(cc != ',') { in.clear(ios::failbit); return in;}
		else {
			in >> p.y; //istream::operator>>(double&)
			if(!in.good()) { in.clear(ios::failbit); return in;}
			in >> cc;
			if(cc != ')') { in.clear(ios::failbit); return in;}
		}
	}
	return in;
}
//FILE.cpp
#incude "Punto.h"
using std::cin; using std::cout;

int main() {
	Punto p;
	cout << "Inserisci un punto nel formato (x,y) {'q' per uscire}\n";
	while(cin.good()) { //while(stato == 0)
		cin >> p;
		if(cin.fail()) {
			cout << "Input non valido, ripetere!\n";
			cin.clear(ios::goodbit);
			char c=0;
			// 10 è il codice ASCII del carattere newline
			while(c!=10) {cin.get(c);} //svuota cin, get() per input binario
			cin.clear(ios::goodbit);
		}
		else cin.clear(ios::eofbit); //stato 1
	}
}
````
### La classe ostream
Gli oggetti della sottoclasse ostream rappresentano **stream di output**, `cout` e `cerr` sono oggetti di ostream (*standard output ed error*).

La classe ostream include l'overloading dell'operatore di output `operator<<` per i tipi primitivi e per gli array di caratteri costanti.
````C++
class ostream: public virtual ios {
public:
	//metodi interni (con ostream di invocazione)
	ostream& operator<<(bool);
	ostream& operator<<(int);
	ostream& operator<<(double);
	...
};
//funzioni esterne
ostream& std::operator<<(ostream&, char); //byte
ostream& std::operator<<(ostream&, const char*); //stringhe
````
Questi operatori convertono valori di tipo primitivo in sequenze di caratteri che vengono scritti (immessi) nelle celle dell'ostream di invocazione. Per quanto riguarda l'output di stringhe, i caratteri della stringa vengono scritti nell'ostream fino al carattere nullo escluso.

### I/O testuale e binario
L'input/output sugli stream tramite gli operatori di input/output >> e << considerano gli stream nel cosiddetto *formato testo*.
````
T x;
cin >> x;
/*conversione dalla rappresentazione testuale di T alla rappresentazione binaria in memoria di T */
cout << x;
/* conversione dalla rappresentazione binaria in memoria di T alla rappresentazione testuale di T */
````
Quindi l'informazione da leggere o scrivere su uno stream deve avere una **natura testuale**. Spesso ciò non è vero (almeno in modo naturale). In questo caso, possiamo considerare lo stream in *formato binario*, cioè tutti i singoli caratteri dello stream vengono trattati allo stesso modo **senza alcuna interpretazione**.

L'**input binario** da uno istream, cioè carattere per carattere (byte per byte senza interpretazione per i byte) può essere fatto tramite alcuni metodi di "*get()*" di istream.
````C++
class istream: public virtual ios{
public:
	int get();
	istream& get(char& c);
	istream& read(char* p, int n);
	istream& ignore(int n=1, int e = EOF);
}
````
Il metodo `int get()` preleva un singolo carattere (1 byte) dall'istream di invocazione e lo restituisce convertito ad intero in [0,255]. Se si è tentato di leggere EOF ritorna -1.
Il metodo `get(char& c)` invece memorizza in `c` il carattere prelevato, se questo esiste.
Il metodo `read(char* p, int n)` preleva dall'istream di invocazione `n` caratteri, a meno che non incontri prima EOF, e li memorizza in una stringa puntata da `p`.
Il metodo `ignore(int n, int e=EOF)` effetua il prelievo di `n` caratteri ma non li memorizza.

L'**output binario** su uno ostream può essere fatto tramite i seguenti metodi di "put()" di ostream.
````C++
class ostream: public virtual ios{
public:
	ostream& put(char c);
	ostream& write(const char* p, int n);
	...
}
````
Il metodo `put(char c)` scrive il carattere `c` nello ostream di invocazione.
Il metodo `write(const char*p, int n)` scrive sullo ostream di invocazione i primi `n` caratteri della stringa puntata da `p`.
### Stream di file
Gli stream associati a file sono oggetti delle classi `ifstream, ofstream e fstream`. Sono disponibili diversi costruttori, i più comuni sono:
````C++
ifstream(const char* nomefile, int modalita=ios::in);
ofstream(const char* nomefile, int modalita=ios::out);
fstream(const char* nomefile, int modalita=ios::in | ios::out);
````
La stringa `nomefile` è il nome del file associato allo stream, mentre le modalità di apertura dello stream sono specificate da un tipo enum nella classe base `ios`
````C++
class ios{
public:
	enum openmode {
	in, //apertura in lettura
	out, //apertura in scrittura
	ate, //spostamento a EOF dopo l'apertura
	app, //spostamento a EOF prima di ogni write
	trunc, //erase file all'apertura
	binary, //apertura in binary mode, default text mode
	};
...
}
````
Le modalità di apertura di uno stream su file possono essere combinate tramite l'`OR` bitwise `|`
Per default, gli oggetti di ifstream sono aperti in lettura mentre quelli di ofstream sono aperti in scrittura. Un fstream può essere aperto sia in lettura che in scrittura.
````C++
fstream file("dati.txt", ios::out);
if (file.fail()) cout << "Errore in apertura\n";
````
Apre il file "*dati.txt*" in I/O.
````C++
ofstream file("dati.txt", ios::nocreate|ios::binary);
if (file.bad()) cout << "Il file non esiste\n";
````
il file "*dati.txt*" viene aperto in modalità binaria di append alla fine.
**Chiusura di un file**: il metodo `close()` chiude esplicitamente un file; viene automaticamente invocato dallo stream.
````C++
class ios{
public:
	enum openmode{
	in, //apertura in lettura
	out, //apertura in scrittura
	ate, //apertura a EOF dopo l'apertura
	app, //spostamento a EOF prima di ogni write
	trunc, //erase file all'apertura
	binary, //apertura in binary mode, default text mode
	};
...
}
````
Le modalità di apertura di uno stream su file possono essere combinate tramite l'`OR` bitwise `|`.
Per default, gli oggetti di ifstream sono aperti in lettura mentre quelli di ostream sono aperti in scrittura. Un fstream può essere aperto sia in lettura che in scrittura.

### Stream di stringhe
Si possono definire *stream associati a stringhe*, ossia sequenze di caratteri memorizzate in RAM. Il carattere nullo di terminazione gioca il ruolo di marcatore di fine stream.

Le classi da utilizzare sono `istringstream, ostringstream e stringstream` il file header che le dichiara è `<sstream>`. I costruttori sono i seguenti.
````C++
istringstream(const char* initial, int = ios::in);
ostringstream(int = ios::out);
ostringstream(const char* initial, int = ios::out);
stringstream(int = ios::in|ios::out);
stringstream(const char* initial, int = ios::in|ios::out);
````
I metodi di scrittura/lettura sono quelli ereditati da istream, ostream e iostream. Il metodo `str()` applicato ad uno stream di stringhe ritorna la stringa associata allo stream. Ad esempio:
````C++
#include<iostream>
#include<sstream>
using namespace std;

int main(){
	stringstream ss;
	ss << 236 << ' ' << 3.14 << " pippo "; //output su stringstream
	cout << ss.tellp() << ' ' << ss.tellg() << endl;
	/*
	Posizioni di testina di output e input: 17 0
	la stringa in memoria è: "236 3.14 pippo "
	la testina di output è avanzata alle fine ios::end
	la testina di input è ancora a ios::beg
	*/
	int i; ss >> i; //input da stringstream
	cout << i << endl; //stampa 236
	double d; ss >> d; cout << d << endl; //stampa 3.14
	string s; ss >> s; cout << "*\n"; //stampa *pippo*
}
````
A cosa può servire?
Ad implementare I/O mediante `operator>>` ed `operator<<` su stringhe, ad esempio fornite dall'interazione con una GUI.
