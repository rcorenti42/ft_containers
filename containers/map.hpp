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
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key,T> > >
    class map {
        Compare                                         _comp;
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef size_t size_type;
		typedef Compare key_compare;
        typedef Allocator allocator_type;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		class value_compare {
			Compare comp;
		public:
			value_compare(Compare c): comp(c) {
            };
			bool    operator()(const value_type& lhs, const value_type& rhs) const {
				return comp(lhs.first, rhs.first);
			};
		};
        typedef typename rb_tree<value_type, value_compare, Allocator>::iterator iterator;
		typedef typename rb_tree<value_type, value_compare, Allocator>::const_iterator const_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
        typedef	ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		explicit map (const Compare& comp = Compare(), const Allocator& alloc = Allocator()): _comp(comp), tree(comp, alloc) {
        };
		template <class InputIt>
		map (InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()): _comp(comp), tree(comp, alloc) {
		    insert(first, last);
		};
		map (const map& other): _comp(other._comp), tree(other.tree) {
        };
		map&                                            operator=(const map& other) {
			this->_comp = other._comp;
			this->tree = other.tree;
			return *this;
		}
		allocator_type                                  get_allocator() const {
            return allocator_type(this->tree.allocator);
        };
        T&                                              at(const Key& key) {
            iterator    it = find(key);
            if (it == end())
                throw std::out_of_range("map::at");
            return it->second;
        };
        const T&                                        at(const Key& key) const {
            const_iterator  it = find(key);
            if (it == end())
                throw std::out_of_range("map::at");
            return it->second;
        };
		T&                                              operator[](const Key& key) {
			return insert(pair<key_type, mapped_type>(key, T())).first->second;
		}
		iterator                                        begin() {
            return this->tree.begin();
        }
		const_iterator                                  begin() const {
            return this->tree.begin();
        }
		iterator                                        end() {
            return this->tree.end();
        }
		const_iterator                                  end() const{
            return this->tree.end();
        }
		reverse_iterator                                rbegin() {
            return reverse_iterator(this->end());
        }
		const_reverse_iterator                          rbegin() const {
            return const_reverse_iterator(this->end());
        }
		reverse_iterator                                rend() {
            return reverse_iterator(this->begin());
        }
		const_reverse_iterator                          rend() const{
            return const_reverse_iterator(this->begin());
        }
		bool                                            empty() const {
            return !this->tree.size;
        }
		size_type                                       size() const {
            return this->tree.size;
        }
		size_type                                       max_size() const {
            return this->tree.allocator.max_size();
        }
		void                                            clear() {
			this->tree.clear();
		};
		pair<iterator, bool>                            insert(const value_type& value) {
			return this->tree.insert(value);
		}
		iterator					                    insert(iterator hint, const value_type& value) {
			return this->tree.insert(hint, value).first;
		}
		template<class InputIt>
		void						                    insert(InputIt first, InputIt last) {
            for (iterator it = begin(); first != last; first++)
                it = insert(it, *first);
		}
		void                                            erase(iterator pos) {
			this->tree.erase(pos);
		}
		void                                            erase(iterator first, iterator last) {
            iterator    it;
			while (first != last)
			{
				it = first++;
				erase(it);
			}
		}
		size_type                                       erase(const Key& key) {
			iterator    it = this->tree.find(pair<key_type, mapped_type>(key, mapped_type()));
			if (it == end())
				return 0;
			erase(it);
			return 1;
		}
		void                                            swap(map& other) {
			this->tree.swap(other.tree);
		};
		size_type                                       count(const Key& key) const {
			return this->tree.find(pair<key_type, mapped_type>(key, mapped_type())) != this->end();
		}
		iterator                                        find(const Key& key) {
			return this->tree.find(pair<key_type, mapped_type>(key, mapped_type()));
		}
		const_iterator                                  find(const Key& key) const {
			return this->tree.find(pair<key_type, mapped_type>(key, mapped_type()));
		}
		pair<iterator, iterator>                        equal_range(const Key& key) {
			return pair<iterator, iterator>(this->tree.lower_bound(pair<key_type, mapped_type>(key, mapped_type())), this->tree.upper_bound(pair<key_type, mapped_type>(key, mapped_type())));
		}
		pair<const_iterator, const_iterator>            equal_range(const Key& key) const {
			return pair<const_iterator,const_iterator>(const_iterator(this->tree.lower_bound(pair<key_type, mapped_type>(key, mapped_type()))), const_iterator(this->tree.upper_bound(pair<key_type, mapped_type>(key, mapped_type()))));
		}
		iterator                                        lower_bound(const Key& key) {
			return this->tree.lower_bound(pair<key_type, mapped_type>(key, mapped_type()));
		}
		const_iterator                                  lower_bound(const Key& key) const {
			return const_iterator(this->tree.lower_bound(pair<key_type, mapped_type>(key, mapped_type())));
		}
		iterator                                        upper_bound(const Key& key) {
			return this->tree.upper_bound(pair<key_type, mapped_type>(key, mapped_type()));
		}
		const_iterator                                  upper_bound(const Key& key) const {
			return const_iterator(this->tree.upper_bound(pair<key_type, mapped_type>(key, mapped_type())));
		}
		key_compare                                     key_comp() const {
			return _comp;
		}
		value_compare                                   value_comp() const {
			return this->tree.comp;
		};
    private:
		rb_tree<value_type, value_compare, Allocator>    tree;
	};
    template <class Key, class T, class Compare, class Alloc>
    bool    operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
        return lhs.size() == rhs.size() && ft::equal<typename map<Key, T, Compare, Alloc>::const_iterator, typename map<Key, T, Compare, Alloc>::const_iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template <class Key, class T, class Compare, class Alloc>
    bool    operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return !(lhs == rhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool    operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return ft::lexicographical_compare<typename map<Key, T, Compare, Alloc>::const_iterator, typename map<Key, T, Compare, Alloc>::const_iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template <class Key, class T, class Compare, class Alloc>
    bool    operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return !(rhs < lhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool    operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return rhs < lhs;
    }
    template <class Key, class T, class Compare, class Alloc>
    bool    operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return !(lhs < rhs);
    }
	template <typename iter1, typename iter2>
	bool    operator==(iter1 lhs, iter2 rhs) {
        return &*lhs == &*rhs;
    }
	template <typename iter1, typename iter2>
	bool    operator!=(iter1 lhs, iter2 rhs) {
        return !(&*lhs == &*rhs);
    }
	template<class Key, class T, class Compare, class Alloc>
	void    swap(map<Key, T, Compare, Alloc> &lhs, map<Key, T, Compare, Alloc> &rhs) {
		lhs.swap(rhs);
	}
};

#endif