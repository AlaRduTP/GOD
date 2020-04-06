#ifndef ITER_H
#define ITER_H

/* -/- iter.h -/- */

template <typename T>
struct Iter {
    T ** pp {nullptr};
    int len {0};
    int it {0};

    void set(T ** pi, int l) {
        pp = pi;
        len = l;
    }
    Iter & begin() {
        it = 0;
        return *this;
    }
    int end() const {
        return len;
    }

    T & operator*() {
        return *pp[it];
    }
    bool operator!=(int rhs) {
        return this->it < rhs;
    }
    Iter & operator++() {
        ++it;
        return *this;
    }
};

/* -/- iter.h -/- */

#endif
