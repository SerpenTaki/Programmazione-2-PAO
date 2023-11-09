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

