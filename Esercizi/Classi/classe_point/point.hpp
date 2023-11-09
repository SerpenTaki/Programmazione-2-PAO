#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point{
    private:
    double x, y, z;


    public:

    Point(double = 0.0, double = 0.0, double = 0.0 );

    double getX() const;
    double getY() const;
    double getZ() const;

    void negate();

    double norm()const;

};

std::ostream& operator<<(std::ostream&, const Point&);

Point operator+(const Point &, const Point&);

#endif