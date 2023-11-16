/*Gli oggetti della classe Tree rappresentano alberi binari ricorsivamente definiti
di char. Si ridefiniscano assegnazione, costruttore di copia e distruzione di Tree
come assegnazione, copia e distruzione profonda. Scrivere esplicitamente eventuali
dichiarazioni friend che dovessero essere richieste da tale definizione*/

class Nodo{
    friend class Tree;
private:
    Nodo(char c='*', Nodo* s=0, Nodo* d=0): info(c), sx(s), dx(d) {}
    char info;
    Nodo* sx;
    Nodo* dx;
};

class Tree{
private:
    Nodo* root;
    static Nodo* copia(Nodo* r) {
        if(r == nullptr) return nullptr;//caso base
        // r != nullptr
        new Nodo(r->info, copia(r->sx), copia(r->dx));
    }
    static void distruggi(Nodo* r){
        if(r != nullptr){
            distruggi(r->sx);
            distruggi(r->dx);
            delete r; //invoca il distruttore di nodo, distruttore standard mi dealloca sx, dx e info
        }
    }
public:
    Tree(): root(nullptr) {}
    Tree& operator=(const Tree& t){
        if(this != &t){ //escludere il bug x=x
            distruggi(root);
            root = copia(t.root);
        }
        return *this;
    }
    Tree(const Tree& t): root(copia(t.root)) {}
    ~Tree() {
        distruggi(root);
    }

};

int main(){
    Tree t1, t2;
    t1=t2;
    Tree t3=t2;
}