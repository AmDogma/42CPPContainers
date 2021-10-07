#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <sys/types.h>
#include <iostream>

namespace ft {
    template<class T, class Allocator = std::allocator<T> >
    class Vector {
    private:
        std::size_t v_size;
        size_t v_capacity;
        T *v_data;
    public:

        /* Member functions */

        Vector() : v_data(nullptr), v_size(0), v_capacity(0) {
            ReAlloc(2);
        }

        ~Vector() {
            delete[] v_data; // maybe need to call destructor for each element
        }

        T &operator=(T const &other) {
            v_capacity = other.capacity();
            ReAlloc(v_capacity);
            v_size = other.size();
            for (size_t i = 0; i < v_size; i++)
                v_data[i] = other[i];
            // need to check!
        }

        /* Iterators */

        //
        //

        /* Capacity */

        size_t size() {
            return (v_size);
        }

//    size_t max_size() {
//        return(v_size.max_size());
//    }

        size_t capacity() {
            return (v_capacity);
        }


        T &operator[](size_t index) {
            if (index < v_size)
                return (v_data[index]); // some else option, exception case maybe
        }

        const T &operator[](size_t index) const {
            if (index < v_size)
                return (v_data[index]); // some else option, exception case maybe
        }

        void push_back(T newElement) {
            if (v_size == v_capacity)
                ReAlloc(v_capacity * 2);
            v_data[v_size] = newElement;
            v_size++;
        }

    private:
        void ReAlloc(size_t newCapacity) {
            T *newData = new T[newCapacity];
            if (v_size > newCapacity) // do we need decreasing?
                v_size = newCapacity;
            for (size_t i = 0; i < v_size; i++)
                newData[i] = v_data[i];
            if (v_data)
                delete[] v_data;
            v_data = newData;
            v_capacity = newCapacity;
        }
    };
}

#endif
