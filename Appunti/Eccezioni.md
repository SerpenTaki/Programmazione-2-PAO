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

# Parte riscritta secondo il libro o semplicemente riassuntino tattico

### throw e catch
La funzione in cui la situazione eccezionale si verifica *lancia* (*o solleva*) una cosidetta *eccezione* tramite il costrutto *throw*. Ad esempio consideriamo il metodo `Estrai_Una`.
*nella gestione chiamante andrò a gestire l'eccezione, il try sta nella funzione chiamantem seguito dal catch*
```C++
// con smart-pointer
telefonata bolletta::Estrai_Una(){
	if (Vuota()) throw Ecc_Vuota(); //costruisco l'oggetto che lancio
	telefonata aux = first->info;
	first = first->next;
	return aux;
}
```
L'oggetto lanciato `Ecc_Vuota()` appartiene ad una classe definita allo scopo:
```C++
class Ecc_Vuota{
...
};
```
L'esecuzione di `throw` comporta la terminazione dell'esecuzione della funzione `Estrai_Una()` con il lancio dell'eccezione `Ecc_Vuota()`(*un oggetto eccezione anonimo costruito con il costruttore di default di `Ecc_Vuota`*) alla funzione chiamante (che può essere anche il `main()`).
Nella funzione chiamante, il codice contenente la chiamata o le chiamate alla funzione è racchiuso in un blocco `try`ed è seguito da una lista di procedure, le clausole `catch` dette anche *gestori di eccezioni* che catturano e gestiscono le eccezioni sollevate. La funzione `abort()` fa parte della libreria standard del C che va inclusa con `#include<cstdlib>` e provoca la terminazione "**Brutale**" del `main()`. 
```C++
try { b.Estai_Una(); }
catch (Ecc_Vuota){
	cout << "La bolletta è vuota " << endl;
	abort();
}
```
Un altro esempio di funzione che può sollevare delle eccezioni potrebbe essere l'operatore di input della classe `orario`.
```C++
istream& operator>>(istream& is, orario& o){
	//formato di input: hh:mm:ss
	char c; int ore, minuti, secondi;
	string::size_type pos;
	string cifre("0123456789");
	is >> c; //prima cifra delle ore
	pos = cifre.find(c); ore = pos;
	is >> c;
	if (c != ':'){
		//seconda cifra delle ore
		pos = cifre.find(c);
		ore = ore * 10 + pos;
		is >> c; //input di ':'
	} //ho letto le ore e c = ':'
	is >> c; //prima cifra dei minuti
	pos = cifre.find(c);
	minuti = pos;
	is >> c;
	if(c != ':'){
		//seconda cifra dei minuti
		pos = cifre.find(c);
		minuti = minuti * 10 + pos;
		is >> c; //input di ':'
	}// ho letto i minuti e c = ':'
	is >> c; //prima cifra dei secondi
	pos = cifre.find(c);
	secondi = pos;
	is >> c;
	if(is && cifre.find(c) != string::npos){
		//seconda cifra dei secondi
		pos = cifre.find(c);
		secondi = secondi * 10 + pos;
	} //ho letto i secondi
	else if (is) //carattere non cifra
		is.putback(c);
	o.sec = ore*3600 + minuti*60 + secondi;
	return is;
}
```
Con questa definizione dell'operatore di input può accadere che:
1. I valori di `ore, minuti, secondi` non siano formati da uno o da 2 caratteri cifra (caratteri '0' .... '9') oppure non siano separati dal carattere ':'
2. Lo stream termini (su `cin` con `Ctrl+D`, da file per un EOF) prima che sia stato letto `secondi`;
3. I valori di `ore, minuti` e `secondi` non rispettino i limiti (ore <=23, minuti <=59, secondi <= 59)
Definiamo allora le seguenti classi di eccezioni:
```C++
class err_sint{}; //errore di sintassi

class fine_file{}; //file finito prematuramente

class err_ore{}; //ora > 23
class err_minuti{}; //minuti > 59
class err_secondi{}; //secondi > 59
```
//guardare codice pag.244 per capire come vengono sollevate *in generale viene lanciata una throw*
```C++
if(!(is >> c)) throw fine_file();
```
Possiamo usare tale operatore di input di `orario` in una funzione che prende in input 2 oggetti di tipo `orario` e li somma:
```C++
orario somma() {
	orario o1, o2;
	try { cin >> o1; }
	catch (err_sint) { cerr << "Errore di sintassi"; return orario(); }
	catch (fine_file) { cerr << "Errore EOF"; abort(); }
	catch (err_ore) { cerr << "Errore nelle ore";  return orario(); }
	catch (err_min) { cerr << "Errore in minuti"; return orario(); }
	catch (err_sec) { cerr << "Errore in secondi"; return orario(); }
	try { cin >> o2; }
	catch (err_sint) { cerr << "Errore di sintassi"; return orario(); }
	catch (fine_file) { cerr << "Errore EOF"; abort(); }
	catch (err_ore) { cerr << "Errore nelle ore";  return orario(); }
	catch (err_min) { cerr << "Errore in minuti"; return orario(); }
	catch (err_sec) { cerr << "Errore in secondi"; return orario(); }
	return o1+o2;
}
```
Se una clausola `catch` non contiene l'istruzione `return` (o `abort()`) l'esecuzione continua dal punto di programma che immediatamente segue le clausole `catch` del blocco `try`. La soluzione vista funziona correttamente ma la gestione delle eccezioni è mescolata alle istruzioni relative al normale flusso dell'esecuzione. Una soluzione migliore consiste nel racchiudere tutto il corpo della funzione in un unico blocco `try` e mettere tutte le clausole `catch`alla fine.
```C++
orario somma(){
	try{
		orario o1, o2; cin >> o1 >> o2; return o1 + o2;
	}
	catch (err_sint) {cerr << "Errore di sintassi" << return orario();}
	catch (fine_file) {cerr << "Errore EOF"; abort();}
	catch (err_ore) {cerr << "Errore ore" << return orario();
		catch (err_min) { cerr << "Errore minuti"; return orario(); }
	catch (err_sec) { cerr << "Errore secondi"; return orario(); }
	}
}
```
### Ricerca della clausola catch
*cerca nella catch, poi passo alle funzioni chiamanti e risalgo fino al main*
Quando in una funzione `F()` viene lanciata una eccezione tramite `throw` inizia la ricerca della clausola `catch` in grado di catturarla. Se l'espressione `throw` è collocata in un blocco `try`, l'esecuzione abbandona il blocco `try` e vengono esaminate in successione tutte le clausole `catch` associate a tale blocco per vedere se ne esiste una in grado di catturare l'eccezione. Se la si trova l'eccezione viene catturata e viene eseguito il codice della `catch`. Se non la si trova oppure se l'istruzione `throw` non era collocata all'interno del blocco `try` la ricerca continua nella funzione che ha invocato la funzione `F()`.
Questo processo continua fino a che non viene individuata una clausola `catch` in grado di catturare l'eccezione, se non ne dovesse esistere una allora si arriva al metodo `main()` e in questo caso viene richiamata la funzione di libreria `terminata()` che per default chiama la funzione `abort()`che fa terminare l’esecuzione del programma con un errore.

#### Catch generica
Quando si esce da una funzione a causa di un'eccezione vengono richiamati i distruttori per le variabili locali della funzione. Questo garantisce il recupero di eventuale memoria dinamica allocata dalla funzione o la chiusura di file aperti dalla funzione. In altre parole potremmo volere che in certe azioni vengano comunque eseguite quando si esce dalla funzione.
```C++
class A {public: ~A() {cout << "~A ";}};

void F() { A* p = new A[3]; throw 1; delete p; }

int main(){
	try { F(); }
	catch (int) { cout << "int "; }
	cout << "Fine ";
}
//stampa int fine
//ovviamente non stampa ~A ~A ~A
```
Il seguente è uno schema generale di esempio
```C++
gestore() {
	risorsa rs; //alloco una risorsa
	rs.use();
	... //codice che può sollevare eccezioni 
	rs.release(); //non viene eseguita in caso di eccezione
}
```
Se viene sollevata una eccezione e questa non viene catturata all'interno della funzione si esce dalla funzione senza rilasciare la risorsa.
Possiamo gestire questo caso tramite una cosidetta `catch` *generica*.
```C++
gestore() try{
	risorsa rs;
	rs.use();
	... //codice che può generare eccezioni
	rs.realease();
}
catch(...) {//catch generica
	rs.release();
	throw; //rilancia l'eccezione al chiamante
}
```
La sintassi `catch(...)` denota una `catch` generica in grado di catturare tutte le eccezioni possibili. Quindi se si definisce un blocco `catch` generico prima di altri blocchi `catch` questi blocchi non potranno mai essere eseguiti: si tratterebbe di un errore logico di programmazione. **Una `catch` generica quindi deve sempre essere l'ultima nella lista delle `catch` che seguono un blocco `try`.**

### Rilanciare eccezioni
