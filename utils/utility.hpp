/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/07/22 23:17:43               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   utility.hpp                                                              */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

#include "type_traits.hpp"

namespace ft {
    template <typename T1, typename T2>
    struct pair {
        typedef typename no_const<T1>::new_type first_type;
        typedef typename no_const<T2>::new_type second_type;
        first_type  first;
        second_type second;
        pair(): first(), second() {
        }
        template <typename U, typename V>
        pair(const pair<U, V> &pr): first(pr.first), second(pr.second) {
        }
        pair(const T1 &a, const T2 &b): first(a), second(b) {
        }
        pair&   operator=(const pair &pr) {
            this->first = pr.first;
            this->second = pr.second;
            return *this;
        }
    };
    template <typename T1, typename T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    };
    template <typename T1, typename T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(lhs == rhs);
    };
    template <typename T1, typename T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    };
    template <typename T1, typename T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(rhs < lhs);
    };
    template <typename T1, typename T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return rhs < lhs;
    };
    template <typename T1, typename T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(lhs < rhs);
    };

    template <typename T1, typename T2>
    pair<T1, T2> make_pair(T1 x, T2 y) {
        return pair<T1, T2>(x, y);
    };
}

#endif