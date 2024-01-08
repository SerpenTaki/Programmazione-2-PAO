#include<iostream>
#include<typeinfo>
using std::cout;
using std::endl;

int main(){
	int i=5;
	cout << typeid(i).name() << endl;
	cout << typeid(3.14).name() << endl;
	if (typeid(i) == typeid(int)) cout << "YES";
}