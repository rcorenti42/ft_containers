/* ************************************************************************** */
/*                                                    ,---.      .`````-.     */
/*                                                   /,--.|     /   ,-.  \    */
/*    ,_   _, _, ,_   _,,  , ___,___,               //_  ||    (___/  |   |   */
/*    |_) /  / \,|_) /_,|\ |' | ' |                /_( )_||          .'  /    */
/*   '| \'\_'\_/'| \'\_ |'\|  |  _|_,             /(_ o _)|      _.-'_.-'     */
/*    '  `  `'   '  `  `'  `  ' '                / /(_,_)||_   _/_  .'        */
/*                                              /  `-----' || ( ' )(__..--.   */
/*   Created: 2022/07/24 18:11:12               `-------|||-'(_{;}_)      |   */
/*                                                      '-'   (_,_)-------'   */
/*   main.cpp                                                                 */
/* ************************************************************************** */

#include <iostream>
#include "vector.hpp"
#include "stack.hpp"
#include <typeinfo>

int main ()
{
    ft::vector<int> foo(3,0);
    ft::vector<int> bar(5,0);
    bar = foo;
    foo = ft::vector<int>();
    std::cout << "Size of foo: " << int(foo.size()) << std::endl;
    std::cout << "Size of bar: " << int(bar.size()) << std::endl;
	return (0);
}