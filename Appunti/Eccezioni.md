# Exception handling
La **gestione delle eccezioni** è il processo di risposta al verificarsi, durante il calcolo, di *eccezioni - condizioni anomale o eccezionali che richiedono un'elaborazione speciale -* che spesso modificano il normale flusso di *esecuzione del programma*. È fornita da costrutti specializzati del *linguaggio di programmazione* o da meccanismi hardware del *computer*.

In generale, un'eccezione viene *gestita (risolta) salvando lo stato di esecuzione corrente* in un luogo predefinito e *passando l'esecuzione a una subroutine specifica nota come gestore di eccezioni*.

La funzione in cui si verifica la situazione eccezionale *solleva (o lancia `throw`) una eccezzione*
````C++
telefonata bolletta::Estrai_Una(){
	if (Vuota()) throw Ecc_Vuota();
	telefonata aux = first->info;
	first = first->next;
	return aux;
}

class Ecc_Vuota {};
````
````C++
int main() {
	...
	try { b.Estrai_Una(); }
	catch (Ecc_Vuota e) {
		cerr << "La bolletta è vuota" << endl;
		abort(); //definita in stdlib.h terminazione abnormale di programma
	}
}
````

**Definiamo le seguenti classi di eccezioni**
````C++
class err_sint {}; //errore di sintassi

class fine_file {}; //file finito prematuramente

class err_ore {}; //ora > 23

class err_minuti {}; //minuti > 59

class err_secondi {}; //secondi > 59
````
## Flusso del controllo provocato da una throw
Quando in una funzione `F` viene sollevata una eccezione di tipo `T` tramite una istruzione `throw` inizia la ricerca della clausola `catch` in grado di catturarla
1. Se l'espressione `throw` è collocata in un blocco `try` nel corpo della stessa funzione `F`, l'esecuzione abbandona il blocco `try` e vengono esaminate in successione tutte le `catch` associate a tale blocco.
2. Se si trova un type match per una `catch` l'eccezione viene catturata e viene eseguito il codice della `catch`; eventualmente, al termine dell'esecuzione del corpo della `catch` il controllo dell'esecuzione passa al punto di programma che segue l'ultimo blocco `catch`.
3. Se non si trova un type match per una `catch` oppure se l'istruzione `throw` non era collocata all'interno di un blocco `try` della stessa `F` la ricerca continua nella funzione che ha invocato la funzione `F`.
4. Questa *ricerca top-down sullo stack* delle chiamate di funzioni continua fino a che si trova una `catch` che cattura l'eccezione o si arriva alla funzione `main` nel qual caso viene richiamata la funzione di libreria `terminate()` che per default chiama la funzione `abort()` che fa terminare il programma in errore
### Rilanciare un'eccezione
è possibile che una clausola `catch` si accorga di non poter gestire direttamente una eccezione. In tal caso essa può *rilanciare* l'eccezione alla funzione chiamante con una `throw`
````C++
orario somma() try {
	orario t1, t2;
	cin >> t1 >> t2;
	return t1 + t2;
}
catch (err_sint)
	{cerr << "Errore di sintassi"; return orario();}
catch (fine_file)
	{cerr << "Errore fine file"; throw;}
catch (err_ore)
	{cerr << "Errore nelle ore"; return orario();}
catch (err_minuti)
	{cerr << "Errore nei minuti"; return orario();}
catch (err_secondi)
	{cerr << "Errore nei secondi"; return orario();}
````
**Abbiamo un problema**:
````C++
class A{
public: ~A() {cout << "~A ";}
};

void F() {A* p = new A[3]; throw 1; delete[] p;};

int main() {
	try { F(); }
	catch (int) {cout << "Eccezione int";}
	cout << "Fine ";
}
// STAMPA: Eccezione int Fine
//ovviamente non stampa: ~A ~A ~A
````
#### Utilizzo di risorse
````C++
gestore() {
	risorsa rs; //alloco la risorsa
	rs.use();
	...
	... // codice che può sollevare eccezioni
	...
	rs.release(); //non viene eseguita in caso di eccezione
}
````
Se viene sollevata una eccezione e questa non viene catturata all'interno della funzione si esce dalla funzione senza rilasciare la risorsa. Ad esempio la risorsa è la memoria e quindi si potrebbe provocare **garbage**.

**Clausola `catch` generica**:
````C++
gestore () try {
	risorsa rs;
	... //codice che può sollevare eccezioni
	rs.release(); //non viene eseguita in caso di eccezione
}
catch (...) {
	rs.release();
	throw; //rilancio l'eccezione al chiamante
}
````
### Match del tipo delle eccezioni
La catch che cattura un'eccezione di tipo `E` è la prima catch incontrata durante la ricerca che abbia un *tipo `T` compatibile con `E`*.
Le regole che definiscono la compatibilità tra il tipo `T` del parametro di una catch non generica ed il tipo `E` dell'eccezione sono le seguenti:
- Il tipo `T` è uguale al tipo `E`;
- il tipo `E` è un sottotipo di `T`, ovvero:
	- `E` è un sottotipo derivato pubblicamente da `T`;
	- `T` è un tipo puntatore `B*` ed `E` è un tipo puntatore `D*` dove `D` è un sottotipo di `B`
	- `T` è un tipo riferimento `B&` ed `E` è un tipo riferimento `D&` dove `D` è un sottotipo di `B`
- `T` è il tipo `void*` ed `E` è un qualsiasi tipo puntatore
- **Non possono** essere applicate conversioni implicite.
````C++
class E {public: virtual ~E() {}};
class E1: public E {};

void modify(vector<int>& v) {
	...
	if(v.size()==0) throw new E();
	if(v.size()==1) throw new E1();
	...
}

void G(vector<int>& v){
	try{
		modify(v);
	}
	catch(E* p) {...}
	catch(E1* q) {...}
}
````
**Comportamenti tipici** di una clausola catch sono i seguenti:
- rilanciare un'eccezione
- convertire un tipo di eccezione in un altro, rimediando parzialmente e lanciando un'eccezione diversa
- cercare di ripristinare il funzionamento, in modo che il programma possa continuare dall'istruzione che segue l'ultima `catch`
- analizzare la situazione che ha causato l'errore, eliminarne eventualmente la causa e riprovare a chiamare la funzione che ha causato originariamente l'eccezione
- esaminare l'errore ed invocare `std::terminate()`
### Specifica esplicita delle eccezioni (ALLA JAVA)
````C++
istream& operator>>(istream& is, orario& t)
	throw(err_sint, fine_file, err_ore, err_secondi, err_minuti){
	..
}
````
**DEPRECATA DA C++11**
-> Problemi:
- **Run-time checking**: il test di conformità delle eccezioni avviene a run-time e non a compile-time, quindi non vi era una garanzia statica di conformità
- **Run-time overhead**: Run-time checking richiede al compilatore del codice addizionale che potrebbe inficiare alcune ottimizzazioni
- **Inutilizzabile con i template**: in generale i parametri di tipo dei template non permettono di specificare le eccezioni.
### Qt e le eccezioni
Il modulo GUI di Qt non usa le eccezioni. Perchè?
"*When Qt was started, exceptions were not available for all the compilers* that needed to be supported by Qt. Today we are trying to keep the APIs consistent, so modules that have a history of not using exceptions will generally not get new code using exceptions added.
You will notice exceptions are used in some of the new modules of Qt"
## La gerarchia exception
Il C++ standard prevede una gerarchia di classi di eccezioni predefinita.
````mermaid
flowchart TD
	A[bad_alloc] --> B[exception]
	C[Logic_error] --> B
	D[runtime_error] --> B
	E[bad_cast] --> B
	F[length_error] --> C
	G[domain error] --> F
	H[out_of_range] --> G
	I[invalid_argument] --> H
	L[range_error] --> D
	N[overflow_error] --> L
	M[underflow_error] --> N
````
`exception` è la classe base, da cui derivano `runtime_error` e `logic_error`, da cui derivano parecchie classi.

Se il `dynamic_cast` di un riferimento fallisce allora viene automaticamente lanciata un'eccezione di tipo `bad_cast`.
````C++
class X { public: virtual ~X() {} };
class B { public: virtual ~B() {} };
class D : public B {};

#include<typeinfo>
#include<iostream>
using namespace std;
int main(){
	D d;
	B& b = d; //upcast
	try {
		X& xr = dynamic_cast<X&>(b);
	} catch(bad_cast e) {
		cout << "Cast fallito!" << endl;
	}
}
````
Derivano da `exception` anche le seguenti classi di eccezioni:
- `bad_cast`, le cui eccezioni sono lanciate dal `dynamic_cast` per riferimenti
- `bad_alloc`, lanciata dalla `new` quando lo heap è esaurito (il gestore di default invoca la `terminate()`).
- `bad_typeid`, viene lanciata dall'operatore `typeid` quando ha come argomento un puntatore nullo
