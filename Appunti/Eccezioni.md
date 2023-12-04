# Exception handling
La **gestione delle eccezioni** è il processo di risposta al verificarsi, durante il calcolo, di *eccezioni - condizioni anomale o eccezionali che richiedono un'elaborazione speciale -* che spesso modificano il normale flusso di *esecuzione del programma*. È fornita da costrutti specializzati del *linguaggio di programmazione* o da meccanismi hardware del *computer*.

In generale, un'eccezione viene *gestita (risolta) salvando lo stato di esecuzione corrente* in un luogo predefinito e *passando l'esecuzione a una subroutine specifica nota come gestore di eccezioni*.

La funzione in cui si verifica la situazione eccezionale *solleva (o lancia `throw`) una eccezzione*
````C++
telefonata bolletta::Estrai_Una(){
	if (Vuota()) throw Ecc_Vuota();
	telefonata aux = first->info;
	first = first->next;
	return aux;
}

class Ecc_Vuota {};
````
````C++
int main() {
	...
	try { b.Estrai_Una(); }
	catch (Ecc_Vuota e) {
		cerr << "La bolletta è vuota" << endl;
		abort(); //definita in stdlib.h terminazione abnormale di programma
	}
}
````

**Definiamo le seguenti classi di eccezioni**
````C++
class err_sint {}; //errore di sintassi

class fine_file {}; //file finito prematuramente

class err_ore {}; //ora > 23

class err_minuti {}; //minuti > 59

class err_secondi {}; //secondi > 59
````
## Flusso del controllo provocato da una throw
Quando in una funzione `F` viene sollevata una eccezione di tipo `T` tramite una istruzione `throw` inizia la ricerca della clausola `catch` in grado di catturarla
1. Se l'espressione `throw` è collocata in un blocco `try` nel corpo della stessa funzione `F`, l'esecuzione abbandona il blocco `try` e vengono esaminate in successione tutte le `catch` associate a tale blocco.
2. Se si trova un type match per una `catch` l'eccezione viene catturata e viene eseguito il codice della `catch`; eventualmente, al termine dell'esecuzione del corpo della `catch` il controllo dell'esecuzione passa al punto di programma che segue l'ultimo blocco `catch`.
3. Se non si trova un type match per una `catch` oppure se l'istruzione `throw` non era collocata all'interno di un blocco `try` della stessa `F` la ricerca continua nella funzione che ha invocato la funzione `F`.
4. Questa *ricerca top-down sullo stack* delle chiamate di funzioni continua fino a che si trova una `catch` che cattura l'eccezione o si arriva alla funzione `main` nel qual caso viene richiamata la funzione di libreria `terminate()` che per default chiama la funzione `abort()` che fa terminare il programma in errore
### Rilanciare un'eccezione
è possibile che una clausola `catch` si accorga