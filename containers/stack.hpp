/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/07/23 09:59:10               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   stack.hpp                                                                */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {
    template <typename T, typename Container = ft::vector<T> >
    class   stack {
        public:
            typedef T value_type;
            typedef Container container_type;
            typedef typename container_type::size_type size_type;
            typedef typename container_type::reference reference;
            typedef typename container_type::const_reference const_reference;
            explicit stack(const Container& ctnr = Container()): c(ctnr) {
            }
            stack(const stack& other): c(other.c) {
            }
            stack&              operator=(const stack& other) {
                this->c = other.c;
                return *this;
            }
            value_type&         top() {
                return this->c.back();
            }
            const value_type&   top() const {
                return this->c.back();
            }
            bool                empty() const {
                return this->c.empty();
            }
            size_type           size() const {
                return this->c.size();
            }
            void                push(const value_type& val) {
                this->c.push_back(val);
            }
            void                pop() {
                this->c.pop_back();
            }
            friend bool         operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return lhs.c == rhs.c;
            };
            friend bool         operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return lhs.c != rhs.c;
            };
            friend bool         operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return lhs.c < rhs.c;
            };
            friend bool         operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return lhs.c <= rhs.c;
            };
            friend bool         operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return lhs.c > rhs.c;
            };
            friend bool         operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return lhs.c >= rhs.c;
            };
        protected:
            container_type      c;
    };
}

#endif