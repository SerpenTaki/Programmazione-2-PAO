**Run-Time Type Information (RTTI)**
**`TD(ptr)`** tipo dinamico di puntatore polimorfo **`ptr`**
**`Td(ref)`** tipo dinamico di riferimento polimorfo **`ref`**

Nella programmazione informatica, RTTI si riferisce a un meccanismo del C++ che espone informazioni sul *tipo di dati* di un oggetto a *tempo di esecuzione*. Le informazioni sul tipo a tempo di esecuzione possono essere applicate a tipi di dati semplici, come numeri interi e caratteri, o a tipi generici. Si tratta di una specializzazione in C++ di un concetto più generale chiamato *introspezione del tipo*. Meccanismi simili sono noti anche in altri linguaggi di programmazione.

Nel progetto originale del C++. **Bjarne Stroustrup** non incluse l'RTTI, perché riteneva che questo meccanismo fosse spesso usato in modo improprio.

Il meccanismo dell'*identificazione di tipi a run-time* (**_RTTI_**) permette di identificare il tipo dinamico di un puntatore o di un riferimento a tempo di esecuzione. I 2 principali operatori di RTTI sono `typeid` e `dynamic_cast`. L'operatore `typeid` è definito nel file header di libreria `typeinfo`che deve essere incluso.

# L'operatore typeid
L'operatore `typeid` permette di *determinare il tipo di una espressione qualsiasi a tempo di esecuzione.*
Se l'espressione è un riferimento polimorfo o un puntatore polimorfo dereferenziato allora `typeid` ritorna il tipo dinamico di quella espressione.
````C++
#include <typeinfo> //includere sempre questo header file
#include <iostream> //per usare typeid

int main(){
	int i=5;
	std::cout << typeid(i).name() << endl; //stampa: i(nt)
	std::cout << typeid(3.14).name() << endl; //stampa: d(ouble)
	if (typeid(i) == typeid(int)) std::cout << "Yes";
}
````
L'operatore `typeid` ha come argomento una espressione o un tipo qualsiasi e ritorna un oggetto della classe `type_info`. La definizione della classe `type_info` è nel file header `typeinfo` e rende disponibili i seguenti metodi comuni a tutte le implementazioni del compilatore.
````C++
class type_info{
// rappresentazione dipendente dall'implementazione
private:
	type_info();
	type_info(const type_info&);
	type_info& operator=(const type_info&);
public:
	bool operator==(const type_info&) const;
	bool operator!=(const type_info&) const;
	const char* name() const;
};
````
Non è possibile dichiarare, modificare o assegnare oggetti di tipo `type_info`dal momento che l'unico costruttore è privato così come lo sono il costruttore di copia e l'assegnazione. È possibile solo confrontare oggetti di uguaglianza e disuguaglianza ed estrarne il loro "nome" tramite il metodo `name()`. `typeid` è un operatore di RTTI caratterizzato dal seguente comportamento.
## Comportamento di typeid
1. Se l'espressione operando di `typeid` è un riferimento `ref` ad una classe che **contiene almeno un metodo virtuale**, cioè una **classe polimorfa**, allora `typeid` restituisce un oggetto di `type_info` che rappresenta il tipo dinamico di `ref`
2. Se l'espressione operando di `typeid` è un puntatore **dereferenziato** `*punt`, dove `punt` è un puntatore ad un **tipo polimorfo**, allora `typeid` restituisce un oggetto di `type_info` che rappresenta il tipo `T` dove `T*` è il tipo dinamico di `punt`

Diremo che un tipo `T`è polimorfo se `T` è un tipo classe che include tra i suoi almeno un metodo virtuale. Si noti che se `C`è una classe che contiene almeno un metodo virtuale allora `C`è una classe polimorfa. Inoltre ogni sottotipo di un tipo polimorfo è a sua volta un tipo polimorfo. Quindi ogni classe derivata da una classe polimorfa è pure polimorfa.
**ATTENZIONE**:
1) Se la [[Classi]] non contiene metodi virtuali allora `typeid` restituisce il tipo statico del riferimento o del puntatore dereferenziato
2) `typeid` su un puntatore (non dereferenziato) restituisce sempre il tipo statico del puntatore
3) `typeid` ignora sempre l'attributo di tipo `const`: ad esempio, l'espressione booleana `typeid(T)==typeid(const T)` si valuta sempre a true.
````C++
class A {public: virtual ~A() {} };
class B : public A {};
class D : public B {};

#include<typeinfo>
#include<iostream>

int main(){
	B b; D d;
	B& rb = d;
	A* pa = &b;
	if(typeid(rb) == typeid(B)) std::cout << '1';
	if(typeid(rd) == typeid(D)) std::cout << '2';
	if(typeid(*pa) == typeid(A)) std::cout << '3';
	if(typeid(*pa) == typeid(B)) std::cout << '4';
	if(typeid(*pa) == typeid(D)) std::cout << '5';
	//stampa 24
}
````

# Upcasting and Downcasting

L'operatore di conversione esplicita `dynamic_cast` permette di convertire puntatori e riferimenti ad una classe base `B` polimorfa in puntatori e riferimenti ad una classe `D` derivata da `B`. Supponiamo che `p` sia un puntatore ad una classe polimorfa `B` che punta a qualche oggetto `obj` e che `D` sia una sottoclasse di `B`. L'operatore di conversione dinamica `dynamic_cast<D*>(p)` permette di tentare la conversione di `p` al tipo target `D*`. La conversione sarà possibile o meno a seconda del tipo dinamico del puntatore `p`. Supponiamo che `TD(p) = E*`.
1. Se `E` è sottotipo di `D` allora la conversione andrà a buon fine e `dynamic_cast<D*>(p)` ritornerà un puntatore di tipo `D*` all'oggetto `obj`. Quindi in questo caso la conversione ha successo perchè il tipo dinamico `E*` di `p` è compatibile con il tipo target `D*` della conversione: ricordiamo infatti che il tipo statico di un puntatore deve sempre essere un supertipo del tipo dinamico.
2. Se invece `E`non è sottotipo di `D` allora la conversione fallirà è `dynamic_cast<D*>(p)`ritornerà il puntatore nullo 0. In questo caso si dice che il tipo dinamico del puntatore non è compatibile con il tipo target della conversione.
3. È importante ricordare che analogamente a `typeid`, la classe `B`deve essere polimorfa altrimenti la compilazione di `dynamic_cast`provocherà un errore. Il `dynamic_cast` permette quindi di effetuare esplicitamente le conversioni da classe base a classe derivata.
`B* => D* & B&=>D&`

Nell'OOP, il **downcasting** o raffinamento dei tipi è l'atto di *casting* di un riferimento di una classe base a una delle sue classi derivate. *Da base a derivata `dynamic cast`*

In molti linguaggi di *programmazione*, è possibile verificare attraverso *l'introspezione del tipo* se il tipo dell'oggetto a cui si fa riferimento è effettivamente quello a cui viene fatto il cast o un suo tipo derivato, e quindi emettere un errore in caso contrario.

In altre parole. Quando una variabile della classe base (*classe madre*) ha un valore della classe derivata (*classe figlia*), è possibile eseguire il downcasting.

````
B tipo polimorfo, D <= B//minore uguale
B* p puntatore polimorfo
Downcast B* => D* B& => D&//conversione => non >=

dynamic_cast<D*>(p) != 0
se e solo se
TD(p) <= D* //minore uguale //Tipo dinamico di p compatibile con il tipo target D*
````
Nel caso dei riferimenti, se il `dynamic_cast` di un riferimento fallisce allora viene sollevata un'eccezione di tipo `std::bad_cast` (definito nel file header `typeinfo`).
````C++
class X {public: virtual ~X() {} };
class B {public: virtual ~B() {} };
class D : public B {};

#include<typeinfo>
#include<iostream>

int main() {
	D d;
	B& b = d; //upcast
	try {
		X& xr = dynamic_cast<X&>(b);
	} catch(std::bad_cast e){
		std::cout << "Cast fallito!" << std:endl;
	}
}
````
**Downcasting**
````C++
class B {//classe base polimorfa
public:
	virtual void m();
};
class D : public B {
public:
	virtual void f(); //nuovo metodo virtuale
};
class E: public D{
	void g(); //nuovo metodo
};

B* fun() {/*può ritornare B*, D*, E*,...**/}

int main(){
	B* p = fun(); 
	if(dynamic_cast<*D>(p))/*Downcast possibile*/ (static_cast<D*/*Downacast*/>(p))->f();
	E* q = dynamic_cast<E*>(p);
	if(q) q->g();//downcast ha successo
} 
````
### Criticism
Molti sostengono di evitare il downcasting, poiché, secondo la LSP, un progetto OOP che lo richiede è difettoso. Alcuni linguaggi, come OCaml, rifiutano del tutto il downcasting.

**Safe-cast**: conversione *down casting* da classe Base a classe derivata "dall'alto al basso"
**Upcasting**: si converte "dal basso all'alto" nella gerarchia ovvero da classe base a derivata.

## Downcasting vs metodi virtuali
- Usare il downcast **solo quando necessario**
- **non fare** type checking dinamico inutile
- ove possibile *usare metodi virtuali nelle classi base* piuttosto che fare type checking dinamico
##### Pattern
````mermaid
flowchart TD
A[D1] --> B[Base]
D[D2] --> B
C[D3] --> B
````
````C++
class Base{
public:
	virtual ~Base() {}
	void do_Base_things() {}
};

class D1: public Base {
public:
	void do_D1_things() {}
};
class D2: public Base {
public:
	void do_D2_things() {}
};
class D3: public Base{
public:
	void do_D3_things() {}
};

void fun(Base& rb){
	rb.do_Base_things();
	if (D1* p1 = dynamic_cast<D1*> (&rb))
		p1->do_D1_things();
	else if (D2* p2 = dynamic_cast<D2*> (&rb))
		p2->do_D2_things();
	else if (D3* p3 = dynamic_cast<D3*> (&rb))
		p3->do_D3_things();
}
````




