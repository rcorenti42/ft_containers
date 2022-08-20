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
# include "algorithm.hpp"
# include <utility>
# include <stdexcept>

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
           typedef vector_iterator<T, false> iterator;
           typedef vector_iterator<T, true> const_iterator;
           typedef ft::reverse_iterator<iterator> reverse_iterator;
           typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
           typedef ptrdiff_t difference_type;
           typedef size_t size_type;
           explicit vector(const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _capacity(0), _data(_alloc.allocate(0)) {
           }
           explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(n), _capacity(n), _data(_alloc.allocate(n)) {
               this->_data = this->_alloc.allocate(this->_capacity);
				for (size_type i = 0; i < n; i++)
                   this->_alloc.construct(&this->_data[i], val);
           }
           template <typename InputIterator>
           vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value >::type* = 0): _alloc(alloc), _size(0), _capacity(0), _data(_alloc.allocate(0)) {
               size_type n = 0;
				for (InputIterator it = first; it != last && n < this->max_size(); it++)
					n++;
				this->_capacity = n;
				this->_data = this->_alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					this->_alloc.construct(&this->_data[i], *first++);
				this->_size = n;
           }
           vector(const vector& x): _alloc(x._alloc), _size(x._size), _capacity(x._capacity), _data(_alloc.allocate(x._capacity)) {
               for (size_type i = 0; i < _size; i++)
                   this->_alloc.construct(&this->_data[i], x[i]);
           }
           ~vector() {
               for (size_type i = 0; i < this->_size; i++)
                   this->_alloc.destroy(&this->_data[i]);
               this->_alloc.deallocate(this->_data, this->_capacity);
           }
           vector&                 operator=(const vector& x) {
               if (this != &x) {
                   for (size_type i = 0; i < this->_size; i++)
                       this->_alloc.destroy(&this->_data[i]);
                   this->_alloc.deallocate(this->_data, this->_capacity);
                   this->_size = x._size;
                   this->_capacity = x._capacity;
                   this->_data = this->_alloc.allocate(this->_capacity);
                   for (size_type i = 0; i < this->_size; i++)
                       this->_alloc.construct(&this->_data[i], x._data[i]);
               }
               return *this;
           }
           iterator                begin() {
               return iterator(this->_data);
           }
           const_iterator          begin() const {
               return const_iterator(this->_data);
           }
           iterator                end() {
               return iterator(&this->_data[this->_size]);
           }
           const_iterator          end() const {
               return const_iterator(&this->_data[this->_size]);
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
               return const_iterator(this->_data);
           }
           const_iterator          cend() const {
               return const_iterator(&this->_data[this->_size]);
           }
           const_reverse_iterator  crbegin() const {
               return const_reverse_iterator(end());
           }
           const_reverse_iterator  crend() const {
               return const_reverse_iterator(begin());
           }
           size_type               size() const {
               return this->_size;
           }
           size_type               max_size() const {
               return this->_alloc.max_size();
           }
           void                    resize(size_type n, value_type val = value_type()) {
               reserve(n);
               while (n < this->_size)
                   pop_back();
               while (n > this->_size)
                   push_back(val);
           }
           size_type               capacity() const {
               return this->_capacity;
           }
           bool                    empty() const {
               return this->_size == 0;
           }
           void                    reserve(size_type n) {
               if (n > max_size())
                   throw std::length_error("ft::vector::reserve");
               if (n > this->_capacity) {
                   pointer tmp = this->_alloc.allocate(n);
				    this->_capacity = n;
                   for (size_type i = 0; i < this->_size; i++)
                       this->_alloc.construct(&tmp[i], this->_data[i]);
                   for (size_type i = 0; i < this->_size; i++)
                       this->_alloc.destroy(&this->_data[i]);
                   this->_alloc.deallocate(this->_data, this->_capacity);
                   this->_data = tmp;
               }
           }
           reference               operator[](size_type n) {
               return this->_data[n];
           }
           const_reference         operator[](size_type n) const {
               return this->_data[n];
           }
           reference               at(size_type n) {
               if (n >= _size)
                   throw std::out_of_range("ft::vector::at");
               return this->_data[n];
           }
           const_reference         at(size_type n) const {
               if (n >= this->_size)
                   throw std::out_of_range("ft::vector::at");
               return this->_data[n];
           }
           reference               front() {
               return this->_data[0];
           }
           const_reference         front() const {
               return this->_data[0];
           }
           reference               back() {
               return this->_data[this->_size - 1];
           }
           const_reference         back() const {
               return this->_data[this->_size - 1];
           }
           value_type              *data() {
               return this->_data;
           }
           const value_type        *data() const {
               return this->_data;
           }
           template <typename InputIterator>
           void                    assign(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0) {
               clear();
				size_type n = 0;
				for (InputIterator it = first; it != last; it++)
					n++;
				if (n > this->_capacity) {
					reserve(n);
					this->_size = this->_capacity;
					for (size_type i = 0; first != last; first++, i++)
						this->_alloc.construct(&this->_data[i], *first);
					return;
				}
				while (first != last)
					push_back(*first++);
           }
           void                    assign(size_type n, const value_type& val) {
               clear();
				if (n > this->_capacity) {
					reserve(n);
					this->_size = this->_capacity;
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.construct(&this->_data[i], val);
					return;
				}
				for (size_type i = 0; i < n; i++)
					push_back(val);
           }
           void                    push_back(const value_type& val) {
               if (this->_size >= this->_capacity)
                   reserve(this->_capacity == 0 ? 1 : this->_capacity * 2);
               this->_alloc.construct(&this->_data[this->_size++], val);
           }
           void                    pop_back() {
               if (this->_size == 0)
                   throw std::out_of_range("ft::vector::pop_back");
               this->_alloc.destroy(&this->_data[this->_size - 1]);
               this->_size--;
           }
           iterator                insert(iterator pos, const value_type& val) {
               pointer tmp;
               if (this->_size + 1 > this->_capacity * 2 || this->_capacity == 0)
                   tmp = this->_alloc.allocate(this->_size + 1);
               else if ((this->_size + 1) > this->_capacity && this->_capacity > 0)
                   tmp = this->_alloc.allocate(this->_size * 2);
               else
                   tmp = this->_alloc.allocate(this->_capacity);
               size_type i = 0;
               size_type j = 0;
               for (iterator it = begin(); it != end(); it++) {
                   if (it == pos) {
                       j = i;
                       this->_alloc.construct(&tmp[i++], val);
                   }
                   this->_alloc.construct(&tmp[i++], *it);
               }
               if (pos == end()) {
                   j = i;
                   this->_alloc.construct(&tmp[i++], val);
               }
               for (size_type k = 0; k < this->_size; k++)
                   this->_alloc.destroy(&this->_data[k]);
               this->_alloc.deallocate(this->_data, this->_capacity);
               this->_data = tmp;
               if (this->_size + 1 > this->_capacity * 2 || this->_capacity == 0)
                   this->_capacity = this->_size + 1;
               else if ((this->_size + 1) > this->_capacity && this->_capacity > 0)
                   this->_capacity = this->_size * 2;
               _size = i;
               return &tmp[j];
           }
           void                    insert(iterator pos, size_type n, const value_type& val) {
                   pointer tmp;
                   if (this->_size + n > this->_capacity * 2 || this->_capacity == 0)
                       tmp = this->_alloc.allocate(this->_size + n);
                   else if ((this->_size + n) > this->_capacity && this->_capacity > 0)
                       tmp = this->_alloc.allocate(this->_size * 2);
                   else
                       tmp = this->_alloc.allocate(this->_capacity);
                   size_type i = 0;
                   for (iterator it = begin(); it != end(); it++) {
                       if (it == pos)
                           for (size_type j = 0; j < n; j++)
                               this->_alloc.construct(&tmp[i++], val);
                       this->_alloc.construct(&tmp[i++], *it);
                   }
                   if (pos == end())
                       for (size_type j = 0; j < n; j++)
                           this->_alloc.construct(&tmp[i++], val);
                   for (size_type j = 0; j < this->_size; j++)
                       this->_alloc.destroy(&this->_data[j]);
                   this->_alloc.deallocate(this->_data, this->_capacity);
                   if (this->_size + n > this->_capacity * 2 || this->_capacity == 0)
                       this->_capacity = this->_size + n;
                   else if ((this->_size + n) > this->_capacity && this->_capacity > 0)
                       this->_capacity = this->_size * 2;
                   this->_size = i;
                   this->_data = tmp;
           }
           template <typename InputIterator>
           void                    insert(iterator pos, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value >::type* = 0) {
               pointer tmp;
               size_type n = 0;
               for (InputIterator it = first; it != last; it++)
                   n++;
               if ((this->_size + n) > this->_capacity * 2 || this->_capacity == 0)
                   tmp = this->_alloc.allocate(this->_size + n);
               else if ((this->_size + n) > this->_capacity && this->_capacity > 0)
                   tmp = this->_alloc.allocate(this->_size * 2);
               else
                   tmp = this->_alloc.allocate(this->_capacity);
               size_type i = 0;
               for (iterator it = begin(); it != end(); it++) {
                   if (it == pos)
                       for (InputIterator it2 = first; it2 != last; it2++)
                           this->_alloc.construct(&tmp[i++], *it2);
                   this->_alloc.construct(&tmp[i++], *it);
               }
               if (pos == end())
                   for (InputIterator it = first; it != last; it++)
                       this->_alloc.construct(&tmp[i++], *it);
               for (size_type i = 0; i < this->_size; i++)
                   this->_alloc.destroy(&this->_data[i]);
               this->_alloc.deallocate(this->_data, this->_capacity);
               if ((this->_size + n) > this->_capacity * 2 || this->_capacity == 0)
                   this->_capacity = this->_size + n;
               else if ((this->_size + n) > this->_capacity && this->_capacity > 0)
                   this->_capacity = this->_size * 2;
               this->_size = i;
               this->_data = tmp;
           }
           iterator                erase(iterator pos) {
               iterator it = pos;
               for (; it + 1 != end(); it++)
					*it = *(it + 1);
				this->_alloc.destroy(&this->_data[this->_size - 1]);
				this->_size--;
				return pos;
           }
           iterator                erase(iterator first, iterator last) {
               while (first != last) {
					erase(first);
					last--;
				}
				return first;
           }
           void                   swap(vector& x) {
               ft::swap(this->_size, x._size);
               ft::swap(this->_capacity, x._capacity);
               ft::swap(this->_data, x._data);
               ft::swap(this->_alloc, x._alloc);
           }
           void                    clear() {
               for (size_type i = 0; i < this->_size; i++)
                   this->_alloc.destroy(&this->_data[i]);
               this->_size = 0;
           }
           allocator_type          get_allocator() const {
               return this->_alloc;
           }
       protected:
           allocator_type  _alloc;
           size_type       _size;
           size_type       _capacity;
           pointer         _data;
    };
    template <typename T, typename Alloc>
    bool                            operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
       if (lhs.size() != rhs.size())
           return false;
		const T* lhs_data = lhs.data();
		const T* rhs_data = rhs.data();
       for (size_t i = 0; i < lhs.size(); i++)
           if (lhs_data[i] != rhs_data[i])
               return false;
       return true;
    };
    template <typename T, typename Alloc>
    bool                            operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
       return !(lhs == rhs);
    };
    template <typename T, typename Alloc>
    bool                            operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
       for (typename Alloc::size_type i = 0; i < std::min(lhs.size(), rhs.size()); i++)
           if (lhs[i] != rhs[i])
               return lhs[i] < rhs[i];
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