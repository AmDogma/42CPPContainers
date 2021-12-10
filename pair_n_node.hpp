#pragma once

namespace ft {

    template <class Value>
    struct node {
//        typedef K  first_type;
//        typedef V  second_type;
        Value pair;
        node*	parent;
        node*	left;
        node*	right;
        bool	isBlack;
        node() : pair(Value()), parent(NULL), left(NULL), right(NULL), isBlack(false) {}
        node(const Value& p_pair) : pair(p_pair), parent(NULL), left(NULL), right(NULL), isBlack(false) {}
        node&	operator=(const node& node) {
            pair = node.pair;
            parent = node.parent;
            left = node.left;
            right = node.right;
            isBlack = node.isBlack;
            return *this;
        }
    };

    template<class Key, class Val>
    struct pair {
        typedef Key first_type;
        typedef Val second_type;
        first_type first;
        second_type second;
        pair() : first(first_type()), second(second_type()) {}

        template<class K, class V>
        pair (const pair<K, V> &pr) : first(static_cast<Key>(pr.first)), second(static_cast<Val>(pr.second)) {} // ?? pair(const pair & pr) : first(pr.first), second(pr.second) {}

        pair(const first_type &a, const second_type &b) : first(a), second(b) {}

        pair &operator=(const pair &pr) {
            first = pr.first;
            second = pr.second;
            return (*this);
        }
    };

    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return lhs.first < rhs.first || (!(rhs.first<lhs.first) && lhs.second < rhs.second);
    }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return !(rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return rhs < lhs;
    }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return !(lhs < rhs);
    }

    template <class T1, class T2>
    pair<T1,T2>	make_pair(T1 x, T2 y) {
        return ft::pair<T1, T2>(x, y);
    }


}
