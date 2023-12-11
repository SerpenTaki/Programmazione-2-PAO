*Conversioni di Tipo*
La notazione "( )" ereditata dal C per le *conversioni esplicite* (*explicit cast*) è mantenuta per scopi di compatibilità in C++ ed è illustrata dal seguente esempio:
````C++
float x; char c; void* p;
int i = (int) x;
float y = (float) c;
nodo* q = (nodo*) p;
````
Le conversioni di tipo sono operazioni "*pericolose*", il C++ standard ha introdotto una notazione esplicita più visibile  e differenziata tra le varie tipologie del cast.
`nome_cast <Tipo> (Expr)`
- `nome_cast`indica la tipologia del cast, `const, static, reinterpred, dynamic`.
- `Tipo`denota il tipo in cui deve essere convertito il valore dell' espressione `Expr`.
##### Static cast
`static_cast <Tipo> (Expr)`
Permette di rendere esplicito l'uso di tutte le conversioni, implicite o meno, previste e/o permesse dal linguaggio o definite dal programmatore. Tutte le conversioni oggetto dello static cast si basano su un'informazione di tipo statica, cioè disponibile a compile time.
Usando lo `static_cast`tali segnalazioni di warning vengono evitate. La conversione esplicita `static_cast`permette anche il cast tra puntatori a tipi qualsiasi (sempre che non venga rimosso l'attributo `const`) e in particolare quello dal tipo puntatore generico `void* a Tipo*`.
````
T& => T
T[] => T*
T => const T
T* => const T*
float => double => long double
char => short => int => long
unsigned char => ... => unsigned long
````
````C++
//Esempio di narrowing conversion
double d = 3.14;
int x = static_cast<int>(d):
// Esempio di castless conversion
char c = 'a';
int x = static_cast<int>(c);
//Esempio di conversione void* => T*
void* p; p=&d;
double* q = static_cast<double*>(p);
//Esempio di castless conversion
int* r = static_cast<int*>(q);
````
##### Const cast
`const_cast <T*>` (*puntatore costante*)
`const_cast <T&>`(*riferimento costante*)
Permette di convertire un puntatore/riferimento ad un tipo `const T`ad un puntatore/riferimento a T (rimuovendo quindi l'attributo `const`).
````C++
const int i = 5;
int* p = const_cast<int*> (&i);

void(const C& x){
	const_cast<C&>(x).metodo_non_costante();
}

int j = 7;
const int* q = &j; //OK, cast implicito
````
##### Reinterpret Cast
`reinterpret_cast <T*> (puntatore)`
`reinterpret_cast <T&> (riferimento)
Si limita a reinterpretare a basso livello la sequenza di bit con cui è rappresentato il valore puntato da *puntatore* come se fosse un valore di tipo `T`.
*Prendo un puntatore e reinterpreto come voglio l'oggetto puntato*.
Permette ogni tipologia di conversione tra puntatori. Inoltre questa conversione vale anche per i riferimenti. È un cast pericoloso e va usato con molta cautela ed in situazioni di sicurezza. Permette situazioni *estreme* e con poco senso.
````C++
Classe C{
	int* p = reinterpret_cast<int*>(&c);
	const char* a = reinterpret_cast<const char*> (&c);
	string s(a);
	cout << s;
}
````
#### Dynamic cast
`dynamic_cast <T*> (puntatore)`
`dynamic_cast <T&> (riferimento)`
Nel caso del `dynamic_cast` il cosiddetto "*tipo dinamico*" di *puntatore* o *riferimento* non è noto a tempo di compilazione ma solo a tempo di esecuzione. Si tratta di una conversione che avviene dinamicamente a tempo di esecuzione.
