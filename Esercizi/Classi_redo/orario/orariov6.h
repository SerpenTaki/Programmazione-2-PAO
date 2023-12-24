#ifdef ORARIOV6_H
#define ORARIOV6_H
#include<iostream>
using std::ostream;

//dichiarazione classe orario
class orario{
    friend ostream& operator<<(ostream&, const orario&)
public:
    orario(int o = 0, int m = 0, int s = 0);
    int Ore() const;
    int Minuti() const;
    int Secondi() const;
    orario operator+(const orario&) const;
    bool operator==(const orario&) const;
    bool operator<(const orario&) const;
private:
    int sec;
};

/**
 * Relazione is A, classe dataora è anche un orario. In qualsiasi contesto in cui posso mettere un orario
 * posso mettere una dataora tutto quello che c'è in orario lo eredita, e specifica solo i nuovi campi e funzionammento
 * di cui necessito
*/

class dataora : public orario { //dataora eredita da orario (ereditarietà di tipo pubblico), ci possono essere più classi base e quini ereditarietà multipla
public:
    int Giorno() const;
    int Mese() const;
    int Anno() const;
private:
    int giorno;
    int mese;
    int anno;
};

#endif