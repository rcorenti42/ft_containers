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

# include "ft_iterator_base_types.hpp"
# include "type_traits.hpp"


# include <iterator>

namespace ft {
    template <typename Iterator>
    class reverse_iterator: public iterator<typename iterator_traits<Iterator>::iterator_category, typename iterator_traits<Iterator>::value_type, typename iterator_traits<Iterator>::difference_type, typename iterator_traits<Iterator>::pointer, typename iterator_traits<Iterator>::reference> {
        public:
            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer pointer;
            typedef typename iterator_traits<Iterator>::reference reference;
            reverse_iterator(): current() {
            }
            template <typename Iter>
            reverse_iterator(const reverse_iterator<Iter>& rev_it): current(rev_it.current) {
            }
            explicit reverse_iterator(iterator_type it): current(it) {
            }
            reference                                       operator*() const {
                iterator_type tmp = this->current;
                return *--tmp;
            }
            reverse_iterator                                operator+(difference_type n) const {
                return reverse_iterator(this->current - n);
            }
            reverse_iterator&                               operator++() {
                --this->current;
                return *this;
            }
            reverse_iterator                                operator++(int) {
                reverse_iterator tmp = *this;
                --this->current;
                return tmp;
            }
            reverse_iterator&                               operator+=(difference_type n) {
                this->current -= n;
                return *this;
            }
            reverse_iterator                                operator-(difference_type n) const {
                return reverse_iterator(this->current + n);
            }
            reverse_iterator&                               operator--() {
                ++this->current;
                return *this;
            }
            reverse_iterator                                operator--(int) {
                reverse_iterator tmp = *this;
                ++this->current;
                return tmp;
            }
            reverse_iterator&                               operator-=(difference_type n) {
                this->current += n;
                return *this;
            }
            pointer                                         operator->() const {
                return &(this->operator*());
            }
            reference                                       operator[](difference_type n) const {
                return *(*this + n);
            }
            iterator_type                                   base() const {
                return this->current;
            }
        protected:
            iterator_type                                   current;
    };
    template <typename Iterator>
    bool                                                    operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return lhs.base() == rhs.base();
    };
    template <typename Iterator>
    bool                                                    operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return !(lhs == rhs);
    };
    template <typename Iterator>
    bool                                                    operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() < lhs.base();
    };
    template <typename Iterator>
    bool                                                    operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() <= lhs.base();
    };
    template <typename Iterator>
    bool                                                    operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() > lhs.base();
    };
    template <typename Iterator>
    bool                                                    operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() >= lhs.base();
    };
    template <typename Iterator>
    reverse_iterator<Iterator>                              operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
        return reverse_iterator<Iterator>(rev_it.base() - n);
    };
    template <typename Iterator>
    typename reverse_iterator<Iterator>::difference_type    operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() - lhs.base();
    };

    template <typename Iterator, bool Constant>
    class   vector_iterator {
        public:
            typedef ptrdiff_t difference_type;
			typedef std::random_access_iterator_tag iterator_category;
			typedef typename conditional<Constant, const Iterator, Iterator>::type value_type;
			typedef value_type* pointer;
			typedef value_type& reference;
            vector_iterator(): current(Iterator()) {
            }
            vector_iterator(const Iterator* it): current(it) {
            }
            template <bool Const>
			vector_iterator(const vector_iterator<Iterator, Const>& it, typename enable_if<!Const>::type* = 0): current(it.base()) {
			}
            reference                                               operator*() const {
                return *this->current;
            }
            pointer                                                 operator->() const {
                return this->current;
            }
            vector_iterator                                         operator++() {
                ++this->current;
                return *this;
            }
            vector_iterator                                         operator++(int) {
                vector_iterator tmp = *this;
                ++this->current;
                return tmp;
            }
            vector_iterator                                         operator--() {
                --this->current;
                return *this;
            }
            vector_iterator                                         operator--(int) {
                vector_iterator tmp = *this;
                --this->current;
                return tmp;
            }
            vector_iterator                                         operator+(difference_type n) const {
                return vector_iterator(this->current + n);
            }
            vector_iterator                                         operator-(difference_type n) const {
                return vector_iterator(this->current - n);
            }
            vector_iterator&                                        operator+=(difference_type n) {
                this->current += n;
                return *this;
            }
            vector_iterator&                                        operator-=(difference_type n) {
                this->current -= n;
                return *this;
            }
            reference                                               operator[](difference_type n) const {
                return *(this->current + n);
            }
			bool                                                   	operator==(const vector_iterator<Iterator, Constant>& lhs) const {
        		return this->current == lhs.current;
    		}
			bool                                            		operator==(value_type* lhs) const {
				return this->current == lhs;
			}
            const Iterator&                                    base() const {
                return this->current;
            }
            protected:
            Iterator                                           current;
    };
    template <typename Iterator, bool Constant>
    bool                                                            operator<(const vector_iterator<Iterator, Constant>& lhs, const vector_iterator<Iterator, Constant>& rhs) {
        return rhs.base() < lhs.base();
    };
    template <typename Iterator, bool Constant>
    bool                                                            operator<=(const vector_iterator<Iterator, Constant>& lhs, const vector_iterator<Iterator, Constant>& rhs) {
        return rhs.base() <= lhs.base();
    };
    template <typename Iterator, bool Constant>
    bool                                                            operator>(const vector_iterator<Iterator, Constant>& lhs, const vector_iterator<Iterator, Constant>& rhs) {
        return rhs.base() > lhs.base();
    };
    template <typename Iterator, bool Constant>
    bool                                                            operator>=(const vector_iterator<Iterator, Constant>& lhs, const vector_iterator<Iterator, Constant>& rhs) {
        return rhs.base() >= lhs.base();
    };
    template <typename Iterator, bool Constant>
    vector_iterator<Iterator, Constant>                            operator+(typename vector_iterator<Iterator, Constant>::difference_type n, const vector_iterator<Iterator, Constant>& vec_it) {
        return vector_iterator<Iterator, Constant>(vec_it.base() + n);
    };
    template <typename Iterator, bool Constant>
    typename vector_iterator<Iterator, Constant>::difference_type  operator-(const vector_iterator<Iterator, Constant>& lhs, const vector_iterator<Iterator, Constant>& rhs) {
        return rhs.base() - lhs.base();
    };
	template <typename Iterator, bool Constant>
	bool                                                   			operator!=(const vector_iterator<Iterator, Constant>& lhs, const vector_iterator<Iterator, Constant>& rhs) {
		return lhs.base() != rhs.base();
	};
}

#endif