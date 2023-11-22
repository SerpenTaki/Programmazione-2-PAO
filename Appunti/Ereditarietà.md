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


