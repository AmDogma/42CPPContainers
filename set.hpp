#pragma once
#include "RBTree.hpp"
#include "iterator.hpp"
#include "utils.hpp"

namespace ft {

    template <class Key, class Compare = std::less<Key>,
            class Alloc = std::allocator<Key> >
    class set {
    public:
        typedef Key key_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef Compare key_compare;
        typedef key_compare value_compare;
        typedef key_type value_type;
        typedef Alloc allocator_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
    private:
        typedef typename Alloc::template rebind<node<value_type> >::other node_allocator_type;
        typedef RBTree<value_type , value_compare , node_allocator_type> tree_type;
    public:
        typedef typename ft::map_iterator<const value_type> iterator;
        typedef typename ft::map_iterator<const value_type> const_iterator;
        typedef typename ft::reverse_iterator<iterator> reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
    private:
        typedef typename ft::node<value_type>* node_ptr;
        tree_type	_tree;
        node_ptr	_root;
        allocator_type	_alloc;
        key_compare	_k_comp;
        size_type	_size;
    public:
        explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
                : _root(NULL), _alloc(alloc), _k_comp(comp), _size(0) {
            _root = _tree.create_node(value_type());
        }

        template <class InputIterator>
        set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type()) : _root(NULL), _alloc(alloc), _k_comp(comp), _size(0) {
            _root = _tree.create_node(value_type());
            insert(first, last);
        }

        ~set() {
            _tree.clear(&_root->parent);
            _tree.clear(&_root);
        }

        set (const set& other) : _root(NULL), _alloc(other._alloc), _k_comp(other._k_comp), _size(0) {
            _root = _tree.create_node(value_type());
            *this = other;
        }

        set& operator= (const set& other) {
            clear();
            _alloc = other._alloc;
            _k_comp = other._k_comp;
            insert(other.begin(), other.end());
            return *this;
        }

        iterator begin() {
            return iterator(_root, _tree.min_node(_root->parent));
        }

        const_iterator begin() const {
            return const_iterator(_root, _tree.min_node(_root->parent));
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

        ft::pair<iterator, bool> insert (const value_type& val) {
            bool res = _tree.insert(&_root->parent, _tree.create_node(val));
            _size += res;
            node_ptr forIter = _tree.find_node(_root->parent, val);
            return ft::pair<iterator, bool>(iterator(_root, forIter), res);
        }

        iterator insert (iterator, const value_type& val) {
            _size += _tree.insert(&_root->parent, _tree.create_node(val));
            node_ptr forIter = _tree.find_node(_root->parent, val);
            return iterator(_root, forIter);
        }

        template <class InputIterator>
        void insert (InputIterator first, InputIterator last) {
            for (; first != last; ++first)
                insert(*first);
        }

        void erase (iterator position) {
            bool res = _tree.erase(&_root->parent, *position);
            if (res)
                --_size;
        }

        size_type erase (const key_type& k) {
            bool res = (bool)_tree.erase(&_root->parent, k);
            if (res)
                --_size;
            return res;
        }

        void erase (iterator first, iterator last) {
            while ( first != last)
                erase(first++);
        }

        void swap (set& x) {
            std::swap(_root, x._root);
            std::swap(_alloc, x._alloc);
            std::swap(_k_comp, x._k_comp);
            std::swap(_size, x._size);
        }

        void clear() {
            _tree.clear(&_root->parent);
            _root->parent = NULL;
            _size = 0;
        }

        key_compare key_comp() const {
            return _k_comp;
        }

        value_compare value_comp() const {
            return _k_comp;
        }

        iterator find (const key_type& k) {
            node_ptr forIter = _tree.find_node(_root->parent, k);
            return iterator(_root, forIter);
        }

        const_iterator find (const key_type& k) const {
            node_ptr forIter = _tree.find_node(_root->parent, k);
            return const_iterator(_root, forIter);
        }

        size_type count (const key_type& k) const {
            if (_tree.find_node(_root->parent, k))
                return 1;
            return 0;
        }

        iterator lower_bound (const key_type& k) {
            return (iterator(_root, _tree.lower(_root->parent, k)));
        }

        const_iterator lower_bound (const key_type& k) const {
            return (const_iterator(_root, _tree.lower(_root->parent, k)));
        }

        iterator upper_bound (const key_type& k) {
            node_ptr temp = _tree.lower(_root->parent, k);
            iterator res(_root, temp);
            if (temp && temp->pair == k)
                ++res;
            return iterator(res);
        }

        const_iterator upper_bound (const key_type& k) const {
            node_ptr temp = _tree.lower(_root->parent, k);
            iterator res(_root, temp);
            if (temp && temp->pair == k)
                ++res;
            return const_iterator(res);
        }

        ft::pair<iterator, iterator> equal_range (const key_type& k) {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        allocator_type get_allocator() const {
            return _alloc;
        }

    };

    template <class Key, class Compare, class Allocator>
    bool operator==(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
        return x.size() == y.size() && \
				ft::equal( x.begin(), x.end(), y.begin() ) && \
				ft::equal( y.begin(), y.end(), x.begin() );
    }

    template <class Key, class Compare, class Allocator>
    bool operator!=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
        return !(x == y);
    }

    template <class Key, class Compare, class Allocator>
    bool operator< (const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
        return ft::lexicographical_compare( x.begin(), x.end(), y.begin(), y.end()) && x != y;
    }

    template <class Key, class Compare, class Allocator>
    bool operator> (const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
        return y < x;
    }

    template <class Key, class Compare, class Allocator>
    bool operator>=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
        return x > y || x == y;
    }

    template <class Key, class Compare, class Allocator>
    bool operator<=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
        return x < y || x == y;
    }

    template <class Key, class Compare, class Allocator>
    void swap(set<Key,Compare,Allocator>& x, set<Key,Compare,Allocator>& y) {
        x.swap(y);
    }
}
