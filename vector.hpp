#pragma once
#include <cstdlib>
#include <algorithm>
#include "iterator.hpp"
#include "utils.hpp"

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
        typedef ft::iterator_vector<T *>	    iterator;
        typedef ft::iterator_vector<const T *>	const_iterator;
        typedef ft::reverse_iterator<iterator>	reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type	difference_type;
        typedef std::size_t	size_type;

    private:
        size_type       _size;
        size_type       _capacity;
        allocator_type	_alloc;
        pointer         _pointer;
    public:
        /* Constructors and destructor */
        explicit vector(const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc), _pointer(0) {
        }

        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc), _pointer(0)  {
            if (n < 0)
                throw std::logic_error("Insert position fail!");
            this->insert(begin(), n, val);
        }

        template <class InputIterator>
                 vector (InputIterator first, InputIterator last,
                         const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value>::type* = 0) : _size(0), _capacity(0), _alloc(alloc), _pointer(0)  {
            this->insert(begin(), first, last);

        }

        /* Operator=  */
        vector& operator= (const vector& x) {
            if (this != &x) {
                clear();
                _alloc.deallocate(_pointer, _capacity);
                _capacity = x.capacity();
                _pointer = _alloc.allocate(_capacity);
                insert(begin(), x.begin(), x.end());
            }
            return *this;
        }

        vector (const vector& x) : _size(0), _capacity(0), _alloc(x._alloc), _pointer(0) {
            insert(begin(), x.begin(), x.end());
        }

        ~vector() {
            clear();
            if (_capacity)
                _alloc.deallocate(_pointer, _capacity);
        }

        /* Iterators */
        iterator begin() {
            return iterator(_pointer);
        }

        iterator end() {
            return iterator(_pointer + _size);
        }

        const_iterator begin() const {
            return const_iterator(_pointer);
        }

        const_iterator end() const {
            return const_iterator(_pointer + _size);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

        /* Getters */
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
                clear();
                insert(begin(), first, last);
            }

        void assign (size_type n, const value_type& val) {
            clear();
            insert(begin(), n, val);
        }

        void reserve(size_type newCapacity) {
            if (newCapacity > max_size() || newCapacity < 0)
                throw std::length_error("Vector capacity error!");
            else if (_capacity < newCapacity) {
                size_type capTwice = _capacity * 2 + (_capacity == 0);
                if (newCapacity < capTwice && capTwice < max_size())
                        newCapacity = capTwice;
                pointer temp = _alloc.allocate(newCapacity);
                for (size_type i = 0; i < _size; i++)
                    _alloc.construct (temp + i, _pointer[i]);
                for (size_type i = 0; i < _size; ++i)
                    _alloc.destroy(_pointer + i);
                _alloc.deallocate(_pointer, _capacity);
                _capacity = newCapacity;
                _pointer = temp;
            }
        }

        void resize (size_type n, value_type val = value_type()) {
            if (n > _size)
                insert(end(), n - _size, val);
            else if (n < _size)
                for (; _size > n; --_size)
                    _alloc.destroy(_pointer + (_size - 1));
        }

        void push_back (const value_type& val) {
            reserve(_size + 1);
            _alloc.construct(_pointer + _size, val);
            _size++;
        }

        void pop_back() {
            if (_size) {
                _size--;
                _alloc.destroy(_pointer + _size);
            }
        }

        iterator insert (iterator position, const value_type& val) {
            size_type dis = static_cast<size_type>(std::distance(begin(), position));
            if (position > end() || position < begin())
                throw std::logic_error("Insert position fail!");
            reserve(_size + 1);
            for (size_type i = 0; _size - i != dis; ++i) {
                _alloc.construct(_pointer + _size - i, _pointer[_size - i - 1]);
                _alloc.destroy(_pointer + _size - i - 1);
            }
            _alloc.construct(_pointer + dis, val);
            _size++;
            return iterator(begin() + dis);
        }

        void insert (iterator position, size_type n, const value_type& val) {
            size_type dis = static_cast<size_type>(std::distance(begin(), position));
            if (position > end() || position < begin())
                throw std::logic_error("Insert position fail!");
            reserve(_size + n);
            for (size_type i = 0; _size - i != dis; ++i) {
                _alloc.construct(_pointer + _size - 1 - i + n, _pointer[_size - i - 1]);
                _alloc.destroy(_pointer + _size - i - 1);
            }
            for (size_type i = 0; i < n; i++) {
                _alloc.construct(_pointer + dis + i, val);
                _size++;
            }
        }

        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0) {
            size_type n = static_cast<size_type>(std::distance(first, last));
            size_type dis = static_cast<size_type>(std::distance(begin(), position));
            if (position > end() || position < begin())
                throw std::logic_error("Insert position fail!");
            pointer temp = _alloc.allocate(n);
            try {
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(temp + i, *first++);
            }
            catch(...) {
                for (size_type i = 0; temp + i != NULL && i < n; i++)
                    _alloc.destroy(temp + i);
                _alloc.deallocate(temp, n);
                throw;
            }
            reserve(_size + n);
            for (size_type i = 0; _size - i != dis; ++i){
                _alloc.construct(_pointer + _size - 1 - i + n, _pointer[_size - i - 1]);
                _alloc.destroy(_pointer + _size - i - 1);
            }
            for (size_type i = 0; i < n; i++) {
                _alloc.construct(_pointer + dis + i, temp[i]);
                _alloc.destroy(temp + i);
                _size++;
            }
            _alloc.deallocate(temp, n);
        }

        iterator erase (iterator position) {
            size_type dis = static_cast<size_type>(std::distance(begin(), position));
            if (_size == 0)
                return end();
            _alloc.destroy(_pointer + dis);
            for (size_type i = 0; dis + i != _size; ++i) {
                _alloc.construct(_pointer + dis + i, _pointer[dis + i + 1]);
                _alloc.destroy(_pointer + dis + i + 1);
            }
            _size--;
            return (begin() + dis);
        }

        iterator erase (iterator first, iterator last) {
            size_type n = static_cast<size_type>(std::distance(first, last));
            size_type dis = static_cast<size_type>(std::distance(begin(), first));
            if (_size == 0)
                return end();
            for (size_type i = 0; i != n; ++i)
                _alloc.destroy(_pointer + dis + i);
            _size -= n;
            for (size_type i = 0; dis + i != _size; ++i) {
                _alloc.construct(_pointer + dis + i, _pointer[dis + i + n]);
                _alloc.destroy(_pointer + dis + i + n);
            }
            return (begin() + dis);
        }

        void clear() {
            for (; _size; --_size)
                _alloc.destroy(_pointer + (_size - 1));
        }

        void swap(vector& other) {
          allocator_type    alloc = _alloc;
          pointer           pointer = _pointer;
          size_type         size = _size;
          size_type         capacity = _capacity;
          _alloc = other._alloc;
          _pointer = other._pointer;
          _size = other._size;
          _capacity = other._capacity;
          other._alloc = alloc;
          other._pointer = pointer;
          other._size = size;
          other._capacity = capacity;
        }
     };

    template< class T, class Alloc >
    void swap( vector<T,Alloc>& lhs,
               vector<T,Alloc>& rhs ) {
        lhs.swap(rhs);
    }

    template< class T, class Alloc >
    bool operator==( const vector<T,Alloc>& lhs,
                     const vector<T,Alloc>& rhs ) {
        return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }

    template< class T, class Alloc >
    bool operator!=( const vector<T,Alloc>& lhs,
                     const vector<T,Alloc>& rhs ) {
        return !(lhs == rhs);
    }

    template< class T, class Alloc >
    bool operator<( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template< class T, class Alloc >
    bool operator<=( const vector<T,Alloc>& lhs,
                     const vector<T,Alloc>& rhs ) {
        return !(lhs > rhs);
    }

    template< class T, class Alloc >
    bool operator>( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
        return rhs < lhs;
    }

    template< class T, class Alloc >
    bool operator>=( const vector<T,Alloc>& lhs,
                     const vector<T,Alloc>& rhs ) {
        return !(lhs < rhs);
    }

}

