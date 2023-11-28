**Run-Time Type Information (RTTI)**
**`TD(ptr)`** tipo dinamico di puntatore polimorfo **`ptr`**
**`Td(ref)`** tipo dinamico di riferimento polimorfo **`ref`**

Nella programmazione informatica, RTTI si riferisce a un meccanismo del C++ che espone informazioni sul *tipo di dati* di un oggetto a *tempo di esecuzione*. Le informazioni sul tipo a tempo di esecuzione possono essere applicate a tipi di dati semplici, come numeri interi e caratteri, o a tipi generici. Si tratta di una specializzazione in C++ di un concetto più generale chiamato *introspezione del tipo*. Meccanismi simili sono noti anche in altri linguaggi di programmazione.

Nel progetto originale del C++. **Bjarne Stroustrup** non incluse l'RTTI, perché riteneva che questo meccanismo fosse spesso usato in modo improprio.

# L'operatore typeid
L'operatore `typeid` permette di determinare il tipo di una espressione qualsiasi a tempo di esecuzione.
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
## Comportamento di typeid
1. Se l'espressione operando di `typeid` è un riferimento `ref` ad una classe che **contiene almeno un metodo virtuale**, cioè una **classe polimorfa**, allora `typeid` restituisce un oggetto di `type_info` che rappresenta il tipo dinamico di `ref`
2. Se l'espressione operando di `typeid` è un puntatore **dereferenziato** `*punt`, dove `punt` è un puntatore ad un **tipo polimorfo**, allora `typeid` restituisce un oggetto di `type_info` che rappresenta il tipo `T` dove `T*` è il tipo dinamico di `punt`
**ATTENZIONE**:
1) Se la classe non contiene metodi virtuali allora `typeid` restituisce il tipo statico del riferimento o del puntatore dereferenziato
2) `typeid` su un puntatore (non dereferenziato) restituisce sempre il tipo statico del puntatore
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
