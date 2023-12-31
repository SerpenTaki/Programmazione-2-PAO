#include <iostream>
//DICHIARAZIONE DELLA CLASSE
class orario{
public:
    //"SELETTORI" in realtà sono metodi
    int Ore(); //Selettore Ore
    int Minuti(); //Selettore Minuti
    int Secondi(); //Selettore Secondi
    //costruttori
    orario(); //costruttore di default
    orario(int); //costruttore ore
    orario(int, int);//costruttore ore-minuti
    orario(int,int,int); //costruttore ore-minuti-secondi
    //Metodi della v3
    orario UnOraPiuTardi();// QUESTO METODO DOVREBBE ESSERE SEGNATO CON IL CONST
     // x rimane invariato restituisce un'espressione = x+1 ora
    void AvanzaUnOra(); // modifica lo stato dell'oggetto di invocazione

private:
    int sec; //unico campo dati della classe, scegliamo di rappresentare l'orario
            //mediante il numero di secondi trascorsi dalla mezzanotte
};

//Definizione Metodi
int orario::Ore() {return sec / 3600;}
int orario::Minuti() {return (sec/60) % 60;}
int orario::Secondi() {return sec % 60;}

orario orario::UnOraPiuTardi(){
    orario aux; //variabile ausiliaria
    aux.sec = (sec + 3600) % 86400; //aggiungo un ora //posso accedere a sec
    return aux; //restituisco il valore di aux
}

void orario::AvanzaUnOra(){
    sec = (sec + 3600) % 86400; //modifica l'oggetto chiamante provocando side-effects
}

//definzione dei costruttori di orario
orario::orario(){ //costruttore di default.
    sec = 0;
}
//costruttore ore
orario::orario(int o){
    if(o < 0 || o > 23)
        sec = 0;
    else
        sec = o * 3600;
}
//costruttore ore-minuti
orario::orario(int o, int m){
    if(o < 0 || o > 23 || m < 0 || m > 59) 
        sec = 0; //oppure l'invocazione:orario();
    else sec = o * 3600 + m*60;
}

//costruttore ore minuti secondi:
orario::orario(int o, int m, int s){
    if(o < 0 || o > 23 || m < 0 || m > 59 || s < 0 || s > 59) //se si sfora sec è uguale a 0 e quindi anche gli altri campi andranno a 0
        sec = 0;
    else sec = o * 3600 + m*60 + s;
}


//file.cpp

using std::cout;
using std::endl;


int main(){
    orario mezzanotte;
    cout << mezzanotte.Ore() << endl;
    orario adesso(15);
    cout << adesso.Ore() << endl;
    adesso.AvanzaUnOra();
    cout << adesso.Ore() << endl;
    adesso = mezzanotte.UnOraPiuTardi();
    cout << adesso.Ore() << endl;
    cout << mezzanotte.Ore() << endl;
    mezzanotte.AvanzaUnOra();
    cout << mezzanotte.Ore() << endl;
}

/* Stampa
0
15
16
1
0
1
*/