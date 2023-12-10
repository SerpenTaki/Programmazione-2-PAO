#ifndef ORARIO_HANDLE_H
#define ORARIO_HANDLE_H
#include <iostream>
using std::ostream;

class orario_handle{
public:
    orario_handle(int =0, int =0, int =0);
    int Ore() const;
    int Minuti() const;
    int Secondi() const;
    void AvanzaUnOra();
private:
    class orario_rappr;
    orario_rappr* punt;
};

ostream& operator<<(ostream&, const orario_handle&);

#endif
