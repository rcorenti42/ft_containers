/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/07/19 01:39:18               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   reverse_iterator.hpp                                                     */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iostream>
# include <iterator_traits.hpp>

namespace	ft {
	template <class Iter>
	class reverse_iterator {
		public:
			reverse_iterator();
			reverse_iterator(Iter);
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> &);
			template <class Iter>
			reverse_iterator &								operator=(const reverse_iterator<Iter> &);
			reference										operator*() const;
			pointer											operator->() const;
			reference										operator[] (difference_type) const;
			reverse_iterator &								operator++();
			reverse_iterator								operator++(int);
			reverse_iterator &								operator--();
			reverse_iterator								operator--(int);
			reverse_iterator								operator+(difference_type) const;
			reverse_iterator								operator-(difference_type) const;
			reverse_iterator &								operator+=(difference_type);
			reverse_iterator &								operator-=(difference_type);
			iterator_type									base() const;

			Iter											iterator_type;
			ft::iterator_traits<Iter>::iterator_category	iterator_category;
			ft::iterator_traits<Iter>::value_type			value_type;
			ft::iterator_traits<Iter>::difference_type		difference_type;
			ft::iterator_traits<Iter>::pointer				pointer;
			ft::iterator_traits<Iter>::reference			reference;
		private:
	};

	template <class Iterator1, class Iterator2>
	bool												operator==(const ft::reverse_iterator<Iterator1> &, const ft::reverse_iterator<Iterator2> &);
	template <class Iterator1, class Iterator2>
	bool												operator!=(const ft::reverse_iterator<Iterator1> &, const ft::reverse_iterator<Iterator2> &);
	template <class Iterator1, class Iterator2>
	bool												operator<(const ft::reverse_iterator<Iterator1> &, const ft::reverse_iterator<Iterator2> &);
	template <class Iterator1, class Iterator2>
	bool												operator<=(const ft::reverse_iterator<Iterator1> &, const ft::reverse_iterator<Iterator2> &);
	template <class Iterator1, class Iterator2>
	bool												operator>(const ft::reverse_iterator<Iterator1> &, const ft::reverse_iterator<Iterator2> &);
	template <class Iterator1, class Iterator2>
	bool												operator>=(const ft::reverse_iterator<Iterator1> &, const ft::reverse_iterator<Iterator2> &);
	template <class Iter>
	reverse_iterator<Iter>								operator+(typename reverse_iterator<Iter>::difference_type, const reverse_iterator<Iter> &);
	template <class Iter>
	typename reverse_iterator<Iter>::difference_type	operator-(const reverse_iterator<Iter> &, const reverse_iterator<Iter> &);
}

#endif