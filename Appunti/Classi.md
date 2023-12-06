La possibilità di definire delle classi permette al programmatore di estendere il linguaggio con nuovi [[ADT]]. 

**COME SI CREA UNA CLASSE**
---
Per creare una classe si parte dalla sua forma più semplice per poi introdurre pian piano le sue caratteristiche. Una classe si specifica in 2 *fasi o parti*:
1. **Definizione dell'interfaccia di classe _o dichiarazione della classe_**
	- Creazione dei suoi attributi (*campi dati / fields*)
2. **Definizione (_o implementazione_) dei suoi metodi**
[[classe orario]] //Consiglio di vedere l'esercizio su "redo orario.cpp"

NB: **Dichiarazione e Definizione devono essere memorizzate in file diversi**.
[[Programmazione orientata agli oggetti#la keyword this]]
# Modularizzazione delle classi
La definizione di classi permette di aggiungere nuovi tipi di dato disponibili al programmatore. Naturalmente, le classi, una volta definite possono essere usate per definire *modularmente* altre classi più complesse.

### Relazione has-a

è una relazione di composizione dove un oggetto (oggetto costituito o oggetto parte costituente membro) appartiene ad un altro oggetto. Un tipo definito da utente appartiene ad un campo dati definito da utente.

##### Esercizio P1 trova l'invariante!
[[Telefonata e Bolletta]]

# Classi annidate
Facendo riferimento alla classe bolletta in esercizi>>classi_redo notiamo:

Che nella definizione della classe `bolletta` notiamo che la classe `nodo`, i cui oggetti rappresentano i nodi della lista dinamica che rappresenta una bolletta è definita internamente alla classe `bolletta`.

-> *Una classe definita internamente ad un'altra classe `C` o classe interna a `C`*. Una classe `A` annidata in `C` è quindi nello scoping della classe `C` ed è a tutti gli effetti un membro della classe `C`. In particolare la classe interna `A` può essere *pubblica* o *privata*. Se A è *pubblica* allora posso definire oggetti di `A` esternamente a `C` usando l'operatore di scoping `::`, ad esempio con la dichiarazione `C::A obj;`.
Se `A` è invece privata allora il tipo `A` è inaccessibile esternamente a `C`. Nella classe annidata `A`, in particolare nel corpo dei suoi metodi, posso usare solamente i membri statici della classe contenitrice `C`. Ad esempio:

````C++
int x; //variabile globale

class C{
public:
	int x;
	static int s;
	class A {
		void f(int i){
			int z = sizeof(x); //ILLEGALE: x si riferisce a C::x
			x = i; //ILLEGALE: x si riferisce a C::x
			s = i; //OK
			::x = i; //OK: assegno alla variabile globale x
		}
		void g(C* p, int i){
			p->x = i; //OK
		}
	};
};
````
I membri della classe `A` annidata in `C` non hanno dei privilegi speciali di accesso ai membri di `C`, così come i membri di `C` non hanno dei privilegi speciali di accesso ai membri della classe `A`. Valgono quindi le usuali regole di **(_in_)accessibilità**. 
````C++
class C {
private:
	int x;
	class B{};
	class A{
	private:
		B b; //illegale: il tipo C::B è privato
		int y;
		void f(C* p, int i){
			p->x = i; //ILLEGALE: il campo dati C::x è privato
		}
	};
	int g(A* p){
		return p->y; //ILLEGALE: il campo dati A::y è privato
	}
};
````
