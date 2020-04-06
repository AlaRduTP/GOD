#ifndef COORD_H
#define COORD_H

/* -/- coord.h -/- */

#include <iostream>
#include <cmath>

using namespace std;

template<typename T>
struct Coord {
    int x {0};
    int y {0};

    template <typename U>
    double operator-(const U & rhs) {
        int dx = this->x - rhs.x;
        int dy = this->y - rhs.y;
        return sqrt(dx*dx + dy*dy);
    }

    template <typename U>
    T & operator+=(const U & rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        return *(T *)this;
    }

    template <typename U>
    T & operator-=(const U & rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *(T *)this;
    }

    template <typename U>
    T & operator=(const U & rhs) {
        this->x = rhs.x;
        this->y = rhs.y;
        return *(T *)this;
    }
};

template <typename T>
istream & operator>>(istream & is, Coord<T> & coord) {
    is >> coord.x >> coord.y;
    return is;
}

template <typename T>
ostream & operator<<(ostream & os, const Coord<T> & coord) {
    os << '(' << coord.x << ", " << coord.y << ')';
    return os;
}

/* -/- coord.h -/- */

#endif
