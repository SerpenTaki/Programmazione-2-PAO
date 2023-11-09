In informatica, l'information hiding è il principio di segregazioni delle decisioni progettuali di un programma che sono molto soggette a cambiamenti. Proteggo le parti del programma da modifiche. 

I campi dati sono di solito nella parte privata e non pubblica.
- **Specificatori di accesso** `public` e `private`
- **Parte pubblica** di una classe (*interfaccia pubblica*) nella `struct` è pubblica di base
- **Parte privata** di una classe (*è il default*)
- **Interfaccia pubblica** come *documentazione*
Dall'esterno della classe si può accedere solamente alla parte pubblica
````C++
orario o;
cout << o.Ore << endl; //OK Ore() è pubblica
cout << o.sec << endl; //Errore: sec è privato
````
Invece, **I metodi della classe ovviamente possono accedere alla parte privata:** non solo a quella dell'oggetto di invocazione ma anche alla parte privata **di qualsiasi altro oggetto della classe** (*ad esempio i parametri del metodo*).

[[Classe complesso]]



