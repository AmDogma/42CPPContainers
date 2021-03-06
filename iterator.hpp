#pragma once
#include <iostream>
#include "iterator_traits.hpp"
#include "RBTree.hpp"
#include "utils.hpp"

namespace ft {

    template <class Val>
    class   map_iterator {
    public:
        typedef typename ft::iterator_traits<Val*>::value_type 		value_type;
        typedef typename ft::iterator_traits<Val*>::reference 		reference;
        typedef typename ft::iterator_traits<Val*>::pointer			pointer;
        typedef typename ft::iterator_traits<Val*>::difference_type	difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef ft::node<typename ft::remove_const<Val>::type >* node_ptr;
    private:
        node_ptr _root;
        node_ptr _base;

        node_ptr	min_node(node_ptr some) const {
            if (some) {
                while (some->left)
                    some = some->left;
            }
            return some;
        }

        node_ptr	max_node(node_ptr some) const {
            if (some) {
                while (some->right)
                    some = some->right;
            }
            return some;
        }

    public:
        map_iterator() : _root(NULL), _base(NULL) {}

        explicit map_iterator(const node_ptr& root, const node_ptr& node) : _root(root), _base(node) {} // static_cast<pointer>(node)

        map_iterator(const map_iterator& other) : _root(other._root), _base(other._base) {}

        ~map_iterator() {}

        template <class Type>
        operator map_iterator<const Type>() const {
            return map_iterator<const Type>(_root, _base);
        }

        reference 	operator*() const {
            return (_base->pair);
        }

        pointer 	operator->() const {
            return &(_base->pair);
        }

        map_iterator&	operator++() {
            if (!_base)
                return *this;
            else if (_base->right)
                _base =  min_node(_base->right);
            else if (_base == max_node(_root->parent))
                _base = NULL;
            else {
                while (_base->parent->right == _base)
                    _base = _base->parent;
                _base = _base->parent;
            }
            return *this;
        }

        map_iterator	operator++(int) {
            map_iterator<Val>	tmp(*this);
            ++(*this);
            return tmp;
        }

        map_iterator&	operator--() {
            if (!_base)
                _base = max_node(_root->parent);
            else if (_base->left)
                _base =  max_node(_base->left);
            else {
                while (_base->parent->left == _base)
                    _base = _base->parent;
                _base = _base->parent;
            }
            return *this;
        }

        map_iterator	operator--(int) {
            map_iterator<Val>	tmp(*this);
            --(*this);
            return tmp;
        }

        template <class Iterator1, class Iterator2>
        friend  bool	operator==(const map_iterator<Iterator1>& A, const map_iterator<Iterator2>& B);

    };

    template <class Iterator1, class Iterator2>
    bool	operator==(const map_iterator<Iterator1>& A, const map_iterator<Iterator2>& B) {
        return A._base == B._base;
    }


    template <class Iterator1, class Iterator2>
    bool	operator!=(const map_iterator<Iterator1>& A, const map_iterator<Iterator2>& B) {
        return !(A == B);
    }

    template <class IteratorType>
    class reverse_iterator {
    private:
        typedef iterator_traits<IteratorType> _traits;
    public:
        typedef typename _traits::value_type         value_type;
        typedef typename _traits::difference_type    difference_type;
        typedef typename _traits::pointer            pointer;
        typedef typename _traits::reference          reference;
        typedef typename _traits::iterator_category  iterator_category;
    private:
        IteratorType _point;
    public:
        reverse_iterator() : _point(IteratorType()) {}

        explicit reverse_iterator(const IteratorType &p) : _point(p) {}

        reverse_iterator(const reverse_iterator &it) : _point(it._point) {}

        ~reverse_iterator() {}

        template <class Type>
        operator reverse_iterator<Type>() const {
            return reverse_iterator<Type>(_point);
        }

        template <class Iter>
        reverse_iterator&	operator=(reverse_iterator<Iter> const & other) {
            _point = other.base();
            return *this;
        }

        IteratorType base() const {
            return _point;
        }

        reference operator* () const {
            IteratorType tmp = _point;
            --tmp;
            return *tmp;
        }

        pointer operator-> () const {
            return &(operator*());
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
            return reverse_iterator(_point - n);
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
            return reverse_iterator(_point + n);
        }

        reverse_iterator operator-=(difference_type n) {
            _point += n;
            return *this;
        }

        reference operator[](difference_type n) {
            return _point[ -n - 1];
        }

    };

    template <class Iterator1, class Iterator2>
    bool	operator==(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B) {
        return A.base() == B.base();
    }

    template <class Iterator1, class Iterator2>
    bool	operator!=(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B) {
        return !(A == B);
    }


    template <class Iterator1, class Iterator2>
    bool	operator<(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B) {
        return A.base() > B.base();
    }

    template <class Iterator1, class Iterator2>
    bool	operator<=(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B) {
        return A < B || A == B;
    }

    template <class Iterator1, class Iterator2>
    bool	operator>(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B) {
        return A.base() < B.base();
    }

    template <class Iterator1, class Iterator2>
    bool	operator>=(const reverse_iterator<Iterator1>& A, const reverse_iterator<Iterator2>& B) {
        return A > B || A == B;
    }

    template <class Iterator>
    reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it) {
        return reverse_iterator<Iterator>(it + n);
    }

    template <class Iterator1, class Iterator2>
    typename reverse_iterator<Iterator1>::difference_type	operator-(const reverse_iterator<Iterator1>& first, const reverse_iterator<Iterator2>& second) {
        return second.base() - first.base();
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
        typedef	std::random_access_iterator_tag iterator_category;

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

        template <class Iterator1, class Iterator2>
        friend bool	operator==(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B);

        template <class Iterator1, class Iterator2>
        friend bool	operator!=(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B);

        template <class Iterator1, class Iterator2>
        friend bool	operator<=(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B);

        template <class Iterator1, class Iterator2>
        friend bool	operator>(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B);

        template <class Iterator1, class Iterator2>
        friend bool	operator<(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B);

        template <class Iterator1, class Iterator2>
        friend bool	operator>=(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B);

        template <class Iterator>
        friend  typename iterator_vector<Iterator>::difference_type	operator-(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B);

        template <class Iterator1, class Iterator2>
        friend  typename iterator_vector<Iterator1>::difference_type	operator-(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B);
    };

    template <class Iterator1, class Iterator2>
    bool	operator==(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return A._point == B._point;
    }

    template <class Iterator1, class Iterator2>
    bool	operator!=(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return !(A._point == B._point);
    }

    template <class Iterator1, class Iterator2>
    bool	operator<=(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return A._point < B._point || A._point == B._point;
    }

    template <class Iterator1, class Iterator2>
    bool	operator>(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return A._point > B._point;
    }

    template <class Iterator1, class Iterator2>
    bool	operator<(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return A._point < B._point;
    }

    template <class Iterator1, class Iterator2>
    bool	operator>=(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return A._point > B._point || A._point == B._point;
    }

    template <class Iterator>
    iterator_vector<Iterator>	operator+(typename iterator_vector<Iterator>::difference_type n, const iterator_vector<Iterator>& it) {
        return iterator_vector<Iterator>(it + n);
    }

    template <class Iterator>
    typename iterator_vector<Iterator>::difference_type	operator-(const iterator_vector<Iterator>& A, const iterator_vector<Iterator>& B) {
        return A._point - B._point;
    }

    template <class Iterator1, class Iterator2>
    typename iterator_vector<Iterator1>::difference_type	operator-(const iterator_vector<Iterator1>& A, const iterator_vector<Iterator2>& B) {
        return A._point - B._point;
    }

}
