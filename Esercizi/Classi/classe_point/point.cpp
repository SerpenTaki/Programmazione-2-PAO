#include "point.hpp"
#include <math.h>

Point::Point(double a, double b, double c){
    x = a; y = b; z = c;
}


double Point::getX() const{
    return x;
}
double Point::getY() const{
    return y;
}
double Point::getZ() const{
    return z;
}

void Point::negate(){
    x *= -1.0;
    y *= -1.0;
    z *= -1.0;
}

double Point::norm() const{
    return sqrt(x*x + y*y + z*z);
}

std::ostream& operator<<(std::ostream& os, const Point& p){
    return os << "(" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")";
}

Point operator+(const Point& a, const Point& b){
    return Point(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ() );
}