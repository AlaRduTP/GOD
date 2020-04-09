#ifndef COORD_H
#define COORD_H

#include "iter.h"

/* -/- coord.h -/- */

#include <iostream>

using namespace std;

template<typename T>
struct Coord {
    int x {0};
    int y {0};

    template<typename U>
    int operator-(const U & rhs) const {
        int dx = this->x - rhs.x;
        int dy = this->y - rhs.y;
        return dx*dx + dy*dy;
    }

    template<typename U>
    T & operator+=(const U & rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        return *(T *)this;
    }

    template<typename U>
    T & operator-=(const U & rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *(T *)this;
    }

    template<typename U>
    T & operator=(const U & rhs) {
        this->x = rhs.x;
        this->y = rhs.y;
        return *(T *)this;
    }

    template<typename U>
    bool In(const U & other) const {
        return this->operator-(other) <= 10000;
    }

    friend istream & operator>>(istream & is, Coord<T> & coord)  {
        coord._trace[0][0] = coord._trace[1][0];
        coord._trace[0][1] = coord._trace[1][1];
        is >> coord.x >> coord.y;
        coord._trace[1][0] = coord.x;
        coord._trace[1][1] = coord.y;
        return is;
    }
protected:
    int _trace[2][2] {{-1, -1}, {-1, -1}};
};

template <typename T>
ostream & operator<<(ostream & os, const Coord<T> & coord) {
    os << '(' << coord.x << ", " << coord.y << ')';
    return os;
}

/* -/- coord.h -/- */

#endif
