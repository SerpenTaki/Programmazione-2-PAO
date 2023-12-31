È una libreria di classi contenitore, di classi iteratore e di algoritmi su tali classi. STL è una libreria generica, cioè i suoi membri, classi e funzioni, sono dei template.
# Vector
È il più semplice contenitore di STL e per la maggioranza delle applicazioni è il più efficiente. È un template di classe che generalizza gli array dinamici.

Caratteristiche di **_vector_**: (*array dinamico*)
1. È un contenitore che supporta **l'accesso casuale** agli elementi (accesso in posizione arbitraria in *tempo costante*)
2. Inserimento e rimozione in *coda* in **tempo _ammortizzato_ costante**
3. Inserimento e rimozione *arbitraria* in **tempo lineare _ammortizzato_**
4. La **capacità** di un vector può variare dinamicamente
5. La gestione della memoria è **automatica**

````C++
template <class _Tp, class _Alloc = __STL_DEFAULT_ALLOCATOR(_Tp)>
class vector : protected _Vector_base<_Tp, _Alloc>
{
...
}
````
`vector` è un [[Template#Template di classe]] con 2 parametri di tipo ed un parametro di default per il secondo parametro di tipo.

Ci sono 2 modi diversi di usare un `vector`: lo stile array ereditato dal C e lo stile [[STL]] più consono al C++
````C++
int a[10]; //array
vector<int> v(10); //costruttore ad un argomento
					//vector(size_type)
					//con costruzione di default per gli elementi
````
Si può accedere agli elementi di un `vector` con l'operatore di indicizzazione `operator[]`
````C++
int n = 5;
vector <int> v(n);
int a[n] = {2,4,5,2,-2};
for(int i = 0; i < n; i++)
	v[i] = a[i] + 1;
````
````C++
vector<string> v(10), w;
cout << v.size() << " " << v.capacity(); // 10 10
vector<string> u(v); //costruzione di copia
w = u; //assegnazione
````
Il metodo `size()` ritorna il numero di elementi correnti contenuti nel vector. Il metodo `capacity()` ritorna invece la capacità del vector, quindi il numero massimo prima di dover ridimensionarsi (*ogni ridimensionamento raddoppia la capacità. Nuova allocazione, copia e deallocazione del vecchio vettore*).
**Invariante**: `v.size() <= v.capacity() == true`
````C++
template <class T>
void stampa(const vector<T>& v){
	for(int i = 0; i < v.size(); i++)
		cout << v[i] << endl;
}
````
Il costruttore `vector(size_type)` costruisce un vector i cui elementi sono inizializzati con il **costruttore di default**. Il costruttore `vector(size_type n, const T& t)` permette invece di specificare un valore iniziale `t` da cui sono costruiti di copia tutti gli elementi.
`vector <int> ivec(10,-1);`
In C++03 **non** è possibile inizializzare un `vector` con una data sequenza di valori, diventa invece possibile in C++11.
````C++
int ia[6] = {-1,5,-7,0,12,3}; //OK
vector <int> ivec(6) = {-1,5,-7,0,12,3}; //NO C++03
vector <int> ivec(6) = {-1,5,-7,0,12,3}; //OK C++11
````
#### Alcuni metodi di vector
````
// std::vector
void push_back(const T&)
void pop_back()
T& front() //!!!!!!! IMPORTANTI
T& back() //!!!!!!!!! FONDAMENTALI
iterator begin()
iterator end()
````

`void push_back(const T&):` principale metodo di inserimento in (coda ad) un vector, il nuovo elemento inserito è creato con il costruttore di copia.
````C++
int main(){
	vector <string> sv; string x;
	while (cin >> x) sv.push_back(x);
	/*legge stringhe da cin, separate da spazi, tab o enter fino a end_of_file
	e le inserisce in coda a sv.
	Da tastiera end_of_file si invia con una combinazione particolare:
	normalemente <Ctrl>+<d>*/
	cout << endl << "Abbiamo letto:" << endl;
	for(int i = 0; i < sv.size(); i++)
		cout << sv[i] << endl;
}
````
###### size vs capacity
````C++
#include <iostream>
#include <vector>

int main(){
	std::vector<int> myvector;

	for(int i=0; i<100;i++) myvector.push_back(i);

	std::cout << "size: " << myvector.size() << '\n';
	std::cout << "capacity: " << myvector.capacity() << '\n';
}
````

In modo analogo leggiamo le stringhe di un file separate da spazi, tab o enter e memorizzarle in un vector
````C++
int main() {
	vector<string> sv;
	string x;
	ifstream file("dati.txt", ios:in);
	while (file >> x) sv.push_back(x);

	cout << "Abbiamo letto:" << endl;
	vector<string>::iterator it;
	for(it = sv.begin(); it != sv.end(); it++)
		cout << *it << endl;
}
````
`sv.begin()` e `sv.end()` sono degli oggetti della **classe iteratore** su vector

Ad ogni classe contenitore **C** della STL sono associati 2 tipi di iteratore.
`C::iterator`
`C::const_iterator`
Si usa `iterator` quando si necessita un accesso agli elementi del contenitore come lvalue (in lettura e scrittura), se basta un accesso come rvalue (in sola lettura) si preferisce la protezione di `const_iterator`

Si tratta di cosidetti **_iteratori bidirezionali_**
````
vector<int>::iterator
vector<int>::const_iterator
````
````C++
template <class T>
T& vector<T>::iterator::operator*() const;

template <class T>
vector<T>::iterator vector<T>::begin();
template <class T>
vector<T>::iterator vector<T>::end();
------------------------------------------------------
template <class T>
const T& vector<T>::const_iterator::operator*() const;

template <class T>
vector<T>::const_iterator vector<T>::begin() const;
template <class T>
vector<T>::const_iterator vector<T>::end() const;
------------------------------------------------------
vector<int> v(1); const vector<int> w(2);
iterator it = w.begin(); //ILLEGALE
*(w.begin())=0; //ILLEGALE
````

Su ogni tipo iteratore (anche *const*) di qualche istanza di contenitore `Cont<Tipo>::[const_]iterator` sono **sempre disponibili** le seguenti funzionalità:
````C++
Cont<Tipo> x;
Cont<Tipo>::[const_]iterator i;

x.begin(); // iteratore che punta al primo elemento
x.end();   //particolare iteratore che non punta ad alcun elemento è un puntatore all'ultimo elemento +1
*i; //elemento puntato da i
i++;++i; //puntatore all'elemento successivo. Se i punta all'ultimo elemento di x allora ++i == x.end()
i--;--i; //puntatore all'elemento precedente. Se i punta al primo elemento di x allora i-- è indefinito (x.begin()-1) (v.end())-- punta all'ultimo elemento
````

Gli iteratori per i contenitori `vector` e `deque` (**contenitori ad accesso casuale**) permettono di avanzare e di retrocedere di un numero arbitrario di elementi in tempo costante. Sono inoltre disponibili gli operatori di confronto per questi iteratori. Si tratta degli *iteratori ad accesso casuale*
````
vector<Tipo> v; //oppure deque<Tipo>
vector<Tipo>::iterator i, j;
int k;

i += k;
i -= k;
j = i+k;
j = i-k;
i < j;
i <= j;
i > j;
i >= j;
````

Tipicamente gli iteratori vengono usati per scorrere gli elementi di un contenitore.
````
Cont<Tipo> x;
...
for(Cont<Tipo>::iterator i = x.begin(); i != x.end(); i++)
{...}
````
I metodi `empty()` e `size()` sono comuni a tutti i contenitori
````C++
x.empty(); //true se x è vuoto, false altrimenti
x.size(); //numero di elementi contenuti in x
````
È possibile inizializzare un `vector` con un segmento di un array o di un `vector` tramite il **template di costruttore:**
`template<class InputIterator> vector(InputIterator, InputIterator)`
````C++
int main(){
	int ia[20];
	vector<int> iv(ia,ia+6); //OK
	cout << iv.size() << endl; //size 6
	vector<int> iv2(iv.begin(), iv.end()-2); //OK
	cout << iv2.size() << endl; //size 4
}
````
Metodi di inserimento di un vector:
````C++
string s;
vector<string> vs, vsl;
vector<string>::iterator i;
...
vs.push_back(s); //aggiunge s in coda al vector
vs.insert(i,s); //aggiunge s subito prima di *i
vs.insert(i,5,s); //aggiunge 5 s subito prima di *i
i = vs.begin() + vs.size()/2;
vs.insert(i, vs1.begin(), vs1.end());
/*inserisce tutti gli elementi di vs1 nella posizione mediana di vs In generale: v.insert(it1,it2,it3) inserisce [it2,it3] in v subito prima di it1*/
````
````C++
vs.insert(i,s);
i = vs.begin() + vs.size()/2;
vs.insert(i, vs1.begin(), vs1.end());
````
**ATTENZIONE**: le operazioni di `insert()` possono risultare piuttosto *inefficienti* e ciò dipende dall'implementazione della classe `vector`

Metodo `void pop_back()` di rimozione da un `vector`:
````
iterator erase (iterator position);
iterator erase (iterator first, iterator last);
````
````C++
vector<string> v;
vector<string>::iterator i, j;
...
v.pop_back(); //toglie l'ultimo elemento
v.erase(i); //toglie l'elemento puntato da i
v.erase(i,j); //toglie tutti gli elementi compresi tra il puntatore i incluso e il puntatore j escluso, ovvero gli elementi nel segmento [*i, *j)
````
Su tutti i contenitori è definito `==`
Su tutti i *contenitori sequenziali*(vector, list, deque) sono definiti gli operatori booleani relazionali `<` e `<=`
````C++
Cont<Tipo> x,y;

x == y, x != y, x < y, x <= y, x> y, x >= y
/*operatori relazionali per l'ordine lessicografico, Occorre che sul tipo base Tipo siano definiti i 2 operatori == e <
ATTENZIONE: sui map confronta le coppie (chiave, valore)*
````
Il metodo di inserimento  `insert()`, nei suoi vari overloading, è disponibile per ogni contenitore: 
````C++
Cont<Tipo> x;
Cont<Tipo>::iterator p;
Tipo a;

x.insert(p,a); //aggiunge l'elemento a prima della posizione puntata da p

//In particolare:
x.insert(x.begin(),a); //aggiunge a all'inizio
x.insert(x.end(), a); //aggiunge a alla fine
````

Per tutti i **contenitori sequenziali** `vector`, `deque`, `list` è definita l'operazione di inserimento in coda al contenitore `push_back`:
````C++
Cont<Tipo> x; //x vector, deque, list
Tipo t;
x.push_back(a); //aggiunge t alla fine di x
````
In ogni contenitore sequenziale (*vector, deque, list*) possiamo rimuovere un qualsiasi elemento tramite il metodo `erase()`:
````C++
Cont<Tipo> x;
Cont<Tipo>::iterator p, q;

x.erase(p); //toglie l'elemento puntato da p
x.erase(p,q); //toglie tutti gli elementi nell'intervallo [p,q), cioè da p incluso fino a q escluso
````
In ogni contenitore sequenziale possiamo accedere al primo ed ultimo elemento con i metodi:
````C++
T& front();
const T& front() const;

T& back();
const T& back() const;
````
````C++
std::vector<int> v; v.push_back(8); v.push_back(3);
v.front() -= v.back();
v.back() += v.back();
std::cout << v[0] << " " << v[1];
//stampa: 5 6
````

L'[[Overloading]] dell'operatore di indicizzazione `operator[]` è disponibile **solamente** per i contenitori ad accesso casuale **`vector`** e **`deque`**
````C++
Cont<Tipo> x; //x vector o deque 
int i = 3;
Tipo e = x[i]; //elemento in posizione i-esima
````
Per portabilità, in generale per gli indici è preferibile usare il tipo interno al contenitore `Cont<Tipo>::size_type` (unsigned integral type):
````C++
Cont<Tipo> x;
Cont<Tipo>::size_type i = 5;
Tipo e = x[i]; //elemento in posizione i-esima
````

## Contenitore lista
`list<Tipo>`
È implementata come una **"doubly-linked list"**. A differenza di `vector` permette quindi di eseguire in tempo costante le operazioni di inserimento e rimozione di elementi in posizione arbitraria.

È meno efficiente di `vector` nell'accesso agli elementi: infatti l'implementazione necessariamente deve percorrere la lista dall'inizio (o della fine): infatti l'implementazione necessariamente deve percorrere la lista dell'inizio (o dalla fine): **non è disponibile `operator[]`** 
`forward_list<Tipo>` (C++11) o `slist<Tipo>` (C++03) è invece una lista implementata come una "**singly-linked list**"

````C++
vector<int> v;
for(int i=0; i<500000;++i) v.insert(v.begin(), 0);
//time: 9.31s         FRONT

vector<int> v;
for(int i=0; i<500000; ++i) v.insert(v.begin() + v.size()/2,0);
//time: 4.62s         MIDDLE

deque<int> d;
for(int i=0; i<500000; ++i) d.insert(d.begin() + d.size()/2,0):
//time: 11.61s        MIDDLE

list<int> 1;
for(int i=0; i<200000; ++i) l.insert(l.begin(),0);
//time: 0.15s         FRONT

vector<int> v;
for(int i=0; i<9000000; ++i) v.push_back(0);
//time: 0.45s

list<int> l;
for(int i=0; i<9000000; ++i) l.insert(l.begin(),0);
//time: 2.52s
````
_GoingNative 2012 **Why you should  avoid linked list**_

## Contenitore bidirezionale
`deque<Tipo>`
Si tratta del contenitore "*Double Ended Queue*", coda a 2 estremi (si legge "deck").

Il contenitore deque unisce alcuni dei vantaggi principali del vector e della list. 
1. Accesso indicizzato efficiente per lettura e scrittura come in un vector.
2. Inserimento ed eliminazione agli estremi del contenitore sono efficienti come in una list.

Il contenitore deque è tipicamente implementato mediante una struttura dati complessa che consiste di più array dinamici di dimensione fissa o di un buffer circolare. Rispetto al vector, le riallocazioni sono generalemente più efficienti.

I **Contenitori associativi** permettono di accedere ad un elemento stesso o di una parte di tale valore, cioè la cossidetta *chiave* di accesso all'elemento. In ogni contenitore associativo **le chiavi sono mantenute ordinate**, quindi il tipo delle chiavi deve supportare l'operatore relazionale d'ordinamento `operator<`.

### Contenitore insieme:
`set<Tipo>`
Modella il concetto matematico di insieme e quindi accetta solamente una occorrenza per ogni valore nell'insieme. La *chiave è costituita dal valore dell'elemento*. Quindi gli elementi contenuti nel set devono avere valori tutti distinti.
- *insieme di elementi tutti distinti*

### Contenitore multinsieme
`multiset<Tipo>`

La chiave è anche in questo caso data dal valore dell'elemento. Un multiset può contenere **occorrenze multiple dello stesso elemento**, ovvero più elementi con lo stesso valore.
*come i set ma permettono le ripetizioni*

### Contenitore mappa: 
`map<T1,T2>`
Un elemento di map è costituito da una coppia (chiave, valore), ovvero da una chiave di accesso e fa un valore associato a tale chiave. Il tipo delle chiavi `T1` deve quindi supportare l'operatore relazionale d'ordinamento `operator<` Gli elementi contenuti nel map devono avere **chiavi tutte distinte**. Tipicamente, in un map **m** si accede al valore associato ad una chiava **k** tramite l'operatore di indicizzazione: `T2 x = m[k];`

### Contenitore multimappa:
`multimap<T1,T2>`
Come in un map, il valore di un elemento di un multimap è costituito da una chiave e da un valore associato a tale chiave. La differenza è che un multimap può contenere più elementi con la stessa chiave.

Nella libreria STL sono definiti anche un gran numero di algoritmi generici efficienti per i contenitori:
````
sort()
count()
copy()
reverse()
max_element()
binary_search()...

È necessaria la direttiva di inclusione #include<algorithm>
````



