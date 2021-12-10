#pragma once
#include "iterator_traits.hpp"

namespace ft {

    template<class T> struct remove_const { typedef T type; };

    template<class T> struct remove_const <const T> { typedef T type; };

    template<class T, bool v>
    struct integral_constant {
        static const bool value = v;
        typedef T value_type;
        typedef integral_constant type;
        operator value_type() const { return value; }
    };

    template <class T> struct is_integral				: public ft::integral_constant<T, false> {};
    template <> struct is_integral<bool>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<char>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<signed char>			: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned char>		: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<wchar_t>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<char16_t>			: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<short>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned short>		: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<int>					: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned int>		: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<long>				: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long> 		: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<long long>			: public ft::integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long long>	: public ft::integral_constant<bool, true> {};

    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };

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

    template<class InputIt1, class InputIt2>
    bool equal( InputIt1 first1, InputIt1 last1,
                InputIt2 first2 )
    {
        for(; first1 != last1; ++first1, ++first2) {
            if(!(*first1 == *first2)) {
                return false;
            }
        }
        return true;
    }

    template<class InputIt1, class InputIt2, class BinaryPredicate>
    bool equal( InputIt1 first1, InputIt1 last1,
                InputIt2 first2, BinaryPredicate p )
    {
        for(; first1 != last1; ++first1, ++first2) {
            if(!p( *first1, *first2 )) {
                return false;
            }
        }
        return true;
    }

}