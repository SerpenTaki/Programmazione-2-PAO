#include "orario.hpp"
#include <iostream>

// orario::orario() {
//     secondi = 0;
// }

// orario::orario(int s){

//     secondi = s;

// }

// orario::orario(int ore, int minuti) {
//     if ( ore < 0 || ore > 23 || minuti < 0 || minuti > 59 )
//         secondi = 0;
//     else
//         secondi =  (ore * 3600) + (minuti * 60)  ;
    
// }

orario::orario(int o , int m, int s ){
    if (o < 0 || o > 23 || m < 0 || m > 59 || s < 0 || s > 59)
        secondi = 0;
    else
        secondi = o * 3600 + m * 60 + s;    

}


int orario::Ore() const{
    return secondi / 3600;
}

int orario::Min() const{
    return (secondi / 60) % 60;
}

int orario::Sec() const{
    return secondi % 60;
}

// si usare const perche' e' una funzione che non fa side effect e non modifica i dati dell'oggetto
//prova a usare quella senza const non compilera' 


// sbagliata (const) non fa side effect quindi il const serve
// orario orario::UnOraPiuTardi() {
//     orario aux;
//     aux.secondi = (secondi + 3600) % 86400;
//     return aux;
// }       

// giusta
orario orario::UnOraPiuTardi() const{
    orario aux;
    aux.secondi = (secondi + 3600) % 86400;
    return aux;
}

// questa fa side effect
void orario::AvanzaUnOra(){
    secondi = (secondi + 3600) % 86400;
}

orario::operator int(){
    return secondi;
}

//sbagliato NON UTILIZZA L'OGGETTO DI INVOCAZIONE serve il const!
orario orario::OrarioDIPranzo() {
    return orario(13,15);
}

//campi dati statici definizione (elementi in lettura)
const int orario::Sec_di_un_Ora = 3600;
const int orario::Sec_di_un_Giorno = 86400;

// GLI OVERLOAD DI OPERATORI VANNO DEFINITI FUORI DALLA CLASSE 
//è possibile utilizzare degli operatori per potere fare operaioni di somma ecc ( al posto di metodi )
// operatori che sovraccarico di significato
orario orario::operator+(const orario& o) const{
    orario aux;
    aux.secondi = (secondi + o.secondi) % 86400;
    return aux;
}

// è possibile nel c++ sovraccaricare circa 40 operatori 

// g++ -fno-elide-constructors
// lo useremo sempre per togliere le ottimizzazioni del costruttore di copia
        
    
// operatore di stampa

std::ostream& operator<<(std::ostream& os, const orario& o)  {
    return os << o.Ore() << ':' << o.Min() << ':' << o.Sec();
}



