/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/07/23 12:55:07               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   vector.hpp                                                               */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "ft_iterator.hpp"
# include "type_traits.hpp"

namespace ft {
    template <typename T, typename Alloc = std::allocator<T> >
    class vector {
        public:
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef vector_iterator<pointer> iterator;
            typedef vector_iterator<const pointer> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef typename allocator_type::difference_type difference_type;
            typedef typename allocator_type::size_type size_type;
            explicit vector(const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _capacity(0), _data(alloc.allocate(0)) {
            }
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(n), _capacity(n), _data(_alloc.allocate(n)) {
                for (size_type i = 0; i < n; ++i)
                    _alloc.construct(_data + i, val);
            }
            template <typename InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0): _alloc(alloc), _size(0), _capacity(0), _data(alloc.allocate(0)) {
                for (; first != last; ++first)
                    push_back(*first);
            }
            vector(const vector& x): _alloc(x._alloc), _size(x._size), _capacity(x._capacity), _data(x._data) {
                for (size_type i = 0; i < _size; ++i)
                    _alloc.construct(&_data[i], x._data[i]);
            }
            ~vector() {
                for (size_type i = 0; i < _size; ++i)
                    _alloc.destroy(&_data[i]);
                _alloc.deallocate(_data, _capacity);
            }
            iterator                begin() {
                return iterator(_data);
            }
            const_iterator          begin() const {
                return const_iterator(_data);
            }
            iterator                end() {
                return iterator(_data + _size);
            }
            const_iterator          end() const {
                return const_iterator(_data + _size);
            }
            reverse_iterator        rbegin() {
                return reverse_iterator(end());
            }
            const_reverse_iterator  rbegin() const {
                return const_reverse_iterator(end());
            }
            reverse_iterator        rend() {
                return reverse_iterator(begin());
            }
            const_reverse_iterator  rend() const {
                return const_reverse_iterator(begin());
            }
            const_iterator          cbegin() const {
                return const_iterator(_data);
            }
            const_iterator          cend() const {
                return const_iterator(_data + _size);
            }
            const_reverse_iterator  crbegin() const {
                return const_reverse_iterator(end());
            }
            const_reverse_iterator  crend() const {
                return const_reverse_iterator(begin());
            }
            size_type               size() const {
                return _size;
            }
            size_type               max_size() const {
                return _alloc.max_size();
            }
            size_type               capacity() const {
                return _capacity;
            }
            bool                    empty() const {
                return _size == 0;
            }
            void                    reserve(size_type n) {
                if (n > max_size())
                    throw std::length_error("ft::vector::reserve");
                if (n > capacity()) {
                    pointer tmp = _alloc.allocate(n);
                    for (size_type i = 0; i < _size; ++i)
                        _alloc.construct(&tmp[i], _data[i]);
                    for (size_type i = 0; i < _size; ++i)
                        _alloc.destroy(&_data[i]);
                    _alloc.deallocate(_data, _capacity);
                    _data = tmp;
                    _capacity = n;
                }
            }
            reference               operator[](size_type n) {
                return _data[n];
            }
            const_reference         operator[](size_type n) const {
                return _data[n];
            }
            reference               at(size_type n) {
                if (n >= _size)
                    throw std::out_of_range("ft::vector::at");
                return _data[n];
            }
            const_reference         at(size_type n) const {
                if (n >= _size)
                    throw std::out_of_range("ft::vector::at");
                return _data[n];
            }
            reference               front() {
                return _data[0];
            }
            const_reference         front() const {
                return _data[0];
            }
            reference               back() {
                return _data[_size - 1];
            }
            const_reference         back() const {
                return _data[_size - 1];
            }
            value_type             *data() {
                return _data;
            }
            template <typename InputIterator>
            void                    assign(InputIterator first, InputIterator last) {
                for (; first != last; ++first)
                    push_back(*first);
            }
            void                    assign(size_type n, const value_type& val) {
                for (size_type i = 0; i < n; ++i)
                    push_back(val);
            }
            void                    push_back(const value_type& val) {
                if (_size == _capacity)
                    reserve(_capacity == 0 ? 1 : _capacity * 2);
                _alloc.construct(&_data[_size], val);
                ++_size;
            }
            void                    pop_back() {
                if (_size == 0)
                    throw std::out_of_range("ft::vector::pop_back");
                _alloc.destroy(&_data[_size - 1]);
                --_size;
            }
            iterator                insert(iterator pos, const value_type& val) {
                if (_size == _capacity)
                    reserve(_capacity == 0 ? 1 : _capacity * 2);
                for (size_type i = _size; i > pos - _data; --i)
                    _alloc.construct(&_data[i], _data[i - 1]);
                _alloc.construct(&_data[pos - _data], val);
                ++_size;
                return pos;
            }
            iterator                erase(iterator pos) {
                for (size_type i = pos - _data; i < _size - 1; ++i)
                    _alloc.construct(&_data[i], _data[i + 1]);
                _alloc.destroy(&_data[_size - 1]);
                --_size;
                return pos;
            }
            void                   swap(vector& x) {
                std::swap(_size, x._size);
                std::swap(_capacity, x._capacity);
                std::swap(_data, x._data);
                std::swap(_alloc, x._alloc);
            }
            void                    clear() {
                for (size_type i = 0; i < _size; ++i)
                    _alloc.destroy(&_data[i]);
                _size = 0;
            }
            allocator_type          get_allocator() const {
                return _alloc;
            }
        protected:
            allocator_type  _alloc;
            size_type       _size;
            pointer         _data;
            size_type       _capacity;
    };
    template <typename T, typename Alloc>
    bool                            operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        if (lhs.size() != rhs.size())
            return false;
        for (typename Alloc::size_type i = 0; i < lhs.size(); ++i)
            if (lhs[i] != rhs[i])
                return false;
        return true;
    };
    template <typename T, typename Alloc>
    bool                            operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(lhs == rhs);
    };
    template <typename T, typename Alloc>
    bool                            operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        for (typename Alloc::size_type i = 0; i < std::min(lhs.size(), rhs.size()); ++i)
            if (lhs[i] < rhs[i])
                return true;
            else if (lhs[i] > rhs[i])
                return false;
        return lhs.size() < rhs.size();
    };
    template <typename T, typename Alloc>
    bool                            operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(rhs < lhs);
    };
    template <typename T, typename Alloc>
    bool                            operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return rhs < lhs;
    };
    template <typename T, typename Alloc>
    bool                            operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(lhs < rhs);
    };
    template <typename T, typename Alloc>
    void                            swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
        x.swap(y);
    };
}

#endif