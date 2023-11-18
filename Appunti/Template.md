Funzione che ritorna il minimo tra 2 variabili di un tipo che ammette il test booleano operator< 
````C++
int min(int a, int b){
	return a < b ? a : b;
}
````
````C++
float min(float a, float b){
	return a < b ? a : b;
}
````
````C++
orario min (orario a, orario b){
	return a < b ? a : b;
}
````
````C++
string min(string a, string b){
	return a < b ? a : b;
}
````

Una soluzione attraente ma subdolamente pericolosa potrebbe essere la definizione di **macro** per il preprocessore
`#define min(a,b) ((a) < (b) ? (a) : (b))`
il preprocessore sostituisce:
`min(10,20)` con `10 < 20 ? 10 : 20`
`min(3.5,2.1)` con `3.5 < 2.1 ? 3.5 : 2.1`

Non abbiamo ottenuto una "vera funzione"
`min(++i,--j)`
verrebbe espansa dal preprocessore con:
`++i < --j ? ++i : --j`
e provocherebbe una doppia applicazione di ++ o --
````C++
int i = 3, j = 6;
cout << min(++i, --j);
//stampa 5
// NON stampa 4
````

### Generic programming
La **programmazione generica** è uno stile di *programmazione informatica* in cui gli algoritmi sono scritti in termini di tipi *da specificare in seguito* che vengono poi *instanziati* quando necessario per tipi specifici forniti come *parametri*. 

# Template
I template sono una caratteristica del linguaggio di programmazione **C++** che consente alle funzioni e alle classi di operare con tipi *generici*. Ciò consente a una funzione o a una classe di lavorare su molti tipi di dati diversi senza essere riscritta per ciascuno di essi.

I template sono di grande utilità per i programmatori in C++, soprattutto se combinati con l'ereditarietà multipla e l'overloading degli operatori. La *Libreria standard del C++* fornisce molte funzioni utili all'interno di un quadro di modelli collegati.

Le principali ispirazioni per i template del C++ sono stati i moduli parametrizzati forniti da CLU e i generici forniti da Ada.
````C++
template <class T> //oppure: template <typename T>
T min(T a, T b){
	return a < b ? a : b;
}
````
Quindi:
````C++
int main(){
	int i, j,k;
	orario r,s,t;
	...
	//istanziazione implicita del template
	k= min(i,j);
	t = min(r,s);
	//oppure: istanziazione esplicita del template
	k = min<int>(i,j);
	t = min<orario>(r,s);
}
````
- I parametri di un template possono essere:
	- **Parametri di tipo**: si possono istanziare con un tipo qualsiasi
	- **Parametri valore _di qualche tipo_**: si possono istanziare con un valore costante del tipo indicato
		- Un template *non è codice compatibile*: istanziazione **implicita** o **esplicita** di template di funzione
		- **Processo di deduzione degli argomenti** di un template nella istanziazione implicita (dove il *tipo di ritorno non si considera mai*)
**ATTENZIONE:** nell'istanziazione implicita il **tipo di ritorno** dell'istanza del template non viene *mai considerato nella deduzione degli argomenti* (essendo opzionale l'uso del valore ritornato)
````C++
int main(){
	double d; int i, j;
	...
	d = min(i,j); //istanzia int min(int, int)
					//e quindi usa la conversione
					//int => double
}
````
**L'algoritmo di deduzione degli argomenti di un template** procede esaminando tutti i parametri attuali passati al template di funzione da sinistra verso destra. Se si trova uno stesso parametro **T** del template che appare più volte come parametro di tipo, l'argomento del template dedotto per **T** da ogni parametro attuale deve essere **esattamente** lo stesso.
````C++
int main(){
	int i; double d, e;
	...
	e = min(d,i);
	// NON COMPILA
	//Si deducono 2 diversi argomenti del template: double e int
}
````
L'istanziazione dei parametri di tipo **deve essere univoca**.

Nell'algoritmo di deduzione degli argomenti sono ammesse **quattro tipologie di conversioni** dal tipo dell'argomento attuale al tipo dei parametri del template:
1. Conversione da l-value in r-value, i.e. da **`T&`** a **`T`**;
2. da array a puntatore, i.e. da **`T[]`** a **`T*`**
3. fa conversione di qualificazione costante, i.e. da **`T`** a **`const T`**;
4. conversione da r-value a riferimento costante, i.e. da r-value di tipo **`T`** a **`const T&`**
````C++
template <class T> void E(T x) {...};
template <class T> void F(T* p) {...};
template <class T> void G(const T x) {....};
template <class T> void H(const T& y) {....};

int main(){
	int i = 6; int& x = i;
	int a[3] = {4,2,9};
	E(x); //1. istanzia void E(int)
	F(a); //2. istanzia void F(int*)
	G(i); //3. istanzia void G(const int)
	H(7); //4. istanzia void H(const int&)
}
````

**Istanziazione esplicita** degli argomenti dei parametri del template di funzione. Nell'istanziazione esplicita è possibile applicare *qualsiasi conversione implicita* di tipo per i parametri attuali del template di funzione
````C++
int main(){
	int i; double d, e;...
	e = min<double>(d,i);
	//compila!!
	//istanzia. double min(double, double)
	//quindi converte implicitamente i da int a double
}
````
Un parametro di una funzione può essere un *riferimento ad un array statico.* In  questo caso, la dimensione costante dell'array è parte integrante del tipo del parametro e il compilatore controlla che la dimensione dell'array parametro attuale coincida con quella specificata nel tipo del parametro.
````C++
int min(int (&a)[3]){//array di 3 int
	int m = a[0];
	for(int i = 1; i<3; i++)
		if(a[i]<m) m=a[i];
	return m;
}

int ar[4]= {5,2,4,2};
cout << min(ar); //non compila!
````
````C++
template <class T, int size>//int size Parametro valore
T min(T (&a)[size]){
	T vmin = a[0];
	for(int i = 1; i<size; i++)
		if(a[i]<vmin) vmin=a[i];
	return vmin;
}

int main(){
	int ia[20];
	orario ta[50];
	...
	cout << min(ia);
	cout << min(ta);
	//oppure
	cout << min<int,20>(ia);
	cout << min<int,50>(ta);
}
````

## Modello di compilazione del template

1) La definizione del template deve essere visibile all'utilizzatore del template?
2) Il file header del template cosa deve includere?
	- Solo la dichiarazione del template?
	- Sia la dichiarazione che la definizione?
3) Cosa si compila effettivamente?

### Compilazione per inclusione
Definizione del template in un "header file" che deve essere sempre incluso dal codice che necessita di istanziare il template. Non vi è quindi il concetto di compilazione separata di un template
**Problema 1**: No information hiding -> nessuna soluzione (*pazienza*)
**Problema 2:** Istanze multiple del template -> *Dichiarazioni esplicite di istanziazione*
###### Dichiarazione esplicita
di istanziazione del template di funzione:
````C++
template <class Tipo>
Tipo min(Tipo a, Tipo b){
	return a < b ? a : b;
}
````
al tipo `int` ha la forma: `template int min(int,int);`

Forza il compilatore a generare il codice dell'istanza del template relativa al tipo `int`

### Compilazione per separazione
Dichiarazione del template separata dalla sua definizione. Parola chiave **export** non supportata dai compilatori. Compilatori Comeau ed icc (*Intel C++ compiler*) tra i pochissimi che supportavano **export**.
Il comitato C++11 ha deciso di rimuovere **export** dallo standard . Rimane una keyword riservata.



# Template di classe

