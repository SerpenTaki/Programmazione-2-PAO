#include <iostream>
//DICHIARAZIONE DELLA CLASSE
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

//Definizione Metodi
int orario::Ore() const {return sec / 3600;}
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
orario orario::operator+(const orario& o){
    orario aux;
    aux.sec = (sec + o.sec) % 86400;
    return aux;
}

orario orario::operator-(const orario& o){
    orario aux;
    aux.sec = (sec - o.sec) % 86400;
    return aux;
}
/*
bool operator==(const orario& x,const orario& y){
    return (x.sec == y.sec);
}
*/
bool orario::operator>(orario o) const {
    int sec_O = o.Ore() * 3600 + o.Minuti() * 60 + o.Secondi();    
    return (sec > sec_O) ? true : false;

}

bool orario::operator<(orario o) const {
    int sec_O = o.Ore() * 3600 + o.Minuti() * 60 + o.Secondi();    
    return (sec < sec_O); //perchè ha già come oggetto di ritorno il tipo bool
}

bool orario::operator==(orario x) const {
    int sec_X = x.Ore() * 3600 + x.Minuti() * 60 + x.Secondi();    
    return (sec_X == sec);
}

//OVERLOADING di operatori con funzioni esterne
std::ostream& operator<<(std::ostream& os,const orario& o){
    return os << o.Ore() << ':' << o.orario::Minuti() << ':' << o.orario::Secondi();
}
//file.cpps

using std::cout;
using std::endl;


int main(){
    orario LE_TRE(15,0);
    orario LE_DODICI(12,0);
    
    cout << "Adesso sono le " << LE_TRE << endl;
    cout << "Fra dodici ore saranno le " << LE_TRE + LE_DODICI << endl;

}
/*STAMPA:
Adesso sono le 15:0:0
Fra dodici ore saranno le 3:0:0
*/
