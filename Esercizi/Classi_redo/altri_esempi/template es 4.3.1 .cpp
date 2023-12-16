#include<iostream>
using std::cout;
using std::endl;

//dichiarazione incompleta del template di classe C
template<class T> class C;

//Dichiarazione del template di funzione f_friend
template<class T>
void f_friend(C<T>);

template<class T>
class C{
    friend void f_friend<T>(C<T>);
private:
    T t;
public:
    C(T x) : t(x) {}
};

template <class T>
void f_friend(C<T> c){
    cout << c.t << endl; //per amicizia
}

int main(){
    C<int> c1(1); C<double> c2(2.5);
    f_friend(c1); //stampa 1
    f_friend(c2); //stampa 2.5
}