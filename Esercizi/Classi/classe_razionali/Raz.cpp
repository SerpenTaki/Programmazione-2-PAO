#include "Raz.hpp"

std::ostream& operator<<(std::ostream &o, const Raz& r){
    // il raizonale convertito come double vale
    return o << r.operator double() ;
};