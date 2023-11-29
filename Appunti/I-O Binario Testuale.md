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
