# Metodi e oggetti di invocazione costanti

````C++
class orario{
public:
	void StampaSecondi() const;
	...
};

void orario::StampaSecondi() const {
	std::cout << sec << std::endl;
};
````

Il compilatore controlla che nella definizione del metodo dichiarato `const` non compaia alcuna istruzione che possa provocare *side-effect* sull'oggetto di invocazione: _**assegnazioni ai campi dati**_ dell'oggetto di _**invocazione ed invocazioni sui metodi non costanti.**_

**Spiegazione**: in un metodo costante di una classe `C`, il puntatore `this` ha tipo `const C*`

La keyword `const` mi protegge la scrittura in una variabile!!

Anche un oggetto può essere dichiarato costante:
````C++
const orario LE_DUE(14); // è l'analogo di
const int tre = 3;
````

**ATTENZIONE**: un oggetto costante si può usare come oggetto di invocazione **soltanto** per metodi dichiarati costanti!

````C++
const orario LE_TRE(15);
LE_TRE.StampaSecondi(); //OK: stampa 54000
orario t;
t = LE_TRE.UnOraPiuTardi(); //ERRORE: Non compila!
//UnOraPiuTardi non è stato dichiarato come metodo costante
````

**ECCEZIONE(_ovvia_)**: i [[Costruttori]] sono dei metodi non dichiarati costanti che possono venire invocati su oggetti dichiarati costanti!

# The const Matra

The **const mantra** to keep in mind while writing C++ code is to ==**make everything const**==, that is, as much as possible.
[[References]]
````C++
int x = 2; 
int& a = x; //ALIAS
int& a1 = 2; //ILLEGALE
a=5;
int y=3; 
a=y; //Legale, r-valore di y assegnato a l-valore di x
````
````C++
int x = 2;
int* p = &x;
*p=5;
int y=3;
p=&y; //LEGALE
````
````C++
int x =2;
int * const p = &x;//il const dopo la stellina significa che è un puntatore costante quindi punterà sempre a quella cella di memoria
*p=5; //legale
int y=3;
p=&y; //ILLEGALE
````
e per gli alias?
````C++
int x=2;
int & const r = x; //ILLEGALE (tipo illegale)
````
e se mettiamo la stellina dopo il const?
````C++
int x = 2;
const int* p = &x;
*p=5; //Illegale
int y = 3; 
p = &y; //LEGALE
````
````C++
int x = 2;
const int *const p = &x;
*p=5; //ILLEGALE
int y=3;
p=&y; //ILLEGALE
````

vediamo come si fa con i riferimenti
````C++
int x = 2;
const int& r = x; //RIFERIMENTO A TIPO COSTANTE
r = 5; //ILLEGALE (r non assegnabile)
int y = 3;
r = y; //ILLEGALE (r non assegnabile)
````
````C++
const int& r = 4; //LEGALE
r = 5; //ILLEGALE
int y=3;
r = y; //ILLEGALE

const int & const r=2; //ILLEGALE
````
a cosa serve allora?
````C++
void fun(const int& r);
//passaggio per riferimento (A tipo) costante
//come vengono passati gli oggetti al 95%
int x = 2;
fun(x); //Legale
fun(4); //Legale

const int& fun() {return 4; /*Legale*/}
//Ritorna un riferimento (A TIPO) costante
fun()=5; //ILLEGALE
````
````C++
void fun_ref(const int& r);
//Vs
void fun_ptr(const int* p);
int x=2;
fun_ref(x);
//Vs
fun_ptr(&x);

fun_ref(4); //Legale
//vs
fun_ptr(&4); //Illegale
````

````C++
void fun1(const Big& r), //PER RIFERIMENTO COSTANTE
//VERSUS
void fun2(Big v); //PER VALORE

Big b(...);
fun1(b); //copia di riferimento a Big
// VERSUS
fun2(b); //costruttore di copia di Big
````

# What is "const correctness"?
*Una cosa buona.* **Significa usare la parola chiave `const` per evitare che gli oggetti const vengano mutati**

###### In che modo la "correttezza delle costanti" è correlata alla sicurezza dei tipi ordinaria?

Dichiarare la costanza di un parametro è solo un'altra forma di sicurezza dei tipi.
Se trovate che la sicurezza dei tipi ordinaria vi aiuti a ottenere la correttezza del sistema (*lo fa, specialmente in sistemi di grandi dimensioni*), troverete che anche la correttezza delle const è di aiuto.

# Come sono implementati i reference?
- Lo standard C++ non lo prevede, dipende quindi dal compilatore
- In pratica: (*quasi sempre*) mediante puntatori.

Secondo **Bjarne's**:
Come un puntatore, un [[References]] è un alias per un oggetto, di solito è implementato per contenere un indirizzo macchina di un oggetto e non impone un sovraccarico di prestazioni rispetto ai puntatori, ma si differenzia da un puntatore per il fatto che
- si può accedere a un riferimento esattamente con la stessa sintassi del nome di un oggetto
- un riferimento si riferisce sempre all'oggetto a cui è stato inizializzato
- non esiste un "riferimento nullo" e si può assumere che un riferimento si riferisca a un oggetto
Anche se un riferimento lo è in realtà, non dovrebbe essere usato come un puntatore ma come un alias.

**ATTENZIONE**
````C++
const int& f() {return 4;}
int main() {f();}

g++ ex.cpp
//warning:returning reference to temporary [-Wreturn-local-addr]
//	const int& f() {return 4;} 
//						   ^
clang ex.cpp
//Warning:returning reference to local temporary object [-Wreturn-stack-address]
//	const int& f() {return 4;} 
//						   ^
````

````C++
#include <iostream>
//ESERCIZIO
class C{
private:
	int x;
public:
	C(int n = 0) {x=n;}
	C F(C obj) {C r; r.x = obj.x + x; return r;}
	C G(C obj) const {C r; r.x = obj.x +x; return r;}//G è meglio di F
	//se l'oggetto di invocazione viene usato in lettura bisogna proteggerlo
	C H(C& obj) {obj.x += x; return obj;}//qui generiamo side effect perciò è corretto che manchi il const sbagliata perchè oggetto di invocazione non è protetto di const
	C I(const C& obj) {C r; r.x = obj.x +x; return r;}//obj è in sola lettura ma anche x è in sola lettrura ma manca il const
	C J(const C& obj) const {C r; r.x = obj.x +x; return r;}
};

int main(){
	C x, y(1), z(2); const C v(2);
	z=x.F(y); //OK
	//! v.F(y); //ILLEGALE: "passing const C as this discard qualifiers"
	v.G(y); //OK
	(v.G(y)).F(x);//OK
	(v.G(y)).G(x);//OK
	//! x.H(v); //ILLEGALE "no matching function for call to C::H(const C&)"
	//! x.H(z.G(y)); //ILLEGALE!! no matching function for call to C::H(C)
	x.I(z.G(y));//OK nota bene!
	x.j(z.G(y));//OK
	v.j(z.G(y));//OK
}
````
## Parametro per valore VS riferimento costante
````C++
Class C{
	int a[1000]; //5*1000 bytes
};

bool byValue(C x) {return true;}
bool byConstReference(const C& x) {return true;}

int main(){
	C obj;
	for(int i=0; i<10000000; i++) byValue(obj); //3.368 sec
	for(int i=0; i<10000000; i++) byConstReference(obj); //0.031sec 108x faster
}
````
---
Definiamo ora un metodo `OraDiPranzo()` che ritorna uno specifico oggetto della classe orario (*che rappresenta l'orario canonico del pranzo*):

````C++
//TENTATIVO: un metodo costante OraDiPranzo() che ritorna un oggetto della classe orario:

class orario{
public:
	orario OraDiPranzo() const;
	...
};

orario orario::OraDiPranzo() const {//qui l'oggetto di invocazione non serve ne in lettrura ne in scrittura per sua natura
	return orario(13,25);
};

const orario inutile;
cout << "Si pranza alle " << inutile.OraDiPranzo().Ore() << " e " << inutile.OraDiPranzo().Minuti() << " minuti\n";
````

[[Static]]

