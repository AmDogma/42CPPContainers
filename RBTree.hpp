#pragma once
#include "iterator_traits.hpp"
#include "pair_n_node.hpp"

namespace ft {

    template <class Key, class Val, class Compare = std::less<Key>, class Alloc = std::allocator<ft::node<const Key, Val> > >
    class RBTree {
    public:
        typedef Key first_type;
        typedef Val second_type;
        typedef Alloc allocator_type;
//        typedef typename allocator_type::value_type node;
        typedef ft::pair<first_type, second_type> pair;
        typedef ft::node<first_type, second_type> node;
        typedef typename allocator_type::pointer node_ptr;
//        typedef node* node_ptr;
    private:
        allocator_type	_alloc;
        Compare _compare;
    public:
        node_ptr create_node(pair new_pair) {
            node_ptr new_node = _alloc.allocate(1);
            _alloc.construct(new_node, node(new_pair));
            return new_node;
        }

        void	delete_node(node_ptr some) {
            if (some) {
                _alloc.destroy(some);
                _alloc.deallocate(some, 1);
            }
        }

        void	swap_color(node_ptr some) {
            bool	color = some->isBlack;
            some->isBlack = some->right->isBlack;
            some->right->isBlack = color;
            some->left->isBlack = color;
        }

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

        node_ptr	find_node(node_ptr tmp, first_type& key) const  {
            if (tmp) {
                if (_compare(tmp->pair.first, key))
                    return find_node(tmp->right, key);
                else if (_compare(key, tmp->pair.first)){
                    return find_node(tmp->left, key);
                }
            }
            return tmp;
        }

        node_ptr	find_big(node_ptr n, node_ptr* root) const {
            if (!n)
                return NULL;
            else if (n->right)
                return min_node(n->right);
            else if (n == max_node(*root))
                return NULL;
            while (n->parent->right == n)
                n = n->parent;
            return n->parent;
        }

        node_ptr	find_low(node_ptr n, node_ptr* root) const {
            if (!n)
                return max_node(*root);
            else if (n->left)
                return max_node(n->left);
            while (n->parent->left == n)
                n = n->parent;
            return n->parent;
        }

        void	clear(node_ptr* root) {
            if (*root)
            {
                if ((*root)->left)
                    clear(&((*root)->left));
                if ((*root)->right)
                    clear(&((*root)->right));
                delete_node((*root));
            }
            *root = NULL;
        }

        size_t	max_size() const {
            return _alloc.max_size();
        }

        void	insert_balance(node_ptr* root, node_ptr some) {
            node_ptr	parent;
            node_ptr	grand;
            node_ptr	tmp;
            while (some) {
                parent = some->parent;
                grand = NULL;
                tmp = parent;
                if (parent) {
                    grand = parent->parent;
                    if (some->isBlack == false) {
                        if (parent->isBlack == true)
                            some = parent;
                        else if (grand) {
                            if (grand->left && grand->left->isBlack == false && grand->right && grand->right->isBlack == false) {
                                swap_color(grand);
                                some = grand;
                            }
                            else if (grand->right == parent) {
                                if (parent->left == some) {
                                    rotate_right(parent, root);
                                    parent = some;
                                }
                                if (parent->right == some)
                                    rotate_left(grand, root);
                                some = parent->parent;
                            }
                            else {
                                if (parent->right == some) {
                                    rotate_left(parent, root);
                                    parent = some;
                                }
                                if (parent->left == some)
                                    rotate_right(grand, root);
                                some = parent->parent;
                            }
                        }
                    }
                    else
                        some = parent;
                }
                else {
                    some->isBlack = true;
                    some = some->parent;
                }
            }
        }

        bool	insert(node_ptr* root, node_ptr new_node) {
            if (*root == NULL) {
                *root = new_node;
                new_node->isBlack = true;
            }
            else {
                node_ptr	tmp = *root;
                while (tmp) {
                    if (!_compare(tmp->pair.first, new_node->pair.first) && !_compare(new_node->pair.first, tmp->pair.first)) {
                        if (tmp != new_node)
                            delete_node(new_node);
                        return false;
                    }
                    else if (_compare(tmp->pair.first, new_node->pair.first)) {
                        if (tmp->right)
                            tmp = tmp->right;
                        else {
                            tmp->right = new_node;
                            new_node->parent = tmp;
                            break;
                        }
                    }
                    else {
                        if (tmp->left)
                            tmp = tmp->left;
                        else {
                            tmp->left = new_node;
                            new_node->parent = tmp;
                            break;
                        }
                    }
                }
            }
            insert_balance(root, new_node);
            return true;
        }

        void swap_p(node_ptr remove, node_ptr replace) {
            if (remove->parent) {
                if (remove->parent->left == remove)
                    remove->parent->left = replace;
                else
                    remove->parent->right = replace;
            }
            replace->parent = remove->parent;
            if (remove->left) {
                remove->left->parent = replace;
            }
            replace->left = remove->left;
            if (remove->right) {
                remove->right->parent = replace;
            }
            replace->right = remove->right;
            replace->isBlack = remove->isBlack;
//            if(*root == remove)
//                *root = replace;
        }

        bool	erase(node_ptr* root, first_type key) {
            node_ptr	remove = find_node(*root, key);
            if (remove) {
                node_ptr    replace = NULL;
                if (remove->left)
                    replace = erase_left(remove, root);
                else if (remove->right)
                    replace = erase_right(remove, root);
                else
                    erase_not_child(remove, root);
                if (replace)
                    swap_p(remove, replace);
                if (remove == *root) {
                    if (replace)
                        *root = replace;
                    else
                        *root = NULL;
                }
                delete_node(remove);
                return true;
            }
            return false;
        }

        void	erase(node_ptr* root, node_ptr remove) {
//            node_ptr	remove = find_node(*root, key);
            if (remove) {
                node_ptr    replace = NULL;
                if (remove->left)
                    replace = erase_left(remove, root);
                else if (remove->right)
                    replace = erase_right(remove, root);
                else
                    erase_not_child(remove, root);
                if (replace)
                    swap_p(remove, replace);
                if (remove == *root) {
                    if (replace)
                        *root = replace;
                    else
                        *root = NULL;
                }
                delete_node(remove);
            }
        }

        node_ptr	erase_left(node_ptr some, node_ptr* root) {
            node_ptr	replace = max_node(some->left);
            if (replace) {
                if (replace == some->left) {
                    some->left = replace->left;
                    if (replace->left)
                        replace->left->parent = some;
                }
                else {
                    replace->parent->right = replace->left;
                    if (replace->left)
                        replace->left->parent = replace->parent;
                }
                if (replace->isBlack == true) {
                    if (replace->left && replace->left->isBlack == false)
                        replace->left->isBlack = true;
                    erase_balance(root, replace->parent);
                }
            }
            return replace;
        }

        node_ptr	erase_right(node_ptr some, node_ptr* root) {
            node_ptr	replace = min_node(some->right);
            if (replace) {
                if (replace == some->right) {
                    some->right = replace->right;
                    if (replace->right)
                        replace->right->parent = some;
                }
                else {
                    replace->parent->left = replace->right;
                    if (replace->right)
                        replace->right->parent = replace->parent;
                }
                if (replace->isBlack == true) {
                    if (replace->right && replace->right->isBlack == false)
                        replace->right->isBlack = true;
                    erase_balance(root, replace->parent);
                }
            }
            return replace;
        }

        node_ptr	erase_not_child(node_ptr some, node_ptr* root) {
            node_ptr	replace = some;
            if (replace && replace->parent) {
                if (replace->parent->right == replace)
                    replace->parent->right = NULL;
                else
                    replace->parent->left = NULL;
                if (replace->isBlack == true) {
                    if (replace->right && replace->right->isBlack == false)
                        replace->right->isBlack = true;
                    erase_balance(root, replace->parent);
                }
            }
            return replace;
        }

        void	erase_balance(node_ptr* root, node_ptr some) {
            node_ptr	right;
            node_ptr	left;
            node_ptr	brother;
            while (some) {
                brother = some->right; //same
                if (brother) {
                    right = brother->right;
                    left = brother->left;
                    if ((right || left) && (!right || right->isBlack == true) && (!left || left->isBlack == true)) {
                        if (brother->isBlack == true) {
                            brother->isBlack = false;
                            some->isBlack = true;
                            rotate_left(some, root);
                        }
                        else
                            some = some->parent;
                    }
                    else if (right && brother->isBlack == true) {
                        if (left && left->isBlack == false && right->isBlack == true) {
                            rotate_right(brother, root);
                            right = brother;
                            brother = left;
                        }
                        if (right->isBlack == false && (!left || left->isBlack == true || !some->left))
                            rotate_left(some, root);
                        else
                            some = some->parent;
                    }
                    else if (brother->isBlack == true && some->isBlack == false) {
                        some->isBlack = true;
                        brother->isBlack = false;
                        some = some->parent;
                    }
                    else
                        some = some->parent;
                }
                else
                    break;
//                    some = some->parent;
            }
        }

        void	rotate_left(node_ptr some, node_ptr* root) {
            node_ptr	right = some->right;
            right->parent = some->parent;
            if (right->parent) {
                if (right->parent->right == some)
                    right->parent->right = right;
                else
                    right->parent->left = right;
            }
            some->parent = right;
            some->right = right->left;
            if (some->right) {
                if (some->right->parent == right)
                    some->right->parent = some;
                else
                    some->right->parent = some;
            }
            right->left = some;
            bool	color = some->isBlack;
            some->isBlack = right->isBlack;
            right->isBlack = color;
            if (!right->parent)
                *root = right;
        }

        void	rotate_right(node_ptr some, node_ptr* root) {
            node_ptr	left = some->left;
            left->parent = some->parent;
            if (left->parent) {
                if (left->parent->left == some)
                    left->parent->left = left;
                else
                    left->parent->right = left;
            }
            some->parent = left;
            some->left = left->right;
            if (some->left) {
                if (some->left->parent == left)
                    some->left->parent = some;
                else
                    some->left->parent = some;
            }
            left->right = some;
            some->isBlack = false;
            left->isBlack = true;
            if (!left->parent)
                *root = left;
        }

//        void 	rotate_right(node_ptr	node, node_ptr* _root){
//            node_ptr y;
//
//            y = node->left;
//            node->left = y->right;
//            if (y->right)
//                y->right->parent = node;
//            y->parent = node->parent;
//            if (node->parent == NULL)
//                *_root = y;
//            else if (node == node->parent->left)
//                node->parent->left = y;
//            else
//                node->parent->right = y;
//            y->right = node;
//            node->parent = y;
//        }
//        void 	rotate_left(node_ptr node, node_ptr* _root){
//            node_ptr y;
//
//            y = node->right;
//            node->right = y->left;
//            if (y->left)
//                y->left->parent = node;
//            y->parent = node->parent;
//            if (node->parent == NULL)
//                *_root = y;
//            else if (node == node->parent->left)
//                node->parent->left = y;
//            else
//                node->parent->right = y;
//            y->left = node;
//            node->parent = y;
//        }

        void erase_balances(node_ptr* _root, node_ptr x){
            node_ptr brother;
            while (x != *_root && x->isBlack){
                if (x == x->parent->left){
                    brother = x->parent->right;
                    //case 1
                    if (!brother->isBlack){
                        brother->isBlack = true;
                        x->parent->isBlack = false;
                        rotate_left(x->parent, _root);
                        brother = x->parent->right;
                    }
                    //case 2
                    if (brother->left->isBlack && brother->right->isBlack){
                        brother->isBlack = false;
                        x = x->parent;
                    }
                    else{
                        //case 3
                        if (brother->right->isBlack){
                            brother->left->isBlack = true;
                            brother->isBlack = false;
                            rotate_right(brother, _root);
                            brother = x->parent->right;
                        }
                        //case 4
                        brother->isBlack = x->parent->isBlack;
                        x->parent->isBlack = true;
                        brother->right->isBlack = true;
                        rotate_left(x->parent, _root);
                        x = *_root;
                    }
                }
                else{
                    brother = x->parent->left;
                    //case 1
                    if (!brother->isBlack){
                        brother->isBlack = true;
                        x->parent->isBlack = false;
                        rotate_right(x->parent, _root);
                        brother = x->parent->left;
                    }
                    //case 2
                    if (brother->right->isBlack && brother->left->isBlack){
                        brother->isBlack = false;
                        x = x->parent;
                    }
                    else{
                        //case 3
                        if (brother->left->isBlack){
                            brother->right->isBlack = true;
                            brother->isBlack = false;
                            rotate_left(brother, _root);
                            brother = x->parent->left;
                        }
                        //case 4
                        brother->isBlack = x->parent->isBlack;
                        x->parent->isBlack = true;
                        brother->left->isBlack = true;
                        rotate_right(x->parent, _root);
                        x = *_root;
                    }
                }
            }
        }

    };

}