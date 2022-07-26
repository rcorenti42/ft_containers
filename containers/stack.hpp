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

# include <vector>

namespace ft {
    template <typename T, typename Container = std::vector<T> >
    class   stack {
        public:
            typedef T value_type;
            typedef Container container_type;
            typedef typename container_type::size_type size_type;
            typedef typename container_type::reference reference;
            typedef typename container_type::const_reference const_reference;
            explicit stack(const Container& ctnr = Container()): _container(ctnr) {
            }
            stack(const stack& other): _container(other._container) {
            }
            stack&              operator=(const stack& other) {
                this->_container = other._container;
                return *this;
            }
            value_type&         top() {
                return this->_container.back();
            }
            const value_type&   top() const {
                return this->_container.back();
            }
            bool                empty() const {
                return this->_container.empty();
            }
            size_type           size() const {
                return this->_container.size();
            }
            void                push(const value_type& val) {
                this->_container.push_back(val);
            }
            void                pop() {
                this->_container.pop_back();
            }
            friend bool         operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return lhs._container == rhs._container;
            };
            friend bool         operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return lhs._container != rhs._container;
            };
            friend bool         operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return lhs._container < rhs._container;
            };
            friend bool         operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return lhs._container <= rhs._container;
            };
            friend bool         operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return lhs._container > rhs._container;
            };
            friend bool         operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return lhs._container >= rhs._container;
            };
        private:
            container_type      _container;
    };
}

#endif