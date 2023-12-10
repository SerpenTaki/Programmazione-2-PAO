#include<iostream>
#include "orario_handle.h"


int main() {
    orario_handle o1(17,11,27), o2;
    std::cout << o1 << ' ' << o2 << std::endl;

    o2 = o1; //stesso puntatore punt in o2 e o1
    o1.AvanzaUnOra();
    std::cout << o1 << ' ' << o2 << std::endl;

}