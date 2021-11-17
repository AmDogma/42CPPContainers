#pragma once
#include "iterator.hpp"

namespace ft {
    template <class T>
    class iterator_vector {
    private:
        typedef iterator_traits<T> iterator_type;
    public:
        typedef typename iterator_type::value_type         value_type;
        typedef typename iterator_type::difference_type    difference_type;
        typedef typename iterator_type::pointer            pointer;
        typedef typename iterator_type::reference          reference;
        typedef typename iterator_type::iterator_category  iterator_category;
    private:
        T _point;
    public:
        iterator_vector() : _point(T()) {}

        explicit iterator_vector(const T &p) : _point(p) {}

        iterator_vector(const iterator_vector &it) : _point(it._point) {}
        ~iterator_vector() {}

        template <class Type>
        operator iterator_vector<Type>() const {
            return iterator_vector<Type>(_point);
        }

        template <class Iter>
        iterator_vector&	operator=(iterator_vector<Iter> const & other) {
            _point = &(*other);
            return *this;
        }

        /* operators */
        reference operator*() const {
            return(*(_point));
        }

        pointer operator->() const {
            return &(*_point);
        }

        iterator_vector &operator++() {
            ++_point;
            return *this;
        }

        iterator_vector operator++(int) {
            iterator_vector temp(*this);
            ++_point;
            return temp;
        }

        iterator_vector operator+(difference_type n) const {
            return iterator_vector(_point + n);
        }

        iterator_vector operator+=(difference_type n) {
            _point += n;
            return *this;
        }

        iterator_vector &operator--() {
            --_point;
            return *this;
        }

        iterator_vector operator--(int) {
            iterator_vector temp(*this);
            --_point;
            return temp;
        }

        iterator_vector operator-(difference_type n) const {
            return iterator_vector(_point - n);
        }

        iterator_vector operator-=(difference_type n) {
            _point -= n;
            return *this;
        }

        reference operator[](difference_type n) {
            return *(*this + n);
        }

//        ??
        template <class Iterator>
        friend bool	operator==(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B);

        template <class Iterator1, class Iterator2>
        friend bool	operator==(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B);

        template <class Iterator1, class Iterator2>
        friend bool	operator>(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B);

        template <class Iterator1, class Iterator2>
        friend bool	operator<(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B);

        template <class Iterator>
        friend  bool	operator>(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B);
    };
    template <class Iterator>
    bool	operator==(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B) {
        return A._point == B._point;
    }

    template <class Iterator1, class Iterator2>
    bool	operator==(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return A._point == B._point;
    }
    template <class Iterator>
    bool	operator!=(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B) {
        return !(A == B);
    }

    template <class Iterator1, class Iterator2>
    bool	operator!=(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return !(A == B);
    }

    template <class Iterator1, class Iterator2>
    bool	operator<(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return A._point < B._point;
    }

    template <class Iterator>
    bool	operator<=(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B) {
        return A < B || A == B;
    }

    template <class Iterator1, class Iterator2>
    bool	operator<=(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return A < B || A == B;
    }

    template <class Iterator>
    bool	operator>(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B) {
        return A._point > B._point;
    }

    template <class Iterator1, class Iterator2>
    bool	operator>(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return A._point > B._point;
    }

    template <class Iterator>
    bool	operator>=(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B) {
        return A > B || A == B;
    }

    template <class Iterator1, class Iterator2>
    bool	operator>=(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return A > B || A == B;
    }
//const vs noConst ?
//    template <class Iterator>
//    iterator_vector<Iterator>	operator+(typename iterator_vector<Iterator>::difference_type n, const iterator_vector<Iterator>& it) {
//        return vector_iterator<Iterator>(it + n);
//    }
//
//    template <class Iterator>
//    typename iterator_vector<Iterator>::difference_type	operator-(const iterator_vector<Iterator>& first, const iterator_vector<Iterator>& second) {
//        return first._pointer - second._pointer;
//    }
};
