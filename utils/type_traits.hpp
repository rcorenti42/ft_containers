/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/07/22 18:38:35               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   type_traits.hpp                                                          */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft {
    template <bool Cond, class T = void>
    struct  enable_if {
    };
    template <class T>
    struct  enable_if<true, T> {
        typedef T type;
    };

    template <typename T, T v>
    struct  integral_constant {
        static const T    value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;
    };

	struct true_type: public integral_constant<bool, true> {
	};
	struct false_type: public integral_constant<bool, false> {
	};

    template <typename, typename>
    struct  is_same: false_type {
    };
    template <typename T>
    struct  is_same<T, T>: true_type {
    };

    template <typename T>
    struct  is_integral_helper: public false_type {
    };
    template <>
    struct  is_integral_helper<bool>: public true_type {
    };
    template <>
    struct  is_integral_helper<const bool>: public true_type {
    };
    template <>
    struct  is_integral_helper<volatile bool>: public true_type {
    };
    template <>
    struct  is_integral_helper<const volatile bool>: public true_type {
    };
    template <>
    struct  is_integral_helper<char>: public true_type {
    };
    template <>
    struct  is_integral_helper<const char>: public true_type {
    };
    template <>
    struct  is_integral_helper<volatile char>: public true_type {
    };
    template <>
    struct  is_integral_helper<const volatile char>: public true_type {
    };
    template <>
    struct  is_integral_helper<signed char>: public true_type {
    };
    template <>
    struct  is_integral_helper<const signed char>: public true_type {
    };
    template <>
    struct  is_integral_helper<volatile signed char>: public true_type {
    };
    template <>
    struct  is_integral_helper<const volatile signed char>: public true_type {
    };
    template <>
    struct  is_integral_helper<unsigned char>: public true_type {
    };
    template <>
    struct  is_integral_helper<const unsigned char>: public true_type {
    };
    template <>
    struct  is_integral_helper<volatile unsigned char>: public true_type {
    };
    template <>
    struct  is_integral_helper<const volatile unsigned char>: public true_type {
    };
    template <>
    struct  is_integral_helper<wchar_t>: public true_type {
    };
    template <>
    struct  is_integral_helper<const wchar_t>: public true_type {
    };
    template <>
    struct  is_integral_helper<volatile wchar_t>: public true_type {
    };
    template <>
    struct  is_integral_helper<const volatile wchar_t>: public true_type {
    };
    template <>
    struct  is_integral_helper<short>: public true_type {
    };
    template <>
    struct  is_integral_helper<const short>: public true_type {
    };
    template <>
    struct  is_integral_helper<volatile short>: public true_type {
    };
    template <>
    struct  is_integral_helper<const volatile short>: public true_type {
    };
    template <>
    struct  is_integral_helper<unsigned short>: public true_type {
    };
    template <>
    struct  is_integral_helper<const unsigned short>: public true_type {
    };
    template <>
    struct  is_integral_helper<volatile unsigned short>: public true_type {
    };
    template <>
    struct  is_integral_helper<const volatile unsigned short>: public true_type {
    };
    template <>
    struct  is_integral_helper<int>: public true_type {
    };
    template <>
    struct  is_integral_helper<const int>: public true_type {
    };
    template <>
    struct  is_integral_helper<volatile int>: public true_type {
    };
    template <>
    struct  is_integral_helper<const volatile int>: public true_type {
    };
    template <>
    struct  is_integral_helper<unsigned>: public true_type {
    };
    template <>
    struct  is_integral_helper<const unsigned>: public true_type {
    };
    template <>
    struct  is_integral_helper<volatile unsigned>: public true_type {
    };
    template <>
    struct  is_integral_helper<const volatile unsigned>: public true_type {
    };
    template <>
    struct  is_integral_helper<long>: public true_type {
    };
    template <>
    struct  is_integral_helper<const long>: public true_type {
    };
    template <>
    struct  is_integral_helper<volatile long>: public true_type {
    };
    template <>
    struct  is_integral_helper<const volatile long>: public true_type {
    };
    template <>
    struct  is_integral_helper<unsigned long>: public true_type {
    };
    template <>
    struct  is_integral_helper<const unsigned long>: public true_type {
    };
    template <>
    struct  is_integral_helper<volatile unsigned long>: public true_type {
    };
    template <>
    struct  is_integral_helper<const volatile unsigned long>: public true_type {
    };
    template <>
    struct  is_integral_helper<long long>: public true_type {
    };
    template <>
    struct  is_integral_helper<const long long>: public true_type {
    };
    template <>
    struct  is_integral_helper<volatile long long>: public true_type {
    };
    template <>
    struct  is_integral_helper<const volatile long long>: public true_type {
    };
    template <>
    struct  is_integral_helper<unsigned long long>: public true_type {
    };
    template <>
    struct  is_integral_helper<const unsigned long long>: public true_type {
    };
    template <>
    struct  is_integral_helper<volatile unsigned long long>: public true_type {
    };
    template <>
    struct  is_integral_helper<const volatile unsigned long long>: public true_type {
    };
    template <typename T>
    struct  is_integral: public is_integral_helper<T> {
    };
    template <bool Cond, typename T = void, typename F = void>
    struct  conditional_helper {
    };
    template <typename T, typename F>
    struct  conditional_helper<true, T, F> {
        typedef T type;
    };
    template <typename T, typename F>
    struct  conditional_helper<false, T, F> {
        typedef F type;
    };
    template <bool Cond, typename T, typename F>
    struct  conditional: public conditional_helper<Cond, T, F> {
    };
}

#endif