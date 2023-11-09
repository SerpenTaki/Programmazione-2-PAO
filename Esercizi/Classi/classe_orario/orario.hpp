#ifndef ORARIO_H
#define ORARIO_H

#include <iostream>

class orario{
    // membri della classe

    //private:      // keyword per nascondere i membri e i metodi è di default
    int secondi;    // max sec in un giorno =  86399

    public:         // keyword rende diponibili all'esterno metodi della classe 
    int Ore() const;
    int Min() const;
    int Sec() const;

    // orario UnOraPiuTardi() ;             // Questa e' errata
    orario UnOraPiuTardi() const;           // lascia invariato lo stato dell'oggetto   (non fanno side effect) BISOGNA utilizzare const
    void AvanzaUnOra();                     // modifica lo stato dell'oggetto chiamato (fanno side effect)
                                            // se la funzione non fa side effect bisogna mettere const

    // metodi definiti inline  (espansione del metodo non chimata di funzione )

    // (this) keyword per esplicitare il campo dati dell'oggetto della medesima classe

    // int Ore() { return this->secondi / 3600; }
    // int Min() { return  (this->secondi / 60 ) % 60; }
    // int Sec() { return this->secondi % 60; }

    // cosruttori 

    // orario();                  // questo è costruttore di default assegna la memoria dei campi dati 
                                // a celle libere a caso quindi il valore è imprevedibile, ritorna void
                                // se il programmatore aggiunge anche solu un costruttore diverso da
                                // quello di default allora esso non posso costruire oggeti default tipo (orario o) 

    // orario(int);  
    // orario(int, int);           // ore-minuti
    orario(int = 0 , int = 0 , int = 0);    // ore-minuti-secondi
                                            // si possono diciarare dei valori di default int = 0 cosi che non importa quali valori passo come parametro
                                            // posso passare direttamente anche un int o due o fare orario ora = 5 e basta per costruire
                                            // a meno che io non blocchi questa procedura utilizzando la keyword explicit


    // si possono usare operatori espliciti di conversione da classe a intero per esempio 
    // per bloccare la conversione dell'operatore bisogna sostituire la parola operator con la keyworld explicit

    operator int();         // operatore di conversione di tipo da orario-int  cosi 
                            // POSSO fare int x = mezzanotte   e mi da i secondi di mezzanotte
    

    // SBAGLIATO
    // orario OrarioDIPranzo() const;

    // key word static metodo statico fornisco un servizio senza invocare gli oggetti della classe 
    // quindi al posto di usare const si usa static perche la funzione NON usa oggetti di invocazione (utile)
    static orario OrarioDIPranzo();


    // si possono incapsulare anche campi dati statici che possono essere utili per non copiarle in ogni oggetti 
    // sono elementi in sola lettura quindi bisognerebbe utilizzare la keyword const per renderli costanti
    // sono in sola lettura perche sono operazioni che ofrono un servizio e non serve che siano modificabili
    // static perche' ofrono un servizio non necessitano di oggetto di invocazione

    static const int Sec_di_un_Ora;
    static const int Sec_di_un_Giorno;

    // è possibile anche usare un campo dati statico contatore che quindi varia
    // per esempio un campo di dati contatore che incrementa di uno per ogni creazione di oggetto
    // (bisogna cambiare il costruttore)

    // OVERLOADING OPERATORI
    // è possibile utilizzare degli operatori per potere fare operazioni di somma ecc ( al posto di metodi (utilizzo poco immediato))
    // operatori che sovraccarico di significato

    // l'overloading degli operatori puo essere interno o esterno alla classe, 
    // se interno ho il vantaggio di poter utilizzare i campi privati della classe, ma sono costretto ad avere un oggetto d'invocazione del tipo della classe
    // se esterno al contrario posso invocare anche su un oggetto di tipo int (Orario s = 4 + x(ogg orario), avviene conversione implicita), ma non posso 
    // accedere hai campi privati della classe

    orario operator+(const orario&) const;

};

std::ostream& operator<<(std::ostream& , const orario& );

#endif 