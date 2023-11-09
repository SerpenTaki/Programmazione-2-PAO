````
"Hello" + "World" = "Hello World"
1 e 1/2 + 2 e 3/4 = 4 e 1/4
````

````C++
class orario{
public:
	orario operator+(const orario&) const; //operator è una keyword 
	...
};

orario orario::operator+(const orario& o) const {
	orario aux;
	aux.sec = (sec + o.sec) % 86400;
	return aux;
}

int main{
	...
	orario ora(22,45);
	orario DUE_ORE_E_UN_QUARTO(2, 15);
	ora = ora + DUE_ORE_E_UN_QUARTO;
	...
}
````

#### Overloading di un operatore OP
- **operatorOP**
- come metodo oppure come funzione esterna
- se è un metodo allora l'oggetto di invocazione è il primo argomento

Il C++ permette di sovraccaricare circa 40 operatori (unari e binari):
`+ - * / % == != < <= > >= ++ -- << >> = -> [] () & new delete`

## Regole per l'overloading degli operatori

1. Non si possono cambiare:
	- posizione (prefissa/infissa/postfissa)
	- numero di operandi
	- precedenze e associatività
2. Tra gli argomenti deve essere presente almeno un tipo definito dall'utente
3. Gli operatori `= [] e ->` si possono sovraccaricare solo come metodi (interni)
4.  **Non si possono** sovraccaricare `. :: sizeof typeid` i cast e l'operatore ternario  `? :`
5. Gli operatori `= & ,` hanno una versione standard

###### Operatore condizionale ternario
`boolanExpr ? expr1 : expr2 //expr1 se vero expr2 se falso`

````C++
//Esempi
orario oraApertura = (day == SUNDAY) ? 15 : 9;

int max(int x, int y){
	return x>y ? x:y;
}
````

###### Operatore virgola
Separa delle espressioni (i suoi argomenti) e ritorna il valore solamente dell'ultima espressione a destra, mentre  tutte le altre espressioni sono valutate per i loro effetti collaterali.
````C++
int main(){
	int a = 0, b = 1, c = 2, d = 3, e = 4;
	a = (b++, c++, d++, e++)
	cout << "a = " << a << endl; //stampa 4
	cout << "c = " << c << endl; //stampa 3
}
````

## Operatore di Assegnazione

`C& operator=(const C&)` è l'operatore più sovraccaricato al mondo, tipo di ritorno C&

````C++
int x=1, y=4, z=7;
x=y=z;

cout << x << " " << y << " " << z; //cosa stampa?

7 7 7 //valutazione right to left, da destra  a sinistra;
````

````C++
int x=1, y=4, z=7;
(x=y)=z;

cout << x << " " << y << " " << z; //cosa stampa?

7 4 7 //valutazione left to right, da sinistra a destra;

````

[[Costruttori#Costruttore di Copia]]

[[classe orario#Funzionalità di stampa per oggetti orario]]

**Confrontiamo le 2 definizioni**

````C++
ostream& orario::operator<<(ostream& os) const{
	return os << ore() << ':' << minuti() << ':' << secondi();
}

ostream& operator<<(ostream &os, const orario %o){
	return os << o.ore() << ':' << o.minuti() << ':' << o.secondi();
}
````

**Differenza:** accesso alla parte privata

alto esempio: somma.
````C++
orario orario::operator+(const orario& o) const; //operatore +
orario::orario(int o); //costruttore ad un parametro conversione indotta da int a orario

orario t(12, 20), s;
s = t + 4;

//Invece non funziona
s = 4 + t; //ERRORE: operatore non definito
````

**Spiegazione**: un metodo di una classe C deve avere come oggetto di invocazione un oggetto di tipo C, non è ammessa una conversione implicita sull'oggetto di invocazione.

Operatore + come funzione esterna
````C++
// operatore + esterno
orario operator+(const orario& t, const orario& s);
orario::orario(int o); //costruttore ad un parametro

orario t(12,20), s;
s = t + 4; //Ok conversione del secondo parametro

s = 4 + t; //Ok conversione del primo parametro
````

Naturalmente in entrambi i casi funziona

````C++
s = 4 + 5; //Ok: + tra interi e poi conversione del risultato
````

==**Attenzione**==: **non possiamo** però definire la funzione esterna come:

````C++
orario operator+(const orario& t, const orario& s){
	orario aux;
	aux.sec = (t.sec + s.sec) % 86400;
	return aux;
}
````
Implementazione di *basso livello* che usa solo l'interfaccia pubblica di orario:
````C++
orario operator+(const orario& t, const orario& s){
	int sec = t.secondi() + s.secondi();
	int min = t.minuti() + s.minuti() + sec/60;
	sec = sec % 60;
	int ore = t.ore() + s.ore() + min/60;
	min = min % 60;
	ore = ore % 24;
	return orario(ore, min, sec);
}
````

#### Overloading di << come funzione esterna alla classe:
````C++
ostream& operator<<(ostream& os, const orario& o){
	return os << o.ore() << ':' << o.minuti() << ':' << o.secondi();
}
````
````C++
orario le_tre(15,0), dodici(12,0);

cout << "Adesso sono le " << le_tre << endl;
//stampa: Adesso sono le 15:0:0
cout << "Fra dodici ore saranno le " << le_tre + dodici << endl;
//stampa: Fra dodici ore saranno le 3:0:0
````

## Overloading di operatori unari

````C++
operator++(int)// ++ postfisso
operator++() //++ prefisso

/*Dato che non esiste un modo per distinguerli si usa una variabile fittizzia, quindi si mette solo int per il postfisso e non si mette per il prefisso*/
````
