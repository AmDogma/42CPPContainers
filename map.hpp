#pragma once
#include "RBTree.hpp"

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
        typedef Alloc allocator_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
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
        typedef node<const key_type, mapped_type> node;
        typedef typename tree_type::node_ptr node_ptr;
        tree_type	_tree;
        node_ptr	_root;
        node_ptr	_end; // maybe don't need
        allocator_type	_alloc;
        key_compare	_k_comp;
        value_compare	_v_comp;
        size_type	_size;
    public:

        explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _k_comp(comp), _alloc(alloc), _root(NULL), _end(NULL), _size(0) {
            _end = _tree.create_node(ft::make_pair(key_type(), mapped_type()));
        }

        template <class InputIterator>
        map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type()) : _k_comp(comp), _alloc(alloc), _root(NULL), _end(NULL), _size(0)  {
            _end = _tree.create_node(ft::make_pair(key_type(), mapped_type()));
            insert(first, last);
        }

        ~map() {
            _tree.clear(&_root);
            _tree.delete_node(_end);
        };

        map (const map& other) : _root(NULL) {
            _end = _tree.create_node(ft::make_pair(key_type(), mapped_type()));
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

        void inserter(const value_type &some) { // myft to delete
            _tree.insert(&_root, _tree.create_node(some));
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

        void clear() {
            _tree.clear(&_root);
            _size = 0;
        }

//        pair<iterator,bool> insert (const value_type& val) {
//
//        }

//        iterator insert (iterator position, const value_type& val) {
//
//        }

//        template <class InputIterator>
//        void insert (InputIterator first, InputIterator last) {
//
//        }

    };
}