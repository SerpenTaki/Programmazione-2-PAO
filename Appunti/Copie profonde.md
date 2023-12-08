### Assegnazione profonda
L'operatore di assegnazione, che è binario ed infisso, si ridefinisce come ogni altro operatore dichiarando un metodo `operator=` che implementa come vogliamo venga eseguita l'assegnazione ridefinita. 
-> Occorre decidere il tipo dei parametri e il tipo restituito nella dichiarazione di `operator=`. 
Supponiamo che l'assegnazione sia ridefinita internamente alla classe `C` come metodo. Il primo operando `x` viene assunto come oggetto di invocazione dell'assegnazione, mentre avremo un parametro formale di tipo `C` per il secondo operando `y`. Dichiareremo tale parametro per riferimento al fine di evitare che venga effettuata inutilmente una copia del secondo operando `y`ed inoltre lo dichiareremo costante. Come al solito, l'assegnazione `x=y;`restituisce l-valore di `x`. Ciò in particolare, permette l'usuale composizione di assegnazioni come `x=y=z`; Pertanto il tipo del risultato sarà un riferimento ad un oggetto della stessa classe di `x`. La dichiarazione di `operator=`sarà quindi la seguente:
`C& operator=(const C&);`

Aggiorniamo la parte pubblica di `bolletta`come segue:
````C++
class bolletta{ //in modo che = faccio la copia profonda
public:
	bolletta& operator=(const bolletta&);
	...//NB: la roba puntata che va persa va deallocata
};
````
Vogliamo che bolletta effettui copie profonde. Per ottenere ciò aggiungiamo alla parte privata di `bolletta` 2 metodi statici di utilità che quindi dichiariamo privati:
- `copia()` che restituisce una copia profonda
- `distruggi()` che distrugge, cioè dealloca una data lista.
````C++
class bolletta{
...
private:
	static nodo* copia(nodo*); //nodo da duplicare, servono al designer di bolletta l'utente non deve accorgersene
	static void distruggi(nodo*); //nodo da eliminare
	..
}
````
In bolletta.cpp aggiungiamo:
[[Telefonata e Bolletta]]


