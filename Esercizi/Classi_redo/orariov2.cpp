#include <iostream>
//DICHIARAZIONE DELLA CLASSE
class orario{
public:
    int Ore(); //Selettore Ore
    int Minuti(); //Selettore Minuti
    int Secondi(); //Selettore Secondi

    orario(); //costruttore di default
    orario(int, int);//costruttore ore-minuti
    orario(int,int,int); //costruttore ore-minuti-secondi

private:
    int sec; //unico campo dati della classe, scegliamo di rappresentare l'orario
            //mediante il numero di secondi trascorsi dalla mezzanotte
};

//definzione dei costruttori di orario
orario::orario(){
    sec = 0;
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

//Definizione Metodi
int orario::Ore() {return sec / 3600;}
int orario::Minuti() {return (sec/60) % 60;}
int orario::Secondi() {return sec % 60;}


//file.cpp

using std::cout;
using std::endl;


int main(){
    //uso il costruttore ore-minuti-secondi
    orario adesso_preciso(14,25,47);

    //uso il costruttore ore-minuti
    orario adesso(14,25);

    //uso il costruttore di defautl
    orario mezzanotte;
    orario mezzanotte2;

    //uso il costruttore ore-minuti
    orario troppo(27,25);

    cout << adesso_preciso.Ore() << ":" << adesso_preciso.Minuti() << ":" << adesso_preciso.Secondi() << endl;
    //stampa 14:25:47
    cout << adesso.Minuti() << endl; // stampa 25
    cout << mezzanotte.Ore() << endl; // stampa 0
    cout << mezzanotte2.Secondi() << endl; // stampa 0
    cout << troppo.Ore() << ":" << troppo.Minuti() << endl; //stampa 0 : 0
}