#include "point.hpp"
#include <iostream>

int main(){

    Point A(2.5, -3.0, 4.5);

    Point B(-3.35, 0.75, 7.0);

    std::cout << "A = " << A << std::endl;
    std::cout << "B = " << B << std::endl;

    std::cout << "norma(A) = " << A.norm() << std::endl;
    
    B.negate();
    std::cout << "negate(B) =  " << B << std::endl;


    std::cout << "A + B = " << A + B << std::endl;


}