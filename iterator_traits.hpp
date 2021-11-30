#pragma once
#include <cstddef>
#include <iostream>

namespace ft {

    struct	input_iterator_tag {};
    struct	output_iterator_tag {};
    struct	forward_iterator_tag : public input_iterator_tag, public output_iterator_tag{};
    struct	bidirectional_iterator_tag : public forward_iterator_tag {};
    struct	random_access_iterator_tag : public bidirectional_iterator_tag {};

    template<class Iter>
        struct iterator_traits
        {
            typedef typename Iter::iterator_category   iterator_category;
            typedef typename Iter::value_type          value_type;
            typedef typename Iter::difference_type     difference_type;
            typedef typename Iter::pointer             pointer;
            typedef typename Iter::reference           reference;
        };

    template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
        struct iterator
        {
        public:
            typedef Category    iterator_category;
            typedef T           value_type;
            typedef Distance    difference_type;
            typedef Pointer     pointer;
            typedef Reference   reference;
        };

    template <class T>
        struct iterator_traits<T*> {
            typedef ptrdiff_t	difference_type;
            typedef T           value_type;
            typedef T*	        pointer;
            typedef T&	        reference;
            typedef random_access_iterator_tag	iterator_category; // ?
        };

    template<class T>
        struct iterator_traits<const T*> {
            typedef ptrdiff_t	difference_type;
            typedef T           value_type;
            typedef const T*    pointer;
            typedef const T&	reference;
            typedef random_access_iterator_tag	iterator_category; // ?
        };

    template<class Key, class Val>
    struct pair {
        typedef Key first_type;
        typedef Val second_type;
        first_type first;
        second_type second;
        pair() : first(), second() {} // second_type()

        template<class K, class V>
        pair (const pair<K, V> &pr) : first(static_cast<Key>(pr.first)), second(static_cast<Val>(pr.second)) {} // ?? pair(const pair & pr) : first(pr.first), second(pr.second) {}

        pair(const first_type &a, const second_type &b) : first(a), second(b) {}

        pair &operator=(const pair &pr) {
            first = pr.first;
            second = pr.second;
            return (*this);
        }
    };
    // COMPARE PAIR AND MAKE TO DO

    template <class T1, class T2>
    pair<T1,T2>	make_pair(T1 x, T2 y) {
        return ft::pair<T1, T2>(x, y);
    }


    template <class K, class V>
    struct node {
        typedef K  first_type;
        typedef V  second_type;
        ft::pair<first_type, second_type>	pair;
        node*	parent;
        node*	left;
        node*	right;
//        node*	root;
        bool	isBlack;
        node() : parent(NULL), left(NULL), right(NULL), isBlack(false) {}
        node(const ft::pair<first_type, second_type>& p_pair) : pair(p_pair), parent(NULL), left(NULL), right(NULL), isBlack(false) {}
        node&	operator=(const node& node) {
            pair = node.pair;
            parent = node.parent;
            left = node.left;
            right = node.right;
//            this->end = node.end;
            isBlack = node.isBlack;
            return *this;
        }
    };

    template< class InputIt1, class InputIt2 >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                  InputIt2 first2, InputIt2 last2 ) {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, ++first2 ) {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template< class InputIt1, class InputIt2, class Compare >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                  InputIt2 first2, InputIt2 last2,
                                  Compare comp ) {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, ++first2 ) {
            if (comp(*first1 < *first2))
                return true;
            if (comp(*first2 < *first1))
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template< class T >
    struct is_integral {
        static const bool value = false;
    };

    template<>
    struct is_integral<bool> {
        static const bool value = true;
    };

    template<>
    struct is_integral<char> {
        static const bool value = true;
    };

    template<>
    struct is_integral<wchar_t> {
        static const bool value = true;
    };

    template<>
    struct is_integral<short> {
        static const bool value = true;
    };

    template<>
    struct is_integral<int> {
        static const bool value = true;
    };

    template<>
    struct is_integral<long> {
        static const bool value = true;
    };

    template<>
    struct is_integral<long long> {
        static const bool value = true;
    };

    template<>
    struct is_integral<unsigned char> {
        static const bool value = true;
    };

    template<>
    struct is_integral<unsigned short> {
        static const bool value = true;
    };

    template<>
    struct is_integral<unsigned int> {
        static const bool value = true;
    };

    template<>
    struct is_integral<unsigned long> {
        static const bool value = true;
    };

    template<>
    struct is_integral<unsigned long long> {
        static const bool value = true;
    };

    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };
}
