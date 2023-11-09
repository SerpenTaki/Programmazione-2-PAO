**_Telefonata_ has-a _orario_**

````C++
//file telefonata.h
#ifndef TELEFONATA_H
#define TELEFONATA_H
#include <iostream>
#include "orario.h"

class telefonata{
private:
	orario inizio, fine; //relazione has-a
	int numero; //è corretto usare il tipo stringa perchè sequenza di caratteri cifra, oppure la class numero telefono ma noi usiamo int per comodità
public:
	telefonata(orario,orario,int); //p.valore (per ora)
	telefonata();
	orario Inizio() const;
	orario Fine() const;
	int Numero() const;
	bool operator==(const telefonata&) const;
};

std::ostream& operator<<(std::ostream&, const telefonata&);
#endif
````
![[Pasted image 20231030183055.png]]

[[Costruttori#Comportamento del costruttore]]

````C++
//file telefonata.cpp
#include "telefonata.h"

telefonata::telefonata(orario i, orario f, int n){
	inizio = i;
	fine = f;
	numero = n;
}

telefonata::telefonata() {numero = 0;}
//attenzione: gli altri campi dati di tipo orario vengono inizializzati tramite costruttore di default

orario telefonata::Inizio() const {return inizio;}

orario telefonata::Fine() const {return fine;}

int telefonata::Numero() const {return numero;}
````
````C++
bool telefonata::operator==(const telefonata& t) const{
	return inizio == t.inizio && fine == t.fine && numero == t.numero;
}

ostream& operator<<(ostream& s, const telefonata& t){
	return s << "INIZIO" << t.Inizio() << "FINE" << t.Fine() << "NUMERO CHIAMATO" << t.Numero()
}
````

**Differenza tra `& e &&`:** _il `&&` si chiama **lazy valuation** perchè confronta entrambe le variabili inutilmente_, tuttavia ci sono dei casi dove bisogna usare il doppio & 

# Bolletta

````C++
#idndef BOLLETTA_H
#define BOLLETTA_H
#include "telefonata.h"
class bolletta{
public:
	bolletta();
	bool Vuota() const;
	void Aggiungi_Telefonata(const telefonata&);
	void Togli_Telefonata(const telefonata&);
	telefonata Estrai_Una();
private:
	... //linked list
};
#endif
````

````C++
#idndef BOLLETTA_H
#define BOLLETTA_H
#include "telefonata.h"
class bolletta{
public:
	bolletta();
	bool Vuota() const;
	void Aggiungi_Telefonata(const telefonata&);
	void Togli_Telefonata(const telefonata&);
	telefonata Estrai_Una();
private:
	class nodo{ //classe interna privata
	public:
		nodo();
		nodo(const telefonata&, nodo*);
		telefonata info;
		nodo* next;
	};
	nodo* first; //puntatore al primo nodo della lista
};
#endif
````

````C++
//file bolletta.cpp
#include "bolletta.h"

bolletta::nodo::nodo() : next(0) {}
	//costruttore di default per il campo dati info

bolletta::nodo::nodo(const telefonata& t, nodo* s)
						:info(t), next(s) {}
bolletta::bolletta(): first(0) {}

bool bolletta::Vuota() const {
	return first == 0;
}

void bolletta::Aggiungi_Telefonata(const telefonata& t){
	first = new nodo(t, first);
	//aggiunge in testa alla lista
}

void bolletta::Togli_Telefonata(const telefonata& t){
	nodo*p = first, *prec = nullptr;
	while (p && !(p->info == t)){
		prec = p;
		p = p->next;
	}//p==0 (not found) o p punta al nodo da rimuovere
	if (p) {//ho trovato t
		if (prec==nullptr)// p punta al primo nodo
			first = p->next;
		else //p punta ad un nodo successivo al primo
			prec->next = p->next;
			delete p; //attenzione: deallocare!
	}
}

telefonata bolletta::Estrai_Una(){
	//Pre: bolletta non vuota (!(first==0))
	nodo* p = first;
	first = first->next;
	telefonata aux = p->info; //costruttore di copia
	delete p; //attenzione: deallocare!
	return aux;
}
````

*aggiuntgi_telefonata() e togli_telefonata()* possono provocare **side effect** sull'oggetto di invocazione. 

````C++
int main(){
	bolletta b1; //costruttore senza argomenti
	telefonata t1(orario(9,23,12), orario(10,4,53), 2121212);
	telefonata t2(orario(11,15,4), orario(11,22,1), 3131313);

	b1.Aggiungi_Telefonata(t1);
	b1.Aggiungi_Telefonata(t2);
	cout << b1; // supponiamo di avere l'output di bolletta

	bolletta b2;
	b2 = b1;

	b2.Togli_Telefonata(t1);
	cout << b1 << b2;
}
````

![[Pasted image 20231031170243.png]]
![[Pasted image 20231031170252.png]]
![[Pasted image 20231031170414.png]]
Dandling pointer (*puntatore penzolante*) [[Container#Fenomeno dell'interferenza o aliasing]]

###### Ridefinizione dell'assegnazione in bolletta
````C++
class bolletta{
	..
private:
	static nodo* copia(nodo*);
	static void distruggi(nodo*);
	...
};
````

Aggiungiamo a `bolletta` 2 metodi statici di utilità

````C++
//iterativa
//creazione
bolletta::nodo* bolletta::copia(nodo* p){
	if(p==nullptr) return nullptr;
	//prima punta al primo nodo della copia della lista
	nodo* primo = new nodo(p->info,nullptr);
	// q punta all'ultimo nodo della lista finora copiata
	nodo* q = primo;
	while(p->next != nullptr){
		p = p->next;
		q->next = new nodo(p->info,nullptr);
		q = q->next;
	}
	return primo;
}
//distruzione
void bolletta::distruggi(nodo* p){
	if(p!=nullptr){
	//scorro tutta la lista deallcando ogni nodo
		nodo* q = p;
		while (p!=nullptr){
			p = p->next;
			delete q; //dealloco il nodo puntato da q
			q = p;
		}
	}
}
````

Implementazioni ricorsive
````C++
//creazione
bolletta::nodo* bolletta::copia(nodo* p){
	if (!p) return nullptr;// caso base lista vuota
	else
	//passo induttivo:
	/* per ip indutt. copia(p->next) è la copia della coda di p, e quindi
	inserisco una copia del primo nodo di p in testa alla lista copia(p->next)*/
	return new nodo(p->info, copia(p->next));
}
//distruzione
void bolletta::distruggi(nodo* p){
	//caso base: lista vuota nulla da fare
	if (p){
		/*passo induttivo: per ip.induttiva distruggi(p->next) dealloca la coda
		di p e quindi rimane da deallocare solamente il primo nodo di p */
		distruggi(p->next);
		delete p; //dealloco il nodo puntato da p
	}
}
````

**Primo tentativo di definizione di operator=**

````C++
bolletta& bolletta::operator=(const bolletta& b){
	first = copia(b.first); //operator= tra puntatori
	return *this; //ritorna l'oggetto di invocazioe
};
````

Qui si crea Garbage
1)  Memoria puntata da first prima della sua assegnazione
````C++
bolletta& bolletta::operator=(const bolletta& b){
	distruggi(first); //pulizia dello heap
	first = copia(b.first);
	return *this;*
}
````
2) possibile assegnazione `b = b;` con;
````C++
bolletta& bolletta::operator=(const bolletta& b){
	distruggi(first); //pulizia dello heap
	first = copia(b.first);
	return *this;
}
````
quindi:
````C++
bolletta& bolletta::operator=(const bolletta& b) {
	if(this != &b){ //!= tra puntatori
		distruggi(first); //pulizia dello heap
		first = copia(b.first);
	}
	return *this;
}
````


