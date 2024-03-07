**QT Designer** è un'applicazione distribuita a corredo del framework QT, dedicata alla composizione di form e finestre, usabile sia come applicazione stand-alone, sia mediante integrazione in *Qt_creator*.

In modalità designer, la finestra principale di Qt Creator visualizza l'anteprima della form e tutti gli strumenti che servono per gestirne l'aspetto e le proprietà. Il pannello verticale a sinistra consente di selezionare e trascinare [widget](https://www.html.it/pag/344188/widget-su-qt/) all'interno della form, mentre a destra si trovano, rispettivamente in alto e in basso, una vista ad albero degli elementi grafici della form, ed il pannello delle proprietà contestuale che mostra i dettagli dell'elemento correntemente selezionato.
#### Layouting
L'organizzazione degli elementi di una form è gerarchica, per cui il posizionamento di ogni widget è relativo a quello del suo contenitore. Un contenitore può essere una qualunque altra widget, o un **layout**, cioè un elemento grafico il cui unico scopo è quello di gestire la geometria dei propi elementi seguendo un orientamento verticale orizzontale o a griglia.

Per assegnare il layout ad un elemento contenitore (in questo caso la form) è sufficiente selezionarlo con un click nell'anteprima e poi cliccare su uno degli appositi pulsanti dalla barra degli strumenti del designer che raffigurano elementi disposti orizzontalmente, verticalmente o su griglie. Per rimuoverlo, è possibile selezionare uno qualsiasi degli elementi contenuti, o la widget stessa, a poi cliccare sul pulsante _Break Layout_, in penultima posizione nella barra.

Una volta fissato un layout per un elemento contenitore, è possibile aggiungere altri elementi nelle posizioni disponibili, che saranno evidenziate in rosso durante le operazioni di _drag&drop_ come mostrato ad esempio, nell'immagine successiva.

### Splitter
Sono dei particolari layout che includono un separatore mobile interattivo per variare la dimensione dei propri componenti. **_Vanno definiti su coppie di elementi_** nel contesto del loro contenitore e del suo layout globale se definito.

## Connessioni tra segnali e slot, ordine TAB
QT Designer integra un **editor grafico** per la definizione di connessioni tra i segnali e slot delle widget della form. L'editor delle connessioni è attivabile cliccando sull'apposito tasto della barra degli strumenti del designer o premendo f4.

# Finestre modali e non modali
Ogni istanza di `QWidget` può essere mostrata a schermo invocando semplicemente il metodo `show()`. In questo caso, il **window manager** del sistema operativo prende in carico la richiesta di disegno aggiungendo il bordo ed i pulsanti della finestra prima di mostrarla a schermo come finestra **non modale**-
L'uso di una finestra **non modale** preserva la reattività della finestra principale dell'applicazione, permettendo all'utente di interagire allo stesso tempo con entrambe. In altre parole, l'invocazione del metodo `show()` non è bloccante per l'*event loop* della finestra principale.
A volte, però, questo comportamento deve essere modificato per forzare l'utente ad interagire momentaneamente soltanto con una finestra secondaria per motivi specifici.
Per questa eventualità il framework QT mette a disposizione la classe **`QDialog`** che estende `QWidget` con il metodo `exec()`. Invocare `exec()` su una istanza di tipo `QDialog` o di una sua derivata consente di mostrarla come fineste **modali**.
