/*
Definire, separando interfaccia ed implementazione, una classe Raz i cui oggetti rappresentano un numero razionale (denominatore != 0)
La classe deve includere:
1. opportuni costruttori
2. un metodo Raz inverso() con il seguente comportamento: se l'oggetto di invocazione rappresenta n/m <-> m/n
3. un operatore esplicito di conversione al tipo primitivo double;
4. L'overloading degli operatori di somma e moltiplicazione
5. overloading dell'operatore di incremento pre/postfisso che, dovrà incrementare di 1 il razionale di invocazione
6. l'overloading dell'operatore di uguaglianza
7. l'overloading dell'operatore di output su ostream
8. un metodo Raz unTerzo() che ritorna il razionale 0.33333....
*/
//file .h
#include<iostream>

class Raz{
private:
    int num, den; //invariante globale: den!=0, rappresentazioni multiple per lo stesso razionale....( 1/2 e 2/4)... (potrebbe creare problemi per il test di bool 1/2 == 2/4 false)
public:
    // conversione da int n a Raz: n viene convertito in Raz(n,1)
    Raz(int n =0, int d =1): num(n), den(d == 0 ? 1 : d) {}//operatore ternario

    Raz inverso() const{// scambio numeratore e denominatore. Se si inverte zero si ottiene un intero random!
        return Raz(den, num);//ALL'ESAME NON VALUTA I COMMENTI E SE SCRIVI MINCHIATE IL PROF PICCHIA
    }

    operator double() const{
        return (num*(1.0))/(den*(1.0)); //conversione non banale converte un numero intero in double
    }

    Raz operator+(const Raz& r) const{
        return Raz(num*r.den + den*r.num, den*r.den);
        // n1/d1 + n2/d2 = (n1*d2 + n2*d1)/d1*d2
    }
    
    Raz operator*(const Raz& r) const{
        return Raz(num*r.num, den*r.den);
    }

    Raz operator++(int){//postfisso
        Raz aux(*this);
        //*this = *this + 1; //non compila per ambiguità con tipi raz e int
        *this = this->operator+(1);
        return aux;
    }// ++ postfisso ritorna il valore prima dell'incremento, quindi va tornato per valore, per definizione fa side-effect sull'oggetto di invocazione quindi non costante da contratto

    Raz& operator++() { //prefisso
        //*this = *this + 1;
        *this = *this + Raz(1);
        return *this;
    } //++ prefisso, ritornato per riferimento quindi è *this quindi tipo di ritorno Raz&

    bool operator==(const Raz& r) const{//oggetto di invocazione in sola lettura quindi costante
        //n1/d1 == n2/d2 iff n1*d2 == n2*d1
        return num*r.den == den*r.num;
    }

    static Raz unTerzo(){
        return Raz(1,3);
    }

};

//#include<iostream>

std::ostream& operator<<(std::ostream& os, const Raz& r){
    return os << "il razionale convertito come double vale " << r.operator double()<< " ";
}

//main.cpp
// #include<iostream>

int main(){
    Raz x(2,3), y(2), z, u(1,8), v(3,2), w(8,4);

    std::cout << x+y+v*u << std::endl; //2.85417
    std::cout << u.inverso() << std::endl; //8
    std::cout << (y == w) << std::endl; //true
    std::cout << y++ << " " << ++w << std::endl; //2 3
    std::cout << (++y + Raz::unTerzo()) << std::endl; //4.333333
    std::cout << 2 + Raz(1,2) << std::endl; //2.5
}