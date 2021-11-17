#pragma once
#include "iterator_traits.hpp"

namespace ft {
    template<class InputIterator>
    typename iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last) { // дополнить на разные версии перегрузки
        typename ft::iterator_traits<InputIterator>::difference_type dis = 0;
        for(; first != last;  first++)
            dis++;
        return dis;
    }
    template <class Iterator>
    typename iterator_traits<Iterator>::iterator_category	iterator_category(Iterator iter) {
        return typename iterator_traits<Iterator>::iterator_category();
    }
}
