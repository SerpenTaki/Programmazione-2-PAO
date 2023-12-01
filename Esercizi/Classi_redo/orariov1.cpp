// Versione 1.0

#include <iostream>
//DICHIARAZIONE DELLA CLASSE
class orario{
public:
    int Ore(); //Selettore Ore
    int Minuti(); //Selettore Minuti
    int Secondi(); //Selettore Secondi
private:
    int sec; //unico campo dati della classe, scegliamo di rappresentare l'orario
            //mediante il numero di secondi trascorsi dalla mezzanotte
};

//QUI IMPLEMENTIAMO I METODI DI UNA FUNZIONE
int orario::Ore() {return sec / 3600;}
int orario::Minuti() {return (sec/3600) % 60;}
int orario::Secondi() {return sec % 60;}

//file.cpp

using std::cout;
using std::endl;

int main() {
    orario mezzanotte;
    cout << mezzanotte.Secondi() << endl; //esegui il metodo secondi sull'oggetto di tipo Orario
}
