#include "orario.hpp"

int main(){

    // orario mezzanotte = orario(22, 22, 11);         // la new alloca in una cella di memoria i campi dati
                                                    // la keyword delete libera 
                                                
    // per creare un oggetto bisogna usare un costruttore (funzione)
    orario mezzanotte;
    mezzanotte = 5;      // il costruttore può essere usato come conversore di tipo da int a orario 
    
    // orario mezzanotte = orario(2, 3);
    // orario mezzanotte = 19 / 3;             // invocazione di 2 costruttori di copia

    int x = mezzanotte;

    std::cout<< mezzanotte.Ore() << ":" << mezzanotte.Min() << ":" << mezzanotte.Sec() << std::endl; 

    std::cout<< "x(secondi) = "<< x << std::endl;       //l'operatore di conversione 

    // std::cout<< mezzanotte.secondi << std::endl;     // questo e' illegale perche sto cercando di accedere a un campo privato della classe orario 

    //const correttezza
    const orario LE_DUE(14);                    //non c'e problema se io uso una variabile costante o no in questo caso
    orario LE_TRE(15);                          // le variabili di tipo const sono come dice il nomi costanti quindi mon posso riassegnare il valore

    orario t; 
    t = LE_DUE.UnOraPiuTardi();                 // se non metto const nella definizione della funzione non compila perche sto cercando
                                                // di utilizzare una funzione che NON modificha il valore che quindi NON fa' side effect e per questo devo 
                                                // specificare const nella (definizione)funzione cosi che il compilatore sappia che quel metodo e' di sola lettura

    std::cout<< t.Ore() << ":" << t.Min() << ":" << t.Sec() << std::endl; 

    t = LE_TRE.UnOraPiuTardi(); 

    std::cout<< t.Ore() << ":" << t.Min() << ":" << t.Sec() << std::endl; 

    std::cout<< orario::OrarioDIPranzo().Ore() << ":" << orario::OrarioDIPranzo().Min() << ":" << orario::OrarioDIPranzo().Sec() << std::endl; 

    const orario ora(22,45);
    orario duequarto(14,15);

    // si possono sommare in due modi
    // overloading operatori

    orario somma1 = ora + duequarto;
    orario somma2 = ora.operator+(duequarto);

    std::cout<< somma1.Ore() << ":" << somma1.Min() << ":" << somma1.Sec() << std::endl; 
    std::cout<< somma2.Ore() << ":" << somma2.Min() << ":" << somma2.Sec() << std::endl; 

    std::cout << ora << std:: endl;

}

