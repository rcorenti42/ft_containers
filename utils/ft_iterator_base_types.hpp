/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/07/21 02:34:09               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   ft_iterator_base_types.hpp                                               */
/* ************************************************************************** */

#ifndef FT_ITERATOR_BASE_TYPES_HPP
# define FT_ITERATOR_BASE_TYPES_HPP

# include <cstddef>
#include <iterator>

namespace ft {
	class	input_iterator_tag {};
	class	output_iterator_tag {};
	class	forward_iterator_tag : public input_iterator_tag {};
	class	bidirectional_iterator_tag : public forward_iterator_tag {};
	class	random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
	struct	iterator {
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	template <class Iterator>
	struct	iterator_traits {
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
	};

	template <class T>
	struct	iterator_traits<T*> {
		typedef typename std::random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
	};

	template <class T>
	struct	iterator_traits<const T*> {
		typedef typename std::random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef const T* pointer;
		typedef const T& reference;
	};
}

#endif
