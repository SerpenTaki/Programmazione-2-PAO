
### Dichiarazione della classe orario

````C++
//file .h
class orario{
private://elementi nascosti che l'utente non deve sapere (incapsulamento)
	int sec;


public://metodi pubblici della classe
	int ore();//selettore delle ore
	int minuti();//selettore dei minuti
	int secondi();//selettore dei secondi
};
/*
unico compo dati della classe scegliamo di rappresentare l'ora del giorno con il numero di secondi trascorsi dalla mezzanotte
*/
//secondi in un giorno 24 * 60 * 60-1 = 86399 //-1 perchè ci sono 23:59:59
````
**Definizione dei metodi**
````C++
//file .cpp
int orario::ore() {
	return sec / 3600; // / divisione intera
}

int orario::minuti() {
	return (sec/60)%60; // % resto divisione intera
}

int orario::secondi() {
	return sec % 60;
}

````

###### in alternativa

````C++
class orario{
public:
	int ore() {return sec / 3600:}
	int minuti() { return (sec/60)%60;}
	int secondi() { return sec % 60;}
private:
	int sec;
};
````
In questo caso diciamo che i metodi sono definiti **_inline_**
Non raccomandabili se non per uso scolastico (!No Progetto!).

Una funzione **_inline_** è una funzione in C e C++ chiamata con una keyword *inline* che dice al compilatore di sostituire al corpo della funzione inline facendo un espansione inline. 

Le variabili di tipo `orario` vengono dette **Oggetti** o **Istanze** della classe `orario`.

````C++
int main(){
	orario mezzanotte;
	cout << mezzanotte.Secondi() << endl; //stampa un valore indefinito
}
````
[[Costruttori]]

Riassunto classe orario
````C++
class orario{
publoc:
	orario();// C default
	orario(int, int);// C ore minuti
	orario(int, int, int);// C ore minuti secondi
	int Ore();//selettore ore
	int Minuti();//selettore dei minuti
	int Secondi();//selettori secondi
private:
	int sec; //campo dati
}
````


#### Aggiungiamo ad orario 2 metodi pubblici
````C++
class orario{
public:
	...
	orario UnOraPiuTardi();
	void AvanzaUnOra();
private;
	...
};

orario orario::UnOraPiuTardi(){
	orario aux;
	aux.sec = (sec + 3600) % 86400;
	return aux;
};

void orario::AvanzaUnOra(){
	sec = (sec + 3600) % 86400;
};

orario mezzanotte;
cout << mezzanotte.ore(); //stampa 0
orario adesso(15);
cout << adesso.ore(); //stampa 15
adesso = mezzanotte.UnOraPiuTardi();
cout << adesso.ore(); //stampa 1
cout << mezzanotte.ore(); //stampa 0 
mezzanotte.AvanzaUnOra();//questo metodo provoca side effect
cout << mezzanotte.ore(); //stampa 1
````

[[Const Saga]]

###### Metodo orario somma(orario)
[[Static#Campi dati statici (o di classe)]]
````C++
orario orario::Somma(orario o) const{
	orario aux;
	aux.sec = (sec + o.sec) % 86400;
	//Notare che con o.sec si accede ad un campo dati privato del parametro o
	return aux;
}

int main{
	...
	orario ora(22,45);
	orario DUE_ORE_E_UN_QUARTO(2,15);
	ora = ora.Somma(DUE_ORE_E_UN_QUARTO);
	...
}
````

[[Overloading]]

### Funzionalità di stampa per oggetti orario
L'operatore di output del C++ è "<<". Facciamo overloading di questo operatore.
````C++
std::ostream& orario::operator<<(std::ostream& os) const{
	return os << Ore() << ':' << Minuti() << ':' << Secondi();
}
````
Per poter invocare "a cascata" l'operatore << come al solito occorre che esso ritorni lo stream per riferimento.
````C++
orario le_tre(15,0);
orario le_quattro(16,0);
le_quattro << ((le_tre << cout) << "vengono prima delle ");
````
**spiegazione:** si tratta delle seguenti chiamate
````C++
le_quattro.operator<<(cout);
le_tre.operator<<(cout);
````

Vorremmo invece, come al solito:
`cout << le_tre << " vengono prima delle " << le_quattro;`

[[Overloading]] di << come **funzione esterna** alla classe:

````C++
ostream& operator<<(ostream& os, const orario& o){
	return os<< o.Ore() << ':' << o.Minuti() << ':' << o.Secondi();
}
````

````C++
orario le_tre(15,0), dodici(12,0);
cout << "Adesso sono le " << le_tre << endl; //stampa: Adesso sono le 15:0:0

cout << "Fra dodici ore saranno le " << le_tre + dodici << endl;
//stampa: Fra dodici ore saranno le 3:0:0
````


