Il tipo **_string_** è un esempio di [[Classi]] definita nella **STD**.

````C
//stile C  rappresentazione a basso livello
char * st = "ecco una stringa /0";
char * st = "ecco una stringa"; //equivalente
//sempre stile C ma stringhe non modificabile 
const char * st = "ecco una stringa /0";
const char * st = "ecco una stringa";
````
````C++
//rappresentazione ad alto livello impensabile fare
#include <string>

int main(){
	char * s = "ecco una stringa\0";//stile c
	string st("ecco una stringa");//stile c++
	string st = "ecco una stringa";//stile c++
}
````

Più  precisamente `string` è una istanziazione di un *template* di classi: 
`typedef basic_string<char> string`

````C++
cout << "La lunghezza di '" << st
	<< "' è di " << st.size()
	<< " caratteri;"
	<< " l'eventuale carattere nullo terminante"
<< " non è contato";
````
`st` è un **_oggetto_** della classe `string` e `size()` è un **_metodo_*** della classe `string`.
###### Dichiarazione di stringa:
````C++
string st1; //costruttore: dichiara una stringa e la inizializza come vuota

string st2(st); //costruttore di copia: st2 è una copia di st
````

#### funzioni utili per le stringhe
Per una stringa `st`, tramite l'invocazione di funzione `st.size()` si ottiene la lunghezza di `st` come valore restituito dall'invocazione. -> ci dice quanto è lunga una stringa
````C++
#include<iostream>
#include<string>
using std::cout;
using std::endl;
using std::string;

int main(){
	string st = "io sono una stringa bella ";
	cout << "La lunghezza della stringa " << st << "è di " << st.size() << endl;
	// La lunghezza della stringa io sono una stringa bella è di 26
}
````
`st.size()` è una tipica funzione della programmazione ad oggetti. `string` è una [[Classi]], `st` è un oggetto della classe `string e size()` è un *metodo* della classe `string`.

La funzione `find()` permette di trovare elementi nella stringa.

````C++
string st, st1;
int pos;
getline(cin,st);//Legge una riga da cin e la memorizza in st
pos = st.find("rosso"); // cerca sottostringa "rosso"
if (pos== string::npos)
	//in questo caso "rosso" non è sottostringa di st
else
	//altrimenti pos è la posizione del carattere 'p' della prima occorrenza di "rosso" come sottostringa in st

//Consideriamo:
// st =="FLAG: rosso bianco verde". Quindi, pos==6

st1 = st.substr(pos,5)
//ritorna la sottostringa di st di lunghezza 5 a partire dalla posizione pos (NB pos parte da 6) quindi nell'esempio di prima st1="rosso".

st.replace(pos,5,"blu");
//sostituisce in st i 5 caratteri a partire dalla posizione pos con la stringa "blu" Quindi nell'esempio di prima st diventa == "FLAG: blu bianco verde"
````
