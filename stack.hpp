#pragma once
#include <iostream>
#include "vector.hpp"

namespace ft{
    template <class T, class Container = ft::vector<T> >
    class stack {
    public:
        typedef T   value_type;
        typedef Container   container_type;
        typedef typename container_type::size_type  size_type;
        explicit stack (const container_type& ctnr = container_type()) : _container(ctnr) {}
        size_type size() const{
            return (_container.size());
        }
        value_type& top(){
            return (_container.back());
        }
        bool empty() const {
            return _container.empty();
        }
        const value_type& top() const{
            return (_container.back());
        }
        void push (const value_type& val){
            _container.push_back(val);
        }
        void pop(){
            _container.pop_back();
        }
    private:
        container_type _container;

        template <class T1, class ContainerType>
        friend bool operator== (const stack<T1,ContainerType>& lhs, const stack<T1,ContainerType>& rhs);

        template <class T1, class ContainerType>
        friend  bool operator!= (const stack<T1,ContainerType>& lhs, const stack<T1,ContainerType>& rhs);

        template <class T1, class ContainerType>
        friend bool operator<  (const stack<T1,ContainerType>& lhs, const stack<T1,ContainerType>& rhs);

        template <class T1, class ContainerType>
        friend bool operator<= (const stack<T1,ContainerType>& lhs, const stack<T1,ContainerType>& rhs);

        template <class T1, class ContainerType>
        friend bool operator>  (const stack<T1,ContainerType>& lhs, const stack<T1,ContainerType>& rhs);

        template <class T1, class ContainerType>
        friend bool operator>= (const stack<T1,ContainerType>& lhs, const stack<T1,ContainerType>& rhs);

    };

    template <class T, class Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs._container == rhs._container;
    }
    template <class T, class Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs._container != rhs._container;
    }
    template <class T, class Container>
    bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs._container < rhs._container;
    }
    template <class T, class Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs._container <= rhs._container;
    }
    template <class T, class Container>
    bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs._container > rhs._container;
    }
    template <class T, class Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs._container >= rhs._container;
    }

}
