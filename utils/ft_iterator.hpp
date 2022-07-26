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

    template <typename Iterator, typename Container>
    class   vector_iterator {
        public:
            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type value_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer pointer;
            typedef typename iterator_traits<Iterator>::reference reference;
            vector_iterator(): current(iterator_type()) {
            }
            explicit vector_iterator(const iterator_type& it): current(it) {
            }
            template <typename Iter>
            vector_iterator(const vector_iterator<Iter, typename enable_if<(is_same<Iter, typename Container::pointer>::value), Container>::type>& it) : current(it.base()) {
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
            const iterator_type&                                    base() const {
                return this->current;
            }
            protected:
            iterator_type                                           current;
    };
    template <typename Iterator, typename Container>
    bool                                                            operator==(const vector_iterator<Iterator, Container>& lhs, const vector_iterator<Iterator, Container>& rhs) {
        return lhs.base() == rhs.base();
    };
    template <typename Iterator, typename Container>
    bool                                                            operator!=(const vector_iterator<Iterator, Container>& lhs, const vector_iterator<Iterator, Container>& rhs) {
        return !(lhs == rhs);
    };
    template <typename Iterator, typename Container>
    bool                                                            operator<(const vector_iterator<Iterator, Container>& lhs, const vector_iterator<Iterator, Container>& rhs) {
        return rhs.base() < lhs.base();
    };
    template <typename Iterator, typename Container>
    bool                                                            operator<=(const vector_iterator<Iterator, Container>& lhs, const vector_iterator<Iterator, Container>& rhs) {
        return rhs.base() <= lhs.base();
    };
    template <typename Iterator, typename Container>
    bool                                                            operator>(const vector_iterator<Iterator, Container>& lhs, const vector_iterator<Iterator, Container>& rhs) {
        return rhs.base() > lhs.base();
    };
    template <typename Iterator, typename Container>
    bool                                                            operator>=(const vector_iterator<Iterator, Container>& lhs, const vector_iterator<Iterator, Container>& rhs) {
        return rhs.base() >= lhs.base();
    };
    template <typename Iterator, typename Container>
    vector_iterator<Iterator, Container>                            operator+(typename vector_iterator<Iterator, Container>::difference_type n, const vector_iterator<Iterator, Container>& vec_it) {
        return vector_iterator<Iterator, Container>(vec_it.base() + n);
    };
    template <typename Iterator, typename Container>
    typename vector_iterator<Iterator, Container>::difference_type  operator-(const vector_iterator<Iterator, Container>& lhs, const vector_iterator<Iterator, Container>& rhs) {
        return rhs.base() - lhs.base();
    };
}

#endif