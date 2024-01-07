#ifdef IMPIEGATO_H
#define IMPIEGATO_H

class Impegato{ // classe base astratta
public:
    Impiegato(string s): nome(s) {}
    string getNome() const {return nome;}
    virtual double stipendio() const = 0; //virtuale puro
    virtual void print() const {cout << nome;} //virtuale
private:
    string nome;
};

class Dirigente : public Impiegato{
public:
    Dirigente(string s, double d=0): Impiegato(s), fissoMensile(d) {}
    void setFissoMensile(double d) { // metodo non costante
        fissoMensile = d > 0 ? d : 0;
    }
    virtual double stipendio() const { // implementazione
        return fissoMensile;
    }
    virtual void print() const {//overriding
        cout << "Il dirigente "; Impiegato::print();
        //NB: invocazione statica di Impiegato::print()
    }
private:
    double fissoMensile; //stipendio fisso
};

class Rappresentante : public Impiegato{
public:
    Rappresentante(string s, double d=0, double s=0, int x=0): Impiegato(s), baseMensile(d), commissione(e), tot(x) {}
    void setBase(double d){ baseMensile = d > 0 ? d : 0;}
    void setCommissione(double d) {baseMensile = d > 0 ? d : 0; }
    void setVenduti(int x) { tot = x > 0 ? x : 0; }
    virtual double stipendio() const { // implementazione 
        return baseMensile + commissione*tot;
    }
    virtual void print() const { //overriding
        cout << "Il rappresentante "; Impiegato::print();
    };
private:
    double baseMensile; //stipendio base fisso
    double commissione; //commissione per pezzo venduto
    int tot; //pezzi venduti in un mese
};



#endif