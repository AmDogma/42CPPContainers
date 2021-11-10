#pragma once
#include <iostream>
#include <vector> // need to delete after change to ft::vector
#include "vector.hpp"

namespace ft{
    template <class T, class Container = std::vector<T> > // need to delete after change to ft::vector
    class stack {
        typedef T                value_type;
        typedef Container    container_type; //
        typedef std::size_t       size_type;
    public:
        explicit stack (const container_type& ctnr = container_type()) : container() {}
        size_type size() const{
            return (container.size());
        }
        value_type& top(){
            return (container.back());
        }
        const value_type& top() const{
            return (container.back());
        }
        void push (const value_type& val){
            container.push_back(val);
        }
        void pop(){
            container.pop_back();
        }
    private:
        container_type container;
    };
}
