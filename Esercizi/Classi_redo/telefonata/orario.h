#define ORARIO_H
#ifdef ORARIO_H
#include <iostream>
class orario{
public:
    //"SELETTORI" in realtà sono metodi
    int Ore() const; //Selettore Ore
    int Minuti() const; //Selettore Minuti
    int Secondi() const; //Selettore Secondi
    //costruttori
    orario(); //costruttore di default
    orario(int); //costruttore ore
    orario(int, int);//costruttore ore-minuti
    orario(int,int,int); //costruttore ore-minuti-secondi
    //Metodi della v3
    orario UnOraPiuTardi();// QUESTO METODO DOVREBBE ESSERE SEGNATO CON IL CONST
     // x rimane invariato restituisce un'espressione = x+1 ora
    void AvanzaUnOra(); // modifica lo stato dell'oggetto di invocazione
    //Ridefinizione degli operatori
    orario operator+(const orario&); 
    orario operator-(const orario&);
    //friend bool operator==(const orario&,const orario&);
    bool operator==(orario)const;
    bool operator<(orario) const;
    bool operator>(orario) const;

private:
    int sec; //unico campo dati della classe, scegliamo di rappresentare l'orario
            //mediante il numero di secondi trascorsi dalla mezzanotte
};
#endif