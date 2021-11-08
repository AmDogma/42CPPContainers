#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <sys/types.h>
#include <iostream>
#include <iterator>
#include <vector>

namespace ft {
    template<class T, class Allocator = std::allocator<T> >
    class vector {
    public:
        typedef T   value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::const_pointer const_pointer;
//        typedef ft::vector_iterator<T *>	iterator;
//        typedef ft::vector_iterator<const T *>	const_iterator;
//        typedef ft::reverse_iterator<iterator>	reverse_iterator;
//        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
//        typedef typename iterator_traits<iterator>::difference_type	difference_type;
        typedef size_t	size_type;
    private:
        size_type       _size;
        size_type       _capacity;
        allocator_type	_alloc;
        pointer         _pointer;
    public:
        explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _pointer(NULL), _size(0), _capacity(0) {
        }

        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(n) {
            _pointer = _alloc.allocate(_capacity);
            
        }

        // нужны еще 2 конструкора судя по документации
        // range (3)
        //template <class InputIterator>
        //         vector (InputIterator first, InputIterator last,
        //                 const allocator_type& alloc = allocator_type());
        //copy (4)
        //vector (const vector& x);

        ~vector() {
            delete[] v_data; // maybe need to call destructor for each element
        }

        /* Member functions */

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
