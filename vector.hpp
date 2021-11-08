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
        /* Constructors and destructor */
        explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _pointer(NULL), _size(0), _capacity(0) {
        }
//        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n), _pointer(_alloc.allocate(_capacity)) {
//            this->insert(begin(), _capacity, val);
//        }

        // 2 more constr
        // range (3)
        //template <class InputIterator>
        //         vector (InputIterator first, InputIterator last,
        //                 const allocator_type& alloc = allocator_type());
        //copy (4)
        //vector (const vector& x);

        ~vector() {
            clear();
            _alloc.deallocate(_pointer, _capacity);
        }
        /* Operator =  */
        vector& operator= (const vector& x) {
           if (*this == x)
               return *this;
           clear();
           _alloc.deallocate(_pointer, _capacity);
           _capacity = x.capacity();
           _size = x.size();
           _pointer = _alloc.allocate(_capacity);
           for (size_t i = 0; i < _size; i++)
               _pointer[i] = x[i];
           // need to check!
        }
        /* Iterators */
        // ??

        /* Capacity */
        size_type size() const {
           return (_size);
        }
        size_type max_size() const {
           return (_alloc.max_size());
        }
        size_t capacity() const {
          return (_capacity);
        }
        bool        empty () const {
           return (size() == 0);
        }
        /*	Element access	*/
        reference operator[](size_type n) {
           return (*(_pointer + n));
        }
        const_reference operator[](size_type n) const {
           return (*(_pointer + n));
        }
        reference at (size_type n) {
           if (n > _size)
               throw std::out_of_range("N > SIZE");
           return _pointer[n];
        }
        const_reference at (size_type n) const {
           if (n > _size)
               throw std::out_of_range("N > SIZE");
           return _pointer[n];
        }
        reference front () {
           return _pointer[0];
        }
        const_reference front () const {
           return _pointer[0];
        }
        reference back () {
          return _pointer[_size - 1];
        }
        const_reference back () const {
           return _pointer[_size - 1];
        }
        /* Modifiers */
        template <class InputIterator>
            void assign (InputIterator first, InputIterator last) {
//          need to fill
            }
        void assign (size_type n, const value_type& val) {
//          need to fill
        }
        void push_back (const value_type& val) {
//          need to fill
        }
//        iterator insert (iterator position, const value_type& val) {
//            //          need to fill
//        }
//        void insert (iterator position, size_type n, const value_type& val) {
//            //          need to fill
//        }
//        template <class InputIterator>
//            void insert (iterator position, InputIterator first, InputIterator last) {
//            //          need to fill
//            }
        void clear() {
            for (size_type i = 0; i < _size; i++)
                _alloc.destroy(_pointer + i);
            _size = 0;
        }
    private:
        void ReAlloc(size_t newCapacity) {
            T *newData = new T[newCapacity];
            if (_size > newCapacity) // do we need decreasing?
                _size = newCapacity;
            for (size_t i = 0; i < _size; i++)
                newData[i] = _pointer[i];
            if (_pointer)
                delete[] _pointer;
            _pointer = newData;
            _capacity = newCapacity;
        }
    };
}

#endif
