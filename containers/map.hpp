/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/08/20 02:43:25               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   map.hpp                                                                  */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include <stdexcept>
# include <cstddef>
# include "ft_iterator.hpp"
# include "utility.hpp"
# include "type_traits.hpp"
# include "algorithm.hpp"
# include "rb_tree.hpp" 


namespace ft {
    template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
    class map {
        public:
            typedef pair<const Key, T> value_type;
            class value_compare {
                public:
                    value_compare(Compare comp) : comp(comp) {
                    }
                    bool    operator()(const value_type& lhs, const value_type& rhs) const {
                        return comp(lhs.first, rhs.first);
                    }
                protected:
                    Compare comp;
            };
            typedef Key key_type;
            typedef T mapped_type;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef Compare key_compare;
            typedef Allocator allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef typename rb_tree<value_type, value_compare, Allocator>::iterator iterator;
            typedef typename rb_tree<value_type, value_compare, Allocator>::const_iterator const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
            explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : _comp(comp), _root(comp, alloc) {
            }
            template <class InputIt>
            map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : _comp(comp), _root(comp, alloc) {
                insert(first, last);
            }
            map(const map& other): _comp(other._comp), _root(other._root) {
            }
            map&                                            operator=(const map& other) {
                this->_comp = other._comp;
                this->_root = other._root;
                return *this;
            }
            allocator_type                                  get_allocator() const {
                return allocator_type();
            }
            T&                                              at(const Key& key) {
                iterator it = find(key);
                if (it == end())
                    throw std::out_of_range("ft::map::at");
                return it->second;
            }
            const T&                                        at(const Key& key) const {
                const_iterator it = find(key);
                if (it == end())
                    throw std::out_of_range("ft::map::at");
                return it->second;
            }
            T&                                              operator[](const Key& key) {
                return insert(pair<key_type, mapped_type>(key, mapped_type())).first->second;
            }
            iterator                                        begin() {
                return this->_root.begin();
            }
            const_iterator                                  begin() const {
                return this->_root.begin();
            }
            iterator                                        end() {
                return this->_root.end();
            }
            const_iterator                                  end() const {
                return this->_root.end();
            }
            reverse_iterator                                rbegin() {
                return reverse_iterator(end());
            }
            const_reverse_iterator                          rbegin() const {
                return const_reverse_iterator(end());
            }
            reverse_iterator                                rend() {
                return reverse_iterator(begin());
            }
            const_reverse_iterator                          rend() const {
                return const_reverse_iterator(begin());
            }
            bool                                            empty() const {
                return !this->_root.size;
            }
            size_type                                       size() const {
                return this->_root.size;
            }
            size_type                                       max_size() const {
                return this->_root.alloc.max_size();
            }
            void                        clear() {
                this->_root.clear_all();
            }
            pair<iterator, bool>                            insert(const value_type& value) {
                return this->_root.insert(value);
            }
            iterator                                        insert(iterator hint, const value_type& value) {
                return this->_root.insert(hint, value).first;
            }
            template <class InputIt>
            void                                            insert(InputIt first, InputIt last) {
                for (iterator it = begin(); first != last; first++)
                    it = insert(it, *first);
            }
            void                                            erase(iterator pos) {
                this->_root.clear_tree(pos);
            }
            void                                            erase(iterator first, iterator last) {
                for (iterator it; first != last; it = first++) {
                    erase(it);
                }
            }
            size_type                                       erase(const Key& key) {
                iterator it = this->_root.find(ft::pair<key_type, mapped_type>(key, mapped_type()));
                if (it == end())
                    return 0;
                erase(it);
                return 1;
            }
            void                                            swap(map& other) {
                this->_root.swap(other._root);
            }
            size_type                                       count(const Key& key) const {
                return this->_root.find(ft::pair<key_type, mapped_type>(key, mapped_type())) != end();
            }
            iterator                                        find(const Key& key) {
                return this->_root.find(pair<key_type, mapped_type>(key, mapped_type()));
            }
            const_iterator                                  find(const Key& key) const {
                return this->_root.find(pair<key_type, mapped_type>(key, mapped_type()));
            }
            iterator                                        lower_bound(const Key& key) {
                return this->_root.lower_bound(pair<key_type, mapped_type>(key, mapped_type()));
            }
            const_iterator                                  lower_bound(const Key& key) const {
                return const_iterator(this->_root.lower_bound(pair<key_type, mapped_type>(key, mapped_type())));
            }  
            iterator                                        upper_bound(const Key& key) {
                return this->_root.upper_bound(pair<key_type, mapped_type>(key, mapped_type()));
            }
            const_iterator                                  upper_bound(const Key& key) const {
                return const_iterator(this->_root.upper_bound(pair<key_type, mapped_type>(key, mapped_type())));
            }
            pair<iterator, iterator>                        equal_range(const Key& key) {
                return pair<iterator, iterator>(this->_root.lower_bound(pair<key_type, mapped_type>(key, mapped_type())), this->_root.upper_bound(pair<key_type, mapped_type>(key, mapped_type())));
            }
            pair<const_iterator, const_iterator>            equal_range(const Key& key) const {
                return pair<const_iterator, const_iterator>(const_iterator(this->_root.lower_bound(pair<key_type, mapped_type>(key, mapped_type()))), const_iterator(this->_root.upper_bound(pair<key_type, mapped_type>(key, mapped_type()))));
            }
            key_compare                                     key_comp() const {
                return this->_comp;
            }
            value_compare                                   value_comp() const {
                return this->_root.comp;
            }
            friend bool                                     operator==(const map& lhs, const map& rhs) {
                return lhs.size() == rhs.size() && ft::equal<const_iterator, const_iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
            }
            friend bool                                     operator!=(const map& lhs, const map& rhs) {
                return !(lhs == rhs);
            }
            friend bool                                     operator<(const map& lhs, const map& rhs) {
                return ft::lexicographical_compare<const_iterator, const_iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
            }
            friend bool                                     operator<=(const map& lhs, const map& rhs) {
                return !(rhs < lhs);
            }
            friend bool                                     operator>(const map& lhs, const map& rhs) {
                return rhs < lhs;
            }
            friend bool                                     operator>=(const map& lhs, const map& rhs) {
                return !(lhs < rhs);
            }
        private:
            key_compare                                     _comp;
            rb_tree<value_type, value_compare, Allocator>   _root;
    };
    template <class Iter1, class Iter2>
    bool    operator==(Iter1 lhs, Iter2 rhs) {
        return &*lhs == &*rhs;
    }
    template <class Iter1, class Iter2>
    bool    operator!=(Iter1 lhs, Iter2 rhs) {
        return !(&*lhs == &*rhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    void    swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs) {
        lhs.swap(rhs);
    };
};

#endif