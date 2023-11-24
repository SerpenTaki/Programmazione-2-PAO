````C++
//dichiarazione classe orario
class orario{
	friend  ostream& operator<<(ostream&, const orario&);
public:
	orario(int o=0, int m=0, int s=0);
	int Ore() const;
	int Minuti() const;
	int Secondi() const;
	orario operator+(const orario&) const;
	bool operator==(const orario&) const;
	bool operator<(const orario&) const;
private:
	int sec;
};
````
[[ADT]] **dataora**, una data con orario: **31/12/99 ore 23:59** In particolare, un valore data ora **è un**  orario.
````C++
class dataora : public orario{
private:
	int giorno;
	int mese;
	int anno;
public:
	int Giorno() const;
	int Mese() const;
	int Anno() const;
};
````
**Terminologia**!!!!!!!!!
Classe base **`B`** e classe derivata **`D`**
Sottoclasse **`D`** e superclasse **`B`**
Sottotipo **`D`** e supertipo **`B`**
![[Pasted image 20231122154112.png]]

# Subtyping (subsumption)
Relazione "is-a" induce il **subtyping** che è la **caratteristica fondamentale dell'ereditarietà**

Il **sottotipo** è una forma di *polimorfismo di tipo* in cui un **sottotipo** è un tipo di dato che è correlato a un altro tipo di dato (*o supertipo*) da una qualche nozione di *sostituibilità*, il che significa che gli elementi del programma, tipicamente *subroutine* o funzioni, scritti per operare su elementi del supertipo possono operare anche su elementi del sottotipo. 
-> *Ogni oggetto della classe derivata è utilizzabile anche come oggetto della classe base*
- **Subtyping:** sottotipo **`D`** => Supertipo **`B`**
- Per oggetti: **`D`** => **`B`** *estrae il sottooggetto*
-> **Subtyping per _puntatori_ e _riferimenti_**
**`D*`** =>**`B*`**          **`D&`** => **`B&`**
Puntatori e riferimenti *polimorfi*

**Gerarchie di classi:** sottotipi *diretti* ed *indiretti*
Base<-D<-E<-F

## Casi d'uso di ereditarietà
1. **Estensione** `dataora <: orario`
2. **Specializzazione** `QButton <: QComponent`
3. **Ridefinizione** `Queue <: List`
4. **Riutilizzo di codice** (*Non è subtyping*) `Queue reuse List`

Se vogliamo definire un tipo che oltre alle proprietà di `dataora` memorizzi anche il giorno della settimana possiamo farlo con la seguente derivazione di classe:
````C++
//tipo enumerazione giorno
enum giorno {lun, mar, mer, gio, ven, sab, dom};

class dataorasett : public dataora{
public:
	giorno GiornoSettimana() const;
private:
	giorno giornosettimana;
};
````
_Tipo user-defined **enum**_
![[Pasted image 20231122171212.png]]
Data una classe **`B`**, per ogni sottotipo **`D`** (in generale indiretto) di **`B`** valgono quindi le seguenti *conversioni implicite*:
- **`D`** => **`B`** (*oggetti*)
- **`D&`** => **`B&`** (*riferimenti*)
- **`D*`** => **`B*`** (*puntatori*)

Grazie alla conversione implicita `dataora` => `orario`
possiamo scrivere: 
````C++
int F(orario o) {...}
dataora d;
int i = F(d);
````
**Il viceversa non vale!**
````C++
int G(dataora d) {...}
orario o;
int i = G(o); //ILLEGALE
````
Un `dataora` è (*in particolare*) un `orario`, mentre un `orario` non è un `dataora`!

### Polimorfismo in C++ mediante puntatori e riferimenti e non oggetti
Sia `D` una sottoclasse di `B`
````C++
D d; B b;
D* pd=&d;
B* pb=&b;
pb = pd;
````
*tipo statico* del puntatore `pb` versus *tipo dinamico* di `pb`
**Quindi:** il *tipo statico* di un puntatore `p` è il tipo `T*` di dichiarazione di `p`, mentre se in un certo istante dell'esecuzione il tipo dell'oggetto a cui effettivamente punta `p` è `U` allora quell'istante `U*` è il *tipo dinamico* di `p`.
*Mentre il tipo statico è fissato al momento della dichiarazione, il tipo dinamico in generale può variare a run-time*.

Concetti e terminologia analoghi valgono per i riferimenti:
````C++
D d; B b;
D& rd=d;
B& rb=d;

//D& è il tipo dinamico di rb
````

##### La parte privata della classe base è inaccessibile alla classe derivata
Aggiungendo alla classe `dataora` un metodo `Set2K()` che assegna all'oggetto di invocazione le ore 00:00:00 del 1 gennaio 2000 **non possiamo scrivere**
````C++
dataora::Set2K(){
	sec = 0; //NO ILLEGALE
	giorno = 1;
	mese = 1;
	anno = 2000;
}
````

![[Pasted image 20231122173344.png]]
**ATTENZIONE!!!!!!!**:
- I membri `protected` rappresentano comunque una **violazione** dell'[[Information hiding]]
````C++
class C{
private:
	int priv;
protected:
	int prot;
public:
	int publ;
};

class D: private C{
	//prot e publ divengono privati
};

class E: protected C{
	//prot e publ divengono protetti
};

class F: public D{
	//prot e publ sono qui inaccessibili
public:
	void fF(int i, int j){
		//prot=i; //ILLEGALE
		//publ=j; //ILLEGALE
	}
};

class G: public E{
	//prot e publ rimangono qui protetti
	void fG(int i, int j){
		prot=i; //OK
		publ=j; //OK
	}
};
````
### Ereditarietà privata
significa "essere implementati in termini di". Se `D` deriva praticamente da `B` significa che in `D` si è interessati ad alcune funzionalità di `B` e non si è interessati ad una *relazione concettuale di subtyping* tra `D`e`B`. L'ereditarietà privata eredita l'implementazione di `B` ma non l'interfaccia di B. *L'ereditarietà privata non gioca alcun ruolo nella fase di progettazione del software ma solo nella fase di implementazione del software.*

##### Ereditarietà privata vs relazione has-a
````C++
class Motore{
private:
	int numCilindri;
public:
	Motore(int nc): numCilindri(nc) {}
	int getCilindri() const {return numCilindri;}
	void accendi() const{
	cout << "Motore a " << getCilindri() << " cilindri accesso" << endl;}
};
````
###### Relazione has-a
````C++
class Motore{
private:
	int numCilindri;
public:
	Motore(iint nc): numCilindri(nc) {}
	int getCilindri() const {return numCilindri;}
	void accendi() const;{
	cout << "Motore a " << getCilindti() << " cilindri accesso" << endl;}
}

Class Auto{
private:
	Motore mot; //Auto has-a Motore come campo dati
public:
	Auto(int nc = 4): mot(4) {}
	void accendi() const {
		mot.accendi();
		cout << "Auto con motore a " << mot.getCilindri() << " cilindri accesa" << endl;
	}
};
````
###### Ereditarietà privata
````C++
class Motore{
private:
	int numCilindri;
public:
	Motore(int nc): numCilindri(nc) {}
	int getCilindri () const {return numCilindri;}
	void accendi() const{
	cout << "Motore a " << getCilindri() << " cilindri accesso" << endl;}
};

Class Auto: private Motore{ //Auto has-a Motore come sottooggetto
public:
	Auto(int nc = 4): Motore(nc) {}
	void accendi() const{
		Motore::accendi();
		cout << "Auto con motore a " << getCilindri() << " cilindri accessa" << endl;
	}
};
````
**_Similarità_**
1. In entrambi i casi un oggetto Motore "contenuto" in ogni oggetto Auto.
2. In entrambi i casi, per gli utenti esterni, Auto* non è convertibile a Motore*
_**Differenze**_
1) La composizione è necessaria se servono **più motori** in un auto (*a meno di usi limite di ereditarietà multipla*)
2) Ered.privata può introdurre **ereditarietà multipla** (*problematica*) **non necessaria**
3) Ered.privata **permette ad Auto** di convertire `Auto*` a `Motore*`
4) Ered.privata permette **l'accesso alla parte protetta** della base

#### Conversioni implicite e tipologia di derivazione
Le conversioni implicite indotte dalla derivazione **valgono solamente per la derivazione pubblica** che è quindi l'unica tipologia di derivazione che supporta la relazione "is-a". La derivazione protetta e la derivazione privata **non inducono** alcuna conversione implicita.
````C++
class C{
private:
	int i;
protected:
	char c;
public:
	float f;
};

class D: private C { }; //derivazione privata
class E: protected C { }; //derivazione pubblica
// nessuna conversione implicita D => C e E => C
int main(){
	C c, *pc; D d, *pd; E e, *pe;
//c=d; //ILLEGALE: "C is an inaccessible base of D"
//c=e; //ILLEGALE
//pc=&d; //ILLEGALE
//pc=&e; //ILLEGALE
//C& rc=d; //ILLEGALE
}
````
**Ereditare i metodi pubblici**
````C++
class Base{
	int x;
public:
	void f() {x=2;}
};

class Derivata: public Base{
	int y;
public:
	void g() {y=3;}
};

int main(){
	Base b; Derivata d;
	Base* p = &b; Derivata* q = &d;
	p->f(); //OK
	p=&d; //Derivata* è ora il tipo dinamico di p
	p->f(); //OK
	p->g(); //HA senso?
	q->g(); //OK
	q->f();//OK
}
````
**Conversioni Base*=>Derivata*, Base& => Derivata&**
````C++
//VI significa valore (intero) Imprevedibile
class C{
public:
	int x;
	void f() {x=4;}
};

class D: public C{
public:
	int y;
	void g() {x=5; y=6;}
};

class E: public D{
public:
	int x;
	void h() {x=7; y=8; z=9;}
};

int main(){
	C c; D d; E e;
	c.f(); D.g(); e.h();
	D* pd = static_cast<D*> (&c); //PERICOLOSO!!
	cout << pd->x << " " << pd->y << endl; //errore run-time o stampa: 4 VI
	E& re = static_cast<E&> (d); //PERICOLOSO!!
	cout << re.x << " " << re.y << " " << re.z << endl; //err. run-time o stampa: 5 6 VI
	C* pc = &d; pd = static_cast<D*> (pc); //OK
	cout << pd->x << " " << pd -> << endl; //stampa 5 6
	D& rd = e; E& rel = static_cast<E&> (rd); //OK
	cout << rel.x << " " << rel.y << " " << rel.z << endl; //stampa 7 8 9
}
````

# Ereditarietà e amicizia: le amicizie non si ereditano
Falsa [[Amicizia]]
````C++
class C{
private:
	int i;
public:
	C(): i(1) {}
	friend void print(C);
};

class D: public C{
private:
	double z;
public:
	D(): z(3.14) {}
};

void print(C x){
	cout << x.i << endl;
	D d;
//cout << d.z << endl; //illegale
//"D::z is private within this context"
}

int main(){
	C c; D d;
	print(c); //stampa 1
	print(d); // Ok, stampa 1
}
````
````C++
class C{
	friend class Z;
private:
	int i;
public:
	C(): i(1) {}
};

class D: public C {
private:
	double z;
public:
	D(): z(3.14) {}
};

class Z {
public:
	void m() {C c; D d; cout << c.i; //OK
	cout << d.z; //ILLEGALE: "D::z is private within this context"
	}
};

int main(){
	Z z;
	z.m(); //stampa: 1
}
````
````C++
class C{
private:
	int i;
public:
	C(): i(1) {}
	friend void print(C);
};
void print(C x) {cout << x.i << endl;}

class D: public C{
private:
	double z;
public:
	D(): z(3.14) {}
	friend void print(D);
};
void print(D x) {cout << x.z << endl;}

int main() {
	C c; D d;
	print(c); //stampa 1
	print(d); //stampa 3.14
}
````
#### Sul significato di inaccessibile
````C++
class C{
private:
	int i;
public:
	C(): i(1) {}
	void print() {cout << ' ' << i;}
};

class D: public C {
private:
	double z;
public:
	D(): z(3.14) {}
	void print() {
		C::print(); //l'oggetto di invocazione di C::print() è il sottooggetto di tipo C dell'oggetto di invocazioen
		//cout << ' ' << this->i; //membro i INACCESSIBILE
		cout << ' ' << z;
	}
};

int main() {
	C c; D d;
	c.print(); cout << endl; //stampa 1
	d.print(); cout << endl; //stampa 1 3.14
}
````

# Sul significato di protected
29