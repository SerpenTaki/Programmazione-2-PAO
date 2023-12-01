#include<iostream>

#include <iostream>
//DICHIARAZIONE DELLA CLASSE
class orario{
public:
    int Ore(); //Selettore Ore
    int Minuti(); //Selettore Minuti
    int Secondi(); //Selettore Secondi

    orario(); //costruttore di default
    orario(int,int);//costruttore ore-minuti
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
    else sec = 0 * 3600 + m*60;
}

//costruttore ore minuti secondi:
//da fare::::

//Definizione Metodi
int orario::Ore() {return sec / 3600;}
int orario::Minuti() {return (sec/3600) % 60;}
int orario::Secondi() {return sec % 60;}
