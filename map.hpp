#pragma once
#include "RBTree.hpp"

namespace ft {

    template <class T1, class T2>
    pair<T1,T2>	make_pair(T1 x, T2 y) {
        return ft::pair<T1, T2>(x, y);
    }

    template <class Key,                                     // map::key_type
            class T,                                       // map::mapped_type
            class Compare = std::less<Key>,                     // map::key_compare
            class Alloc = std::allocator<ft::pair<const Key,T> > >    // map::allocator_type
    class map {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef Compare key_compare;
        typedef ft::pair<const Key, T> value_type; // ft::pair<const typename check_const<key_type>::type, mapped_type>
        typedef std::less<ft::pair<const Key,T> >	value_compare; //  pair_compare ?
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference	const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
//        typedef ft::map_iterator<ft::pair<Key, T> >	iterator;
//        typedef ft::map_iterator<const ft::pair<Key, T> >	const_iterator;
//        typedef ft::reverse_iterator<iterator>	reverse_iterator;
//        typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
    private:
        typedef ft::pair<Key, T> pair;
        typedef RBTree<Key, T> tree_type;
        typedef node<Key, T> node;
        typedef typename tree_type::node_ptr node_ptr;
        tree_type	_tree;
        node_ptr	_root;
        node_ptr	_end;
        allocator_type	_alloc;
        key_compare	_k_comp;
        value_compare	_v_comp;
        size_type	_size;
    public:
        explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _k_comp(comp), _alloc(alloc), _root(NULL), _end(NULL), _size(0) {
            _end = _tree.create_node(ft::make_pair(key_type(), mapped_type()));
        }
        template <class InputIterator>
        map (InputIterator first, InputIterator last,
             const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type()) {

        }
        map (const map& x) {

        }

        bool empty() const {
            return _size == 0;
        }
    };
}