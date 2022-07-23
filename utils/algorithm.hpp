/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/07/22 22:37:35               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   algorithm.hpp                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft {
    template <typename InputIterator1, typename InputIterator2>
    bool    equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
        while (first1 != last1) {
            if (!(*first1 == *first2))
                return false;
            first1++;
            first2++;
        }
        return true;
    };

    template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
    bool    equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
        while (first1 != last1) {
            if (!pred(*first1, *first2))
                return false;
            first1++;
            first2++;
        }
        return true;
    };

    template <typename InputIterator1, typename InputIterator2>
    bool    lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
        while (first1 != last1) {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
            first1++;
            first2++;
        }
        return first2 != last2;
    };

    template <typename InputIterator1, typename InputIterator2, typename Compare>
    bool    lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
        while (first1 != last1) {
            if (first2 == last2 || comp(*first2, *first1))
                return false;
            else if (comp(*first1, *first2))
                return true;
            first1++;
            first2++;
        }
        return first2 != last2;
    };
}

#endif