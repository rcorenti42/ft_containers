/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/07/21 18:52:38               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   ft_iterator.hpp                                                          */
/* ************************************************************************** */

#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

# include "type_traits.hpp"
# include "ft_iterator_base_types.hpp"

namespace ft {
    template <class Iterator>
	class reverse_iterator {
	    public:
            typedef Iterator iterator_type;
            typedef random_access_iterator_tag iterator_category;
            typedef typename Iterator::value_type value_type;
            typedef ptrdiff_t difference_type;
            typedef value_type* pointer;
            typedef value_type& reference;
	    	reverse_iterator(): current() {
            }
	    	reverse_iterator(iterator_type x): current(--x) {
            }
            template <class U>
            reverse_iterator(const reverse_iterator<U>& x): current(--x.base()) {
            }
	    	Iterator	base() const {
	    		return ++Iterator(this->current);
	    	}
            template <class U>
	    	reverse_iterator&   operator=(const reverse_iterator<U>& other) {
        		this->current = --other.base();
        		return *this;
	    	}
	    	reference   operator*() const {
        		return *(this->current);
        	}
	    	pointer     operator->() const {
        		return &(operator*());
        	}
	    	value_type& operator[](difference_type n) const {
        		return *(*this + n);
        	}
	    	reverse_iterator&   operator++() {
        		--this->current;
        		return *this;
        	}
	    	reverse_iterator&   operator--() {
        		++this->current;
        		return *this;
        	}
	    	reverse_iterator operator++(int) {
        		reverse_iterator tmp(*this);
        		++*this;
        		return tmp;
        	}
	    	reverse_iterator operator--(int) {
        		reverse_iterator tmp(*this);
        		--*this;
        		return tmp;
        	}
	    	reverse_iterator operator+(difference_type n) const {
	    		return this->current - n + 1;
	    	}
	    	reverse_iterator operator-(difference_type n) const {
	    		return this->current + n + 1;
	    	}
            difference_type operator-(const reverse_iterator& rhs) const {
                return rhs.current - this->current;
	    	}
	    	reverse_iterator&   operator+=(difference_type n) {
        		this->current -= n;
        		return *this;
	    	}
	    	reverse_iterator&  operator-=(difference_type n) {
        		this->current += n;
        		return *this;
	    	}
        protected:
            Iterator   current;
	};
    template <class Iterator1, class Iterator2>
    bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
        return lhs.base() == rhs.base();
    };
    template <class Iterator1, class Iterator2>
    bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
        return lhs.base() != rhs.base();
    };
    template <class Iterator1, class Iterator2>
    bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
        return lhs.base() > rhs.base();
    };
    template <class Iterator1, class Iterator2>
    bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
        return lhs.base() >= rhs.base();
    };
    template <class Iterator1, class Iterator2>
    bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
        return lhs.base() < rhs.base();
    };
    template <class Iterator1, class Iterator2>
    bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
        return lhs.base() <= rhs.base();
    };
    template <class Iter>
    reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it) {
        return it.base() - n;
    }

    template <typename Iterator, bool Constant>
    class   vector_iterator {
        public:
            typedef ptrdiff_t difference_type;
            typedef std::random_access_iterator_tag iterator_category;
			typedef typename conditional<Constant, const Iterator, Iterator>::type value_type;
            typedef value_type* pointer;
            typedef value_type& reference;
            vector_iterator(): current(NULL) {
            }
            vector_iterator(value_type* const it): current(it) {
            }
            template <bool Const>
			vector_iterator(const vector_iterator<Iterator, Const>& it, typename enable_if<!Const>::type* = 0): current(it.base()) {
			}
            value_type*                 base() const {
                return this->current;
            }
            bool                        operator==(value_type* it) const {
                return this->current == it;
            }
            template <bool Const>
            bool                        operator==(const vector_iterator<Iterator, Const>& it) const {
                return this->current == it.base();
            }
            template <bool Const>
            bool                        operator!=(const vector_iterator<Iterator, Const>& it) const {
                return !(*this == it);
            }
            value_type&                 operator*() const {
                return *this->current;
            }
            value_type*                 operator->() const {
                return this->current;
            }
            vector_iterator&            operator=(const vector_iterator& it) {
                this->current = it.base();
                return *this;
            }
            vector_iterator&            operator++() {
                ++this->current;
                return *this;
            }
            vector_iterator             operator++(int) {
                vector_iterator tmp = *this;
                ++this->current;
                return tmp;
            }
            vector_iterator&            operator--() {
                --this->current;
                return *this;
            }
            vector_iterator             operator--(int) {
                vector_iterator tmp = *this;
                --this->current;
                return tmp;
            }
            vector_iterator             operator+(difference_type n) const {
                return vector_iterator(this->current + n);
            }
            vector_iterator             operator-(difference_type n) const {
                return vector_iterator(this->current - n);
            }
            difference_type             operator-(const vector_iterator& other) const {
                return this->current - other.base();
            }
            template <bool Const>
            bool                        operator<(const vector_iterator<Iterator, Const>& it) const {
                return this->current < it.base();
            }
            template <bool Const>
            bool                        operator>(const vector_iterator<Iterator, Const>& it) const {
                return this->current > it.base();
            }
            template <bool Const>
            bool                        operator<=(const vector_iterator<Iterator, Const>& it) const {
                return !(this->current > it.base());
            }
            template <bool Const>
            bool                        operator>=(const vector_iterator<Iterator, Const>& it) const {
                return !(this->current < it.base());
            }
            vector_iterator&            operator+=(difference_type n) {
                this->current += n;
                return *this;
            }
            vector_iterator&            operator-=(difference_type n) {
                this->current -= n;
                return *this;
            }
            value_type&                 operator[](difference_type n) const {
                return *(*this + n);
            }
        protected:
            value_type                  *current;
    };
    template <typename Iterator, bool Constant>
    vector_iterator<Iterator, Constant> operator+(typename vector_iterator<Iterator, Constant>::difference_type n, const vector_iterator<Iterator, Constant>& it) {
        return it + n;
    };
}

#endif