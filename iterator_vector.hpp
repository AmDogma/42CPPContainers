#pragma once
#include "iterator_traits.hpp"

namespace ft {
    template <class T>
    class iterator_vector {
    private:
        T _point;
        typedef iterator_traits<T> _type;
    public:
        typedef typename _type::value_type value_type;
        typedef typename _type::difference_type difference_type;
        typedef typename _type::pointer pointer;
        typedef typename _type::reference reference;
        typedef random_access_iterator_tag iterator_category;
    public:
        iterator_vector() : _point(T()) {}

        explicit iterator_vector(const T &p) : _point(p) {}

        iterator_vector(const iterator_vector &it) : _point(it._point) {}
        ~iterator_vector() {}
//
//        const pointer val() const { // need be protected or can
//            return _point;
//        }
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
            iterator_vector<value_type> temp(*this); // value_type like T
            ++_point;
            return temp;
        }

        iterator_vector operator+(difference_type n) const {
            return iterator_vector<value_type>(_point + n);
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
            iterator_vector<value_type> temp(*this); // value_type like T
            --_point;
            return temp;
        }

        iterator_vector operator-(difference_type n) const {
            return iterator_vector<value_type>(_point - n);
        }

        iterator_vector operator-=(difference_type n) {
            _point -= n;
            return *this;
        }

        reference operator[](difference_type n) {
            return *(*this + n);
        }
    };
};
