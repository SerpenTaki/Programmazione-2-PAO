#include<iostream>
#include<string>
using std::cout;
using std::endl;
using std::string;


template <class T>
class C{
    template <class V>
    friend void fun(C<V>);
private:
    T x;
public:
    C(T y): x(y) {}
};

template <class T>
void fun(C<T> t){
    cout << t.x << " ";
    C<double> c(3.1);
    cout << c.x << endl; //ok grazie all'amicizia non associata
}

int main() {
    C <int> c(4);
    C<string> s("blob");
    fun(c); //stampa: 4 3.1, istanziazione implicita fun<int>
    fun(s); //stampa blob 3.1, istanziazione implicita fun<string>
}