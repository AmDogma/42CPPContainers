#pragma once
#include "iterator_traits.hpp"

namespace ft {

    template <class Key, class Val, class Alloc = std::allocator<ft::node<const Key, Val> > >
    class RBTree {
    public:
        typedef Key first_type;
        typedef Val second_type;
        typedef Alloc allocator_type;
//        typedef typename allocator_type::value_type node;
        typedef ft::pair<const first_type, second_type> pair;
        typedef node<const first_type, second_type> node;
//        typedef typename allocator_type::reference node_ptr;
        typedef node* node_ptr;
    private:
        allocator_type	_alloc;
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
//        node_ptr	min_node(node_ptr some, bool root = true) const {
//            if (some) {
//                if (root) {
//                    while (some->parent)
//                        some = some->parent;
//                }
//                while (some->left)
//                    some = some->left;
//            }
//            return some;
//        }
//
//        node_ptr	max_node(node_ptr some, bool root = true) const {
//            if (some) {
//                if (root) {
//                    while (some->parent)
//                        some = some->parent;
//                }
//                while (some->right) {
//                    some = some->right;
//                }
//            }
//            return some;
//        }

        node_ptr	find_node(node_ptr* root, first_type key) const  {
            node_ptr	tmp = *root;
            while (tmp) {
                if (tmp->pair.first == key)
                    return tmp;
                else if (key > tmp->pair.first) {
                    if (tmp->right)
                        tmp = tmp->right;
                    else
                        break;
                }
                else {
                    if (tmp->left)
                        tmp = tmp->left;
                    else
                        break;
                }
            }
            return NULL;
        }
//
//        node_ptr	find_lower_node(node_ptr* root, first_type key) const  {
//            node_ptr	tmp = *root;
//            while (tmp) {
//                if (tmp->pair.first == key)
//                    return tmp;
//                else if (key > tmp->pair.first) {
//                    if (tmp->right)
//                        tmp = tmp->right;
//                    else
//                        return NULL;
//                }
//                else {
//                    if (tmp->left)
//                        tmp = tmp->left;
//                    else
//                        return tmp;
//                }
//            }
//            return NULL;
//        }
//
//        node_ptr	find_upper_node(node_ptr* root, first_type key) const  {
//            node_ptr	tmp = *root;
//            while (tmp) {
//                if (tmp->pair.first == key) {
//                    if (tmp->right)
//                        return tmp->right;
//                    return NULL;
//                }
//                else if (key > tmp->pair.first) {
//                    if (tmp->right)
//                        tmp = tmp->right;
//                    else
//                        return NULL;
//                }
//                else {
//                    if (tmp->left)
//                        tmp = tmp->left;
//                    else
//                        return tmp;
//                }
//            }
//            return NULL;
//        }
//
        node_ptr	find_big(node_ptr n, node_ptr root) const {

            if (!n)
                return NULL;
            else if (n->right)
                return min_node(n->right);
            else if (n == max_node(root))
                return NULL;
            else if (n->parent) { // to delete
                while (n->parent->right == n)
                    n = n->parent;
                return n->parent;
            }
            std::cout << "ERROR FIND_BIG" << std::endl;// to delete
            while (n->parent->right == n)
                n = n->parent;
            return n->parent;
        }

        node_ptr	find_low(node_ptr n, node_ptr root) const {
            if (!n)
                return max_node(root);
            else if (n->left)
                return max_node(n->left);
            else if (n == min_node(root)) // do wee need to care this?
                return NULL;
            else if (n->parent) { // to delete
                while (n->parent->left == n)
                    n = n->parent;
                return n->parent;
            }
            std::cout << "ERROR FIND_LOW" << std::endl;// to delete
            while (n->parent->left == n)
                n = n->parent;
            return n->parent;
        }

//        void	clear(node_ptr* n, node_ptr end = NULL, bool root = true) {
//            node_ptr	tmp = *n;
//            if (tmp && tmp->end) {
//                if (root) {
//                    while (tmp->parent)
//                        tmp = tmp->parent;
//                }
//                while (tmp)
//                    erase(&tmp, tmp->pair.first);
//            }
//            delete_node(end);
//            *n = NULL;
//        }
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
//                new_node->end->parent = *root;
                new_node->isBlack = true;
            }
            else {
                node_ptr	tmp = *root;
                while (tmp) {
                    if (tmp->pair.first == new_node->pair.first) {
                        if (tmp != new_node)
                            delete_node(new_node);
                        return false;
                    }
                    else if (new_node->pair.first > tmp->pair.first) {
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

        bool	erase(node_ptr* root, first_type key) {
            node_ptr	remove = find_node(root, key);
            if (remove) {
                node_ptr    replace = NULL;
                if (remove->left)
                    replace = erase_left(remove, root);
                else if (remove->right)
                    replace = erase_right(remove, root);
                else
                    replace = erase_not_child(remove, root);
                if (replace) {
                    remove->pair.first = replace->pair.first;
                    remove->pair.second = replace->pair.second;
                }
                else
                    replace = remove;
                if (replace == remove && remove == *root) {
                    *root = NULL;
//                    if (replace->end)
//                        replace->end->parent = NULL;
                }
                delete_node(replace);
                return true;
            }
            return false;
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
            node_ptr	child;
            while (some) {
                child = some->right;
                if (child) {
                    right = child->right;
                    left = child->left;
                    if ((right || left) && (!right || right->isBlack == true) && (!left || left->isBlack == true)) {
                        if (child->isBlack == true) {
                            child->isBlack = false;
                            some->isBlack = true;
                        }
                        if (child->isBlack == false)
                            rotate_left(some, root);
                        else
                            some = some->parent;
                    }
                    else if (right && child->isBlack == true) {
                        if (left && left->isBlack == false && right->isBlack == true) {
                            rotate_right(child, root);
                            right = child;
                            child = left;
                        }
                        if (right->isBlack == false && (!left || left->isBlack == true || !some->left))
                            rotate_left(some, root);
                        else
                            some = some->parent;
                    }
                    else if (child->isBlack == true && some->isBlack == false) {
                        some->isBlack = true;
                        child->isBlack = false;
                        some = some->parent;
                    }
                    else
                        some = some->parent;
                }
                else
                    some = some->parent;
                if (*root)
                    (*root)->isBlack = true;
            }
        }

    };

}