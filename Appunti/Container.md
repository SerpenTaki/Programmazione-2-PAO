Un **Container** (*contenitore*) è una _classe_, una _struttura dati_ o un [[ADT]] *abstact data type*. Contiene elementi di vari tipi. In altre parole servono per organizzare oggetti in modo ordinato usando specifiche regole per l'accesso. 

**Un container dovrebbe implementare i seguenti metodi**:
- Creare un contenitore vuoto [[Costruttori]]
- Inserire elementi nel container
- Eliminare elementi dal container
- Eliminare tutti gli elementi nel container (*clear*)
- Accedere agli elmenti del contenier
- Accedere al numero di oggetti presenti nel conteiner (*count*)

I container somo implementati di solito al concetto di iteratore.

##### Esempi:
classi contenitore della libreria STL: string, list, vector, map,.....

**Esempio running**:[[Telefonata e Bolletta#Bolletta]]

## Fenomeno dell'interferenza o aliasing
2 cause:
1. Condivisione di memoria
2. Funzioni con *side effects*

*aliasing*: in computing: descrive una situazione dove un dato presente in memoria possono essere reperite tramite differenti nomi simbolici.
Inoltre capire quando c'è un fenomeno di *aliasing* non è decidibile ma indecidibile. Non esiste un natura un programma che analizzi il fenomeno di aliasing in natura.

![[Pasted image 20231031171320.png]]
[[Telefonata e Bolletta#Ridefinizione dell'assegnazione in bolletta]]

###### Copia superficiale
L'assegnazione standard esegue una *shallow copy*. Idem il costruttore di copia standard

Un metodo per copiare un oggetto è la copia superficiale. Nel processo di copia superficiale di A, B copierà tutti i valori dei campi di A. Se il valore del campo è un indirizzo di memoria, viene copiato l'indirizzo di memoria e se il valore del campo è un tipo primitivo, viene copiato il valore del tipo primitivo.

Lo svantaggio è che se si modifica l'indirizzo di memoria a cui punta uno dei campi di B, si modifica anche il campo a cui punta A.

###### Copie profonde
*per il costruttore di copia e l'assegnazione*
**_Deep copy_**.
Un'alternativa è la copia profonda. In questo caso i dati vengono effettivamente copiati. Il risultato è diverso da quello di una copia superficiale. Il vantaggio è che A e B non dipendono l'uno dall'altro **ma al costo di una copia più lenta e costosa**.

[[Costruttori#Ridefinizione costruttore di copia]]
