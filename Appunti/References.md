Una variabile di riferimento è un alias, cioè un altro nome per una variabile già esistente. Una volta inizializzato un riferimento con una variabile, è possibile utilizzare il nome della variabile o il nome del riferimento per riferirsi alla variabile.

## References vs Pointers
I riferimenti vengono spesso confusi con i puntatori, ma le tre differenze principali tra riferimenti e puntatori sono:
1. Non è possibile avere riferimenti NULL. Si deve poter supporre che un riferimento sia collegato a una porzione di memoria leggitima
2. Una volta inizializzato un riferimento a un oggetto, non può essere modificato per riferirsi a un altro oggetto. I puntatori possono essere indirizzati a un altro oggetto in qualsiasi momento.
3. Un riferimento deve essere inizializzato quando viene creato. I puntatori possono essere inizializzato in qualsiasi momento.

### Creating Reference in C++
Considerate il nome di una variabile come un'etichetta collegata alla posizione della variabile in memoria. Si può poi pensare a un riferimento come a una seconda etichetta collegata alla posizione di memoria. Pertanto, è possibile accedere al contenuto della variabile sia attraverso il nome originale della variabile sia attraverso il riferimento. 
````C++
int i = 17
//Possiamo dichiarare un riferimento nel seguente modo
int & r = i;
````

Leggere il & in queste dichiarazioni come riferimento. Pertanto, leggete la prima dichiarazione come "r è un riferimento intero inizializzato a i" e leggete la seconda dichiarazione come "s è un riferimento doppio inizializzato a d". L'esempio seguente fa uso di riferimenti a int e double
````C++
//primitive variables
int i;
double d;
//reference variables
int& r = i;
double& s = d;
i = 5;
cout << "Value of i : " << i << endl; //5 
cout << "Value of i reference : " << r << endl; // 5
d = 6.7;
cout << "Value of d : " << d << endl, //6.7
cout << "Value of d reference : " << s << endl; //6.7
````

# Passaggio di parametri per Riferimento
````C++
//function declaration: reference parameters
void swap(int& x, int& y);

int main(){
	//local variable declaration
	int a = 1; int b = 2;
	cout << "Before swap, value of a :" << a << endl; //1
	cout << "Before swap, value of b :" << b << endl; //2
	//calling a function to swap the values
	swap(a,b);
	cout << "After swap, value of a :" << a << endl; //2
	cout << "After swap, value of b :" << b << endl; //1
}

void swap(int& x, int& y){
	int temp = x;
	x=y;
	y = temp;
}
````

### Returning References
Un programma C++ può essere reso più facile da leggere e da mantenere utilizzando i riferimenti piuttosto che i puntatori. Una funzione C++ può restituire un riferimento in modo simile a come restituisce un puntatore.

**Quando una funzione restituisce un riferimento, restituisce un puntatore implicito al suo valore di ritorno.**

In questo modo, una funzione può essere utilizzata sul lato sinistro di un'istruzione di assegnazione.

````C++
int v[] = {3,2,6,8,5};

int& setValue(int i){
	return v[i]; //return a reference to i-th element
}

int main(){
	for(int i=0; i<5 ; i++)
		cout << v[i] << " "; //3 2 6 8 5
	cout << endl;
	setValue(1) = 9; setValue(3) = 7;
	for(int i = 0; i<5; i++)
		cout << v[i] << " "; // 3 9 6 9 5
}
````

Quando si restituisce un riferimento, bisogna fare attenzione che l'oggetto a cui si fa riferimento non esca dall'ambito.

Non è quindi legale (**Illegale**) restituire un riferimento a variabile locale
````C++
int& fun(int& a){
	int q;
	//! return q; //compile time error
	return a; //Safe, a is live outside this scope
}
````