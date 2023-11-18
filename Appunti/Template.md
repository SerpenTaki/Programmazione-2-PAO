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
	- 