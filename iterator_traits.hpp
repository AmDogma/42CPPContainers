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
            typedef random_access_iterator_tag	iterator_category;
        };

    template<class T>
        struct iterator_traits<const T*> {
            typedef ptrdiff_t	difference_type;
            typedef T           value_type;
            typedef const T*    pointer;
            typedef const T&	reference;
            typedef random_access_iterator_tag	iterator_category;
        };

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
