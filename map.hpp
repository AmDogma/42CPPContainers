#pragma once
#include "RBTree.hpp"
#include "iterator.hpp"
#include "lex_n_equal.hpp"

namespace ft {

    template <class Key,                                     // map::key_type
            class T,                                       // map::mapped_type
            class Compare = std::less<Key>,                     // map::key_compare
            class Alloc = std::allocator<ft::pair<const Key,T> > >    // map::allocator_type
    class map {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef Compare key_compare;
        typedef ft::pair<const Key, T> value_type; // ft::pair<const typename check_const<key_type>::typecheck_const<key_type>::type, mapped_type>
        typedef std::less<ft::pair<const Key, T> >	value_compare; //  pair_compare ?
//        typedef Alloc allocator_type;
//        typedef value_type& reference;
//        typedef const value_type& const_reference;
//        typedef typename allocator_type::pointer pointer;
//        typedef typename allocator_type::const_pointer const_pointer;
        typedef std::size_t size_type;

//        typedef typename allocator_type::reference reference;
//        typedef typename allocator_type::const_reference	const_reference;
//        typedef std::ptrdiff_t difference_type;
//
        typedef ft::map_iterator<value_type>	iterator;
        typedef ft::map_iterator<const value_type>	const_iterator;
        typedef ft::reverse_iterator<iterator>	reverse_iterator;
        typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

    private:
        typedef ft::pair<const Key, T> pair;
        typedef RBTree<const Key, T> tree_type;
        typedef typename tree_type::allocator_type allocator_type; // ? test allocator?
        typedef node<const key_type, mapped_type> node;
        typedef typename tree_type::node_ptr node_ptr;
        tree_type	_tree;
        node_ptr	_root;
        allocator_type	_alloc;
        key_compare	_k_comp;
        value_compare	_v_comp;
        size_type	_size;
    public:

        explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _alloc(alloc), _k_comp(comp), _size(0) {}

        template <class InputIterator>
        map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type()) : _root(NULL), _alloc(alloc), _k_comp(comp), _size(0) {
            insert(first, last);
        }

        ~map() {
            _tree.clear(&_root);
        };

        map (const map& other) : _root(NULL) {
            *this = other;
        }

        map& operator= (const map& other) {
            clear();
            _alloc = other._alloc;
            _k_comp = other._k_comp;
            _v_comp = other._v_comp;
            insert(other.begin(), other.end());
            return *this;
        }

        iterator begin() {
            return iterator(_root, _tree.min_node(_root));
        }

        const_iterator begin() const {
            return const_iterator(_root, _tree.min_node(_root));
        }

        iterator end() {
            return iterator(_root, NULL);
        }

        const_iterator end() const {
            return const_iterator(_root, NULL);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

        bool empty() const {
            return _size == 0;
        }

        size_type size() const {
            return _size;
        }

        size_type max_size() const {
            return (_tree.max_size());
        }

        mapped_type& operator[] (const key_type& k) {
            insert(ft::make_pair(k, mapped_type()));
            return _tree.find_node(&_root, k)->pair.second;
        }

        ft::pair<iterator, bool> insert (const value_type& val) {
            bool res = _tree.insert(&_root, _tree.create_node(val));
            _size += res;
            node_ptr forIter = _tree.find_node(&_root, val.first);
            return ft::pair<iterator, bool>(iterator(_root, forIter), res);
        }

        iterator insert (iterator, const value_type& val) {
            _size += _tree.insert(&_root, _tree.create_node(val));
            node_ptr forIter = _tree.find_node(&_root, val.first);
            return iterator(_root, forIter);
        }

        template <class InputIterator>
        void insert (InputIterator first, InputIterator last) { // нужна защита от перегрузки типами?
            for (; first != last; ++first)
                insert(*first);
        }

        void erase (iterator position) {
            bool res = _tree.erase(&_root, position->first);
            if (res)
                --_size;
        }

        size_type erase (const key_type& k) {
            bool res = _tree.erase(&_root, k);
            if (res)
                --_size;
            return res;
        }

        void erase (iterator first, iterator last) {
            for (; first != last; ++first)
                erase(first);
        }

        void swap (map& x) {
            std::swap(_root, x._root);
            std::swap(_alloc, x._alloc);
            std::swap(_k_comp, x._k_komp);
            std::swap(_v_comp, x._v_comp);
            std::swap(_size, x._size);
        }

        void clear() {
            _tree.clear(&_root);
            _size = 0;
        }

        key_compare key_comp() const {
            return _k_comp;
        }

        value_compare value_comp() const {
            return _v_comp;
        }

        iterator find (const key_type& k) {
            node_ptr forIter = _tree.find_node(&_root, k);
            return iterator(_root, forIter);
        }

        const_iterator find (const key_type& k) const {
            node_ptr forIter = _tree.find_node(&_root, k);
            return const_iterator(_root, forIter);
        }

        size_type count (const key_type& k) const { // не работает проверка
//            if (!_root)
//                return 0;
            if (_tree.find_node(&_root, k))
                return 1;
            else
                return 0;
        }

        iterator lower_bound (const key_type& k) {
            node_ptr tmp = _tree.min_node(_root);
            while (tmp && k > tmp->pair.first)
                tmp = _tree.find_big(tmp, _root);
            return iterator(_root, tmp);
        }

        const_iterator lower_bound (const key_type& k) const {
            node_ptr tmp = _tree.min_node(_root);
            while (tmp && k > tmp->pair.first)
                tmp = _tree.find_big(tmp, _root);
            return const_iterator(_root, tmp);
        }

        iterator upper_bound (const key_type& k) {
            node_ptr tmp = _tree.min_node(_root);
            while (tmp && k >= tmp->pair.first)
                tmp = _tree.find_big(tmp, _root);
            return iterator(_root, tmp);
        }

        const_iterator upper_bound (const key_type& k) const {
            node_ptr tmp = _tree.min_node(_root);
            while (tmp && k >= tmp->pair.first)
                tmp = _tree.find_big(tmp, _root);
            return const_iterator(_root, tmp);
        }

        ft::pair<iterator,iterator>             equal_range (const key_type& k){
           return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        allocator_type get_allocator() const {
            return _alloc;
        }

    };

    template <class Key, class T, class Compare, class Allocator>
    bool operator==(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
        return x.size() == y.size() && \
				ft::equal( x.begin(), x.end(), y.begin() ) && \
				ft::equal( y.begin(), y.end(), x.begin() );
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator!=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
        return !(x == y);
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator< (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
        return ft::lexicographical_compare( x.begin(), x.end(), y.begin(), y.end() ) && x != y;
    }
    
    template <class Key, class T, class Compare, class Allocator>
    bool operator> (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
        return y < x;
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator>=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
        return x > y && x == y;
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator<=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
        return x < y && x == y;
    }

    template <class Key, class T, class Compare, class Allocator>
    void swap(map<Key,T,Compare,Allocator>& x, map<Key,T,Compare,Allocator>& y) {
        x.swap(y);
    }

}