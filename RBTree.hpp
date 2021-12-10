#pragma once
#include "iterator_traits.hpp"
#include "pair_n_node.hpp"

namespace ft {

    template <class Value, class Compare, class Alloc = std::allocator<Value> >
    class RBTree {
    public:
        typedef Alloc allocator_type;
        typedef typename allocator_type::pointer node_ptr;
    private:
        allocator_type	_alloc;
        Compare _compare;
    public:
        node_ptr create_node(Value toAdd) {
            node_ptr new_node = _alloc.allocate(1);
            _alloc.construct(new_node, toAdd);
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

        node_ptr	find_node(node_ptr tmp, Value key) const  {
            if (tmp) {
                if (_compare(tmp->pair, key))
                    return find_node(tmp->right, key);
                else if (_compare(key, tmp->pair)){
                    return find_node(tmp->left, key);
                }
            }
            return tmp;
        }

        node_ptr	lower(node_ptr root, Value key) const {
            node_ptr tmp = NULL;
            while (root) {
                if (_compare(root->pair, key))
                    root = root->right;
                else
                {
                    if (root->left) {
                        tmp = lower(root->left, key);
                        if (tmp)
                            root = tmp;
                        break;
                    }
                    else
                        break;
                }
            }
            return root;
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
                    if (!_compare(tmp->pair, new_node->pair) && !_compare(new_node->pair, tmp->pair)) {
                        if (tmp != new_node)
                            delete_node(new_node);
                        return false;
                    }
                    else if (_compare(new_node->pair, tmp->pair)) {
                        if (tmp->left)
                            tmp = tmp->left;
                        else {
                            tmp->left = new_node;
                            new_node->parent = tmp;
                            break;
                        }
                    }
                    else {
                        if (tmp->right)
                            tmp = tmp->right;
                        else {
                            tmp->right = new_node;
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
        }

        bool	erase(node_ptr* root, Value key) {
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

            while (some != *root && some->isBlack) {
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
            }
        }

        void	rotate_left(node_ptr node, node_ptr* root) {
            node_ptr	y = node->right; // y

            y->parent = node->parent;

            if (y->parent) {
                if (y->parent->right == node)
                    y->parent->right = y;
                else
                    y->parent->left = y;
            }
            node->parent = y;
            node->right = y->left;
            if (node->right) {
                if (node->right->parent == y)
                    node->right->parent = node;
                else
                    node->right->parent = node;
            }
            y->left = node;
            bool	color = node->isBlack;
            node->isBlack = y->isBlack;
            y->isBlack = color;
            if (!y->parent)
                *root = y;
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

    };

}