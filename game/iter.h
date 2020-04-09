#ifndef ITER_H
#define ITER_H

/* -/- iter.h -/- */

#include <iterator>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class Iter {
public:
    Iter() {}
    Iter(const Iter & other) : _pp(other._pp), _len(other._len), _it(other._it), _del(false) {}
    Iter(T ** pp, int len) : _pp(pp), _len(len) {}
    Iter(T ** pp, int len, bool del) : _pp(pp), _len(len), _del(del) {}

    ~Iter() { if(_del){ delete [] _pp; } }

    typedef size_t difference_type;
    typedef T value_type;
    typedef T & reference;
    typedef T * pointer;
    typedef random_access_iterator_tag iterator_category;

    // Compare
    // Only meaningful when both iterator values iterate over the same underlying sequence
    bool operator!=(const Iter & rhs) const {
        return this->operator->() != rhs.operator->();
    }
    bool operator==(const Iter & rhs) const {
        return this->operator->() == rhs.operator->();
    }
    bool operator>=(const Iter & rhs) const {
        return this->operator->() >= rhs.operator->();
    }
    bool operator<=(const Iter & rhs) const {
        return this->operator->() <= rhs.operator->();
    }
    bool operator>(const Iter & rhs) const {
        return this->operator->() > rhs.operator->();
    }
    bool operator<(const Iter & rhs) const {
        return this->operator->() < rhs.operator->();
    }

    // Dereference
    reference operator*() const {
        return *_pp[_it];
    }
    pointer & operator->() const {
        return _pp[_it];
    }
    reference operator[](difference_type offset) const {
        return *_pp[offset];
    }

    // Difference
    difference_type operator-(const Iter & rhs) const {
        return _it - rhs._it;
    }

    // Arithmetic operation
    Iter & operator+=(difference_type rhs) {
        _it += rhs;
        if(_it < 0) {
            _it = 0;
        } else if(_it > _len) {
            _it = _len;
        }
        return *this;
    }
    Iter operator+(difference_type rhs) const {
        Iter<T> other(*this);
        other.operator+=(rhs);
        return other;
    }
    Iter & operator-=(difference_type rhs) {
        return this->operator+=(-rhs);
    }
    Iter operator-(difference_type rhs) const {
        return this->operator+(-rhs);;
    }

    // Increment & Decrement
    Iter & operator++() {
        return this->operator+=(1);
    }
    Iter & operator--() {
        return this->operator-=(1);
    }

    // Iterate
    Iter begin() const {
        Iter<T> other(*this);
        other._it = 0;
        return other;
    }
    Iter end() const {
        Iter<T> other(*this);
        other._it = _len;
        return other;
    }

    // others
    difference_type size() const {
        return _len;
    }
private:
    T ** _pp {nullptr};
    difference_type _len {0};
    difference_type _it {0};    // 0 <= _it <= _len
    bool _del {0};
};

template<typename T>
Iter<T> operator+(const typename Iter<T>::difference_type lhs, const Iter<T> & rhs) {
    return rhs.operator+(lhs);
}
template<typename T>
Iter<T> operator-(const typename Iter<T>::difference_type lhs, const Iter<T> & rhs) {
    return rhs.operator+(-lhs);
}

namespace GOD {
    template<typename T, typename F>
    void sort(Iter<T> begin, Iter<T> end, F cmp) {
        std::sort(&begin.operator->(), &end.operator->(), [&](const T * a, const T * b) {
            return cmp(*a, *b);
        });
    }
}
/* -/- iter.h -/- */

#endif
