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

namespace ft {
    template <typename Iterator>
    class reverse_iterator: public iterator<typename iterator_traits<Iterator>::iterator_category, typename iterator_traits<Iterator>::value_type, typename iterator_traits<Iterator>::difference_type, typename iterator_traits<Iterator>::pointer, typename iterator_traits<Iterator>::reference> {
        public:
            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type value_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer pointer;
            typedef typename iterator_traits<Iterator>::reference reference;
            reverse_iterator(): current() {
            }
            template <typename Iter>
            reverse_iterator(const reverse_iterator<Iter>& rev_it): current(rev_it.current) {
            }
            explicit reverse_iterator(Iterator it): current(it) {
            }
            typename iterator_traits<Iterator>::reference   operator*() const {
                Iterator tmp = this->current;
                return *--tmp;
            }
            reverse_iterator                                operator+(typename iterator_traits<Iterator>::difference_type n) const {
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
            reverse_iterator&                               operator+=(typename iterator_traits<Iterator>::difference_type n) {
                this->current -= n;
                return *this;
            }
            reverse_iterator                                operator-(typename iterator_traits<Iterator>::difference_type n) const {
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
            reverse_iterator&                               operator-=(typename iterator_traits<Iterator>::difference_type n) {
                this->current += n;
                return *this;
            }
            typename iterator_traits<Iterator>::pointer     operator->() const {
                return &(this->operator*());
            }
            typename iterator_traits<Iterator>::reference   operator[](typename iterator_traits<Iterator>::difference_type n) const {
                return *(*this + n);
            }
            Iterator                                        base() const {
                return this->current;
            }
        protected:
            Iterator                                        current;
    };
    template <typename Iterator>
    bool                                                    operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return lhs.base() == rhs.base();
    }
    template <typename Iterator>
    bool                                                    operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return !(lhs == rhs);
    }
    template <typename Iterator>
    bool                                                    operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() < lhs.base();
    }
    template <typename Iterator>
    bool                                                    operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() <= lhs.base();
    }
    template <typename Iterator>
    bool                                                    operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() > lhs.base();
    }
    template <typename Iterator>
    bool                                                    operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() >= lhs.base();
    }
    template <typename Iterator>
    reverse_iterator<Iterator>                              operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
        return reverse_iterator<Iterator>(rev_it.base() - n);
    }
    template <typename Iterator>
    typename reverse_iterator<Iterator>::difference_type    operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
        return rhs.base() - lhs.base();
    }
}

#endif