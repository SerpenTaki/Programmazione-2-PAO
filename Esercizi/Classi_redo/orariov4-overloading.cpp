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
    //Ridefinizione degli operatori
    orario operator+(orario); 
    orario operator-(orario);
    bool operator==(orario);
    bool operator<(orario);
    bool operator>(orario);

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

//Ridefinizione dell'operatore
orario orario::operator+(orario o){
    orario aux;
    aux.sec = (sec + o.sec) % 86400;
    return aux;
}

orario orario::operator-(orario o){
    orario aux;
    aux.sec = (sec - o.sec) % 86400;
    return aux;
}

bool orario::operator==(orario o){
    orario aux;
    if(aux.sec == o.sec)
        return true;
    else
        return false;
}

bool orario::operator>(orario o){
    
}

bool orario::operator<(orario o){

}

//file.cpp

using std::cout;
using std::endl;


int main(){
    orario mezzanotte;
    cout << mezzanotte.Ore() << endl;
    orario adesso(15);
    cout << adesso.Ore() << endl;
    mezzanotte.AvanzaUnOra();
    cout << mezzanotte.Ore() << endl;
    //proviamo a fare 15 + 1
    adesso = adesso + mezzanotte;
    cout << adesso.Ore() << endl;
    mezzanotte.AvanzaUnOra(); //ora mezzanotte.Ore() stamperà 2 
    //proviamo a fare 16 -2
    adesso = adesso - mezzanotte;
    cout << adesso.Ore() << endl;
    orario quattordici(14);
    cout << quattordici.Ore() << endl;

    if(adesso == true)
        cout << "Vero" << endl;
    else
        cout << "Falso" << endl;

}

/* Stampa
0
15
1
16
14
*/