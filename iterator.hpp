#pragma once
#include "iterator_traits.hpp"

namespace ft {

    template<class InputIterator>
    typename iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last) { // дополнить на разные версии перегрузки
        typename ft::iterator_traits<InputIterator>::difference_type dis = 0;
        for(; first != last;  first++)
            dis++;
        return dis;
    }
//
//    template <class Iterator>
//    typename iterator_traits<Iterator>::iterator_category	iterator_category(Iterator iter) {
//        return typename iterator_traits<Iterator>::iterator_category();
//    }

    template <class IteratorType>
    class reverse_iterator {
    private:
        typedef iterator_traits<IteratorType> _traits;
        IteratorType _point;
    public:
        typedef typename _traits::value_type         value_type;
        typedef typename _traits::difference_type    difference_type;
        typedef typename _traits::pointer            pointer;
        typedef typename _traits::reference          reference;
        typedef typename _traits::iterator_category  iterator_category;

        reverse_iterator() : _point(IteratorType()) {}

        explicit reverse_iterator(const IteratorType &p) : _point(p) {}

        reverse_iterator(const reverse_iterator &it) : _point(it._point) {}

        ~reverse_iterator() {}

        // возможно понадобятся операторы присвоения для конст
        template <class Type>
        operator reverse_iterator<Type>() const {
            return reverse_iterator<Type>(_point);
        }

        template <class Iter>
        reverse_iterator&	operator=(reverse_iterator<Iter> const & other) {
            _point = &(*other);
            return *this;
        }

        IteratorType base() const {
            return _point;
        }

        reference operator* () const {
            return *_point;
        }

        pointer operator-> () const {
            return _point; // &* - ?
        }

        reverse_iterator &operator++() {
            --_point;
            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator temp(*this);
            --_point;
            return temp;
        }

        reverse_iterator operator+(difference_type n) const {
            return iterator_vector(_point - n);
        }

        reverse_iterator operator+=(difference_type n) {
            _point -= n;
            return *this;
        }

        reverse_iterator &operator--() {
            ++_point;
            return *this;
        }

        reverse_iterator operator--(int) {
            reverse_iterator temp(*this);
            ++_point;
            return temp;
        }

        reverse_iterator operator-(difference_type n) const {
            return iterator_vector(_point + n);
        }

        reverse_iterator operator-=(difference_type n) {
            _point += n;
            return *this;
        }

        reference operator[](difference_type n) {
            return *(*this + n);
        }

// Base() don't need
//        template <class Iterator>
//        friend bool	operator==(const reverse_iterator<Iterator>& A, const reverse_iterator<Iterator>& B);
//
//        template <class Iterator1, class Iterator2>
//        friend bool	operator==(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B);
//
//        template <class Iterator>
//        friend bool	operator!=(const reverse_iterator<Iterator>& A, const reverse_iterator<Iterator>& B);
//
//        template <class Iterator1, class Iterator2>
//        friend bool	operator!=(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B);
//
//        template <class Iterator>
//        friend bool	operator<(const reverse_iterator<Iterator>& A, const reverse_iterator<Iterator>& B);
//
//        template <class Iterator1, class Iterator2>
//        friend bool	operator<(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B);
//
//        template <class Iterator>
//        friend bool	operator<=(const reverse_iterator<Iterator>& A, const reverse_iterator<Iterator>& B);
//
//        template <class Iterator1, class Iterator2>
//        friend bool	operator<=(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B);
//
//        template <class Iterator>
//        friend bool	operator>(const reverse_iterator<Iterator>& A, const reverse_iterator<Iterator>& B);
//
//        template <class Iterator1, class Iterator2>
//        friend bool	operator>(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B);
//
//        template <class Iterator>
//        friend bool	operator>=(const reverse_iterator<Iterator>& A, const reverse_iterator<Iterator>& B);
//
//        template <class Iterator1, class Iterator2>
//        friend bool	operator>=(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B);
//
//        template <class Iterator>
//        friend reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it);
//
//        template <class Iterator>
//        friend typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator>& first, const reverse_iterator<Iterator>& second);
    };

    template <class Iterator>
    bool	operator==(const reverse_iterator<Iterator>& A, const reverse_iterator<Iterator>& B) {
        return A.base() == B.base();
    }

    template <class Iterator1, class Iterator2>
    bool	operator==(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B) {
        return (*(A.base()) == *(B.base()));
    }

    template <class Iterator>
    bool	operator!=(const reverse_iterator<Iterator>& A, const reverse_iterator<Iterator>& B) {
        return !(A == B);
    }

    template <class Iterator1, class Iterator2>
    bool	operator!=(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B) {
        return !(A == B);
    }

    template <class Iterator>
    bool	operator<(const reverse_iterator<Iterator>& A, const reverse_iterator<Iterator>& B) {
        return A.base() > B.base();
    }

    template <class Iterator1, class Iterator2>
    bool	operator<(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B) {
        return *(A.base()) > *(B.base());
    }

    template <class Iterator>
    bool	operator<=(const reverse_iterator<Iterator>& A, const reverse_iterator<Iterator>& B) {
        return A < B || A == B;
    }

    template <class Iterator1, class Iterator2>
    bool	operator<=(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B) {
        return A < B || A == B;
    }

    template <class Iterator>
    bool	operator>(const reverse_iterator<Iterator>& A, const reverse_iterator<Iterator>& B) {
        return A.base() < B.base();
    }

    template <class Iterator1, class Iterator2>
    bool	operator>(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B) {
        return *(A.base()) < *(B.base());
    }

    template <class Iterator>
    bool	operator>=(const reverse_iterator<Iterator>& A, const reverse_iterator<Iterator>& B) {
        return A > B || A == B;
    }

    template <class Iterator1, class Iterator2>
    bool	operator>=(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B) {
        return A > B || A == B;
    }

    template <class Iterator>
    reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it) {
        return reverse_iterator<Iterator>(it - n);
    }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator>& first, const reverse_iterator<Iterator>& second) {
        return first.base() - second.base();
    }

    template <class T>
    class iterator_vector {
    private:
        typedef iterator_traits<T> iterator_type;
        T _point;
    public:
        typedef typename iterator_type::value_type         value_type;
        typedef typename iterator_type::difference_type    difference_type;
        typedef typename iterator_type::pointer            pointer;
        typedef typename iterator_type::reference          reference;
        typedef typename iterator_type::iterator_category  iterator_category;

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
//        template <class Iterator>
//        friend bool	operator==(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B);
//
//        template <class Iterator1, class Iterator2>
//        friend bool	operator==(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B);
//
//        template <class Iterator1, class Iterator2>
//        friend bool	operator>(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B);
//
//        template <class Iterator1, class Iterator2>
//        friend bool	operator<(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B);
//
//        template <class Iterator>
//        friend  bool	operator>(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B);
    };

    template <class Iterator1, class Iterator2>
    bool	operator==(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return &(*A) == &(*B);
    }

//    template <class Iterator>
//    bool	operator!=(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B) {
//        return !(A == B);
//    }

    template <class Iterator1, class Iterator2>
    bool	operator!=(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return !(A == B);
    }

//    template <class Iterator>
//    bool	operator<=(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B) {
//        return A < B || A == B;
//    }

    template <class Iterator1, class Iterator2>
    bool	operator<=(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return A < B || A == B;
    }

    template <class Iterator1, class Iterator2>
    bool	operator>(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return &(*A) > &(*B);
    }

    template <class Iterator1, class Iterator2>
    bool	operator<(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return &(*A) < &(*B);
    }

//    template <class Iterator>
//    bool	operator>(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B) {
//        return &(*A) > &(*B);
//    }

//    template <class Iterator>
//    bool	operator>=(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B) {
//        return A > B || A == B;
//    }

    template <class Iterator1, class Iterator2>
    bool	operator>=(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return A > B || A == B;
    }

//    template <class Iterator>
//    iterator_vector<Iterator>	operator+(typename iterator_vector<Iterator>::difference_type n, const iterator_vector<Iterator>& it) {
//        return iterator_vector<Iterator>(it + n);
//    }
//
//    template <class Iterator>
//    typename iterator_vector<Iterator>::difference_type	operator-(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B) {
//        return &(*A) - &(*B);
//    }

    template <class Iterator1, class Iterator2>
    typename iterator_vector<Iterator1>::difference_type	operator-(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return &(*A) - &(*B);
    }

}
