#include "map.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "algorithm.hpp"
#include "ft_iterator_base_types.hpp"
#include "ft_iterator.hpp"
#include "rb_tree.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include <stack>
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include <deque>

int main() {
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "STACK" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl << std::endl;

    std::cout << "Constructors & Size : " << std::endl << std::endl;

    std::vector<int> v(5, 42);
    NAMESPACE::stack<int> s1;
    NAMESPACE::stack<int, std::vector<int> > s2;
    NAMESPACE::stack<int, std::vector<int> > s3(v);
    std::cout << "s1.size() = " << s1.size() << std::endl;
    std::cout << "s2.size() = " << s2.size() << std::endl;
    std::cout << "s3.size() = " << s3.size() << std::endl;

    std::cout << std::endl << "Empty : " << std::endl << std::endl;

    std::cout << "s1.empty() = " << s1.empty() << std::endl;
    std::cout << "s2.empty() = " << s2.empty() << std::endl;
    std::cout << "s3.empty() = " << s3.empty() << std::endl;

    std::cout << std::endl << "Top : " << std::endl << std::endl;

    std::cout << "s3.top() = " << s3.top() << std::endl;

    std::cout << std::endl << "Push : " << std::endl << std::endl;

    s3.push(21);
    std::cout << "s3.top() = " << s3.top() << std::endl;
    std::cout << "s3.size() = " << s3.size() << std::endl;

    std::cout << std::endl << "Pop : " << std::endl << std::endl;

    s3.pop();
    std::cout << "s3.top() = " << s3.top() << std::endl;
    std::cout << "s3.size() = " << s3.size() << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "VECTOR" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl << std::endl;

    std::cout << "Constructors & Size : " << std::endl << std::endl;

    NAMESPACE::vector<int> v1;
    NAMESPACE::vector<int> v2(5, 42);
    NAMESPACE::vector<int> v3(v2);
    NAMESPACE::vector<int> v4(v2.begin(), v2.end());
    NAMESPACE::vector<int> v5(v2.rbegin(), v2.rend());

    std::cout << "v1.size() = " << v1.size() << std::endl;
    std::cout << "v2.size() = " << v2.size() << std::endl;
    std::cout << "v3.size() = " << v3.size() << std::endl;
    std::cout << "v4.size() = " << v4.size() << std::endl;
    std::cout << "v5.size() = " << v5.size() << std::endl;

    std::cout << std::endl << "Operator = : " << std::endl << std::endl;

    v1 = v2;
    std::cout << "v1.size() = " << v1.size() << std::endl;
    std::cout << "v2.size() = " << v2.size() << std::endl;

    std::cout << std::endl << "Begin : " << std::endl << std::endl;

    std::cout << "v1.begin() = " << *v1.begin() << std::endl;
    std::cout << "v2.begin() = " << *v2.begin() << std::endl;
    std::cout << "v3.begin() = " << *v3.begin() << std::endl;
    std::cout << "v4.begin() = " << *v4.begin() << std::endl;
    std::cout << "v5.begin() = " << *v5.begin() << std::endl;

    std::cout << std::endl << "End : " << std::endl << std::endl;

    std::cout << "v1.end() = " << *v1.end() << std::endl;
    std::cout << "v2.end() = " << *v2.end() << std::endl;
    std::cout << "v3.end() = " << *v3.end() << std::endl;
    std::cout << "v4.end() = " << *v4.end() << std::endl;
    std::cout << "v5.end() = " << *v5.end() << std::endl;

    std::cout << std::endl << "Rbegin : " << std::endl << std::endl;

    std::cout << "v1.rbegin() = " << *v1.rbegin() << std::endl;
    std::cout << "v2.rbegin() = " << *v2.rbegin() << std::endl;
    std::cout << "v3.rbegin() = " << *v3.rbegin() << std::endl;
    std::cout << "v4.rbegin() = " << *v4.rbegin() << std::endl;
    std::cout << "v5.rbegin() = " << *v5.rbegin() << std::endl;

    std::cout << std::endl << "Rend : " << std::endl << std::endl;

    std::cout << "v1.rend() = " << *v1.rend() << std::endl;
    std::cout << "v2.rend() = " << *v2.rend() << std::endl;
    std::cout << "v3.rend() = " << *v3.rend() << std::endl;
    std::cout << "v4.rend() = " << *v4.rend() << std::endl;
    std::cout << "v5.rend() = " << *v5.rend() << std::endl;

    std::cout << std::endl << "Max_size : " << std::endl << std::endl;

    std::cout << "v1.max_size() = " << v1.max_size() << std::endl;
    std::cout << "v2.max_size() = " << v2.max_size() << std::endl;
    std::cout << "v3.max_size() = " << v3.max_size() << std::endl;
    std::cout << "v4.max_size() = " << v4.max_size() << std::endl;
    std::cout << "v5.max_size() = " << v5.max_size() << std::endl;

    std::cout << std::endl << "Resize : " << std::endl << std::endl;

    std::cout << "v1.size() = " << v1.size() << std::endl;
    v1.resize(10, 4242);
    std::cout << "v1.size() = " << v1.size() << std::endl;
    std::cout << "v1[0] = " << v1[0] << std::endl;
    std::cout << "v1[1] = " << v1[1] << std::endl;
    std::cout << "v1[2] = " << v1[2] << std::endl;
    std::cout << "v1[3] = " << v1[3] << std::endl;
    std::cout << "v1[4] = " << v1[4] << std::endl;
    std::cout << "v1[5] = " << v1[5] << std::endl;
    std::cout << "v1[6] = " << v1[6] << std::endl;
    std::cout << "v1[7] = " << v1[7] << std::endl;
    std::cout << "v1[8] = " << v1[8] << std::endl;
    std::cout << "v1[9] = " << v1[9] << std::endl;
    
    std::cout << std::endl << "Capacity : " << std::endl << std::endl;

    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    std::cout << "v2.capacity() = " << v2.capacity() << std::endl;
    std::cout << "v3.capacity() = " << v3.capacity() << std::endl;

    std::cout << std::endl << "Empty : " << std::endl << std::endl;

    std::cout << "v1.empty() = " << v1.empty() << std::endl;
    std::cout << "v2.empty() = " << v2.empty() << std::endl;
    std::cout << "v3.empty() = " << v3.empty() << std::endl;
    std::cout << "v4.empty() = " << v4.empty() << std::endl;
    std::cout << "v5.empty() = " << v5.empty() << std::endl;

    std::cout << std::endl << "Reserve : " << std::endl << std::endl;
    
    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    v1.reserve(100);
    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    v1.reserve(10);
    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;

    std::cout << std::endl << "Operator [] : " << std::endl << std::endl;

    std::cout << "v1[0] = " << v1[0] << std::endl;
    std::cout << "v1[1] = " << v1[1] << std::endl;
    std::cout << "v1[2] = " << v1[2] << std::endl;
    std::cout << "v1[3] = " << v1[3] << std::endl;
    std::cout << "v1[4] = " << v1[4] << std::endl;
    std::cout << "v1[5] = " << v1[5] << std::endl;
    std::cout << "v1[6] = " << v1[6] << std::endl;
    std::cout << "v1[7] = " << v1[7] << std::endl;
    std::cout << "v1[8] = " << v1[8] << std::endl;
    std::cout << "v1[9] = " << v1[9] << std::endl;

    std::cout << std::endl << "At : " << std::endl << std::endl;

    std::cout << "v1.at(0) = " << v1.at(0) << std::endl;
    std::cout << "v1.at(1) = " << v1.at(1) << std::endl;
    std::cout << "v1.at(2) = " << v1.at(2) << std::endl;
    std::cout << "v1.at(3) = " << v1.at(3) << std::endl;
    std::cout << "v1.at(4) = " << v1.at(4) << std::endl;
    std::cout << "v1.at(5) = " << v1.at(5) << std::endl;
    std::cout << "v1.at(6) = " << v1.at(6) << std::endl;
    std::cout << "v1.at(7) = " << v1.at(7) << std::endl;
    std::cout << "v1.at(8) = " << v1.at(8) << std::endl;
    std::cout << "v1.at(9) = " << v1.at(9) << std::endl;

    std::cout << std::endl << "Front : " << std::endl << std::endl;

    std::cout << "v1.front() = " << v1.front() << std::endl;

    std::cout << std::endl << "Back : " << std::endl << std::endl;

    std::cout << "v1.back() = " << v1.back() << std::endl;

    std::cout << std::endl << "Assign : " << std::endl << std::endl;

    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    v1.assign(10, 100);
    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    std::cout << "v1[0] = " << v1[0] << std::endl;
    std::cout << "v1[1] = " << v1[1] << std::endl;
    std::cout << "v1[2] = " << v1[2] << std::endl;
    std::cout << "v1[3] = " << v1[3] << std::endl;
    std::cout << "v1[4] = " << v1[4] << std::endl;
    std::cout << "v1[5] = " << v1[5] << std::endl;
    std::cout << "v1[6] = " << v1[6] << std::endl;
    std::cout << "v1[7] = " << v1[7] << std::endl;
    std::cout << "v1[8] = " << v1[8] << std::endl;
    std::cout << "v1[9] = " << v1[9] << std::endl;

    std::cout << std::endl << "Push_back : " << std::endl << std::endl;

    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    v1.push_back(1000);
    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    std::cout << "v1[10] = " << v1[10] << std::endl;

    std::cout << std::endl << "Pop_back : " << std::endl << std::endl;

    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    v1.pop_back();
    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    std::cout << "v1[10] = " << v1[10] << std::endl;

    std::cout << std::endl << "Insert : " << std::endl << std::endl;

    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    v1.insert(v1.begin(), 10000);
    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    std::cout << "v1[0] = " << v1[0] << std::endl;
    std::cout << "v1[1] = " << v1[1] << std::endl;
    std::cout << "v1[2] = " << v1[2] << std::endl;
    std::cout << "v1[3] = " << v1[3] << std::endl;
    std::cout << "v1[4] = " << v1[4] << std::endl;
    std::cout << "v1[5] = " << v1[5] << std::endl;
    std::cout << "v1[6] = " << v1[6] << std::endl;
    std::cout << "v1[7] = " << v1[7] << std::endl;
    std::cout << "v1[8] = " << v1[8] << std::endl;
    std::cout << "v1[9] = " << v1[9] << std::endl;
    std::cout << "v1[10] = " << v1[10] << std::endl;
    std::cout << "v1[11] = " << v1[11] << std::endl;

    std::cout << std::endl << "Erase : " << std::endl << std::endl;

    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    v1.erase(v1.begin());
    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    std::cout << "v1[0] = " << v1[0] << std::endl;
    std::cout << "v1[1] = " << v1[1] << std::endl;
    std::cout << "v1[2] = " << v1[2] << std::endl;
    std::cout << "v1[3] = " << v1[3] << std::endl;
    std::cout << "v1[4] = " << v1[4] << std::endl;
    std::cout << "v1[5] = " << v1[5] << std::endl;
    std::cout << "v1[6] = " << v1[6] << std::endl;
    std::cout << "v1[7] = " << v1[7] << std::endl;
    std::cout << "v1[8] = " << v1[8] << std::endl;
    std::cout << "v1[9] = " << v1[9] << std::endl;
    std::cout << "v1[10] = " << v1[10] << std::endl;

    std::cout << std::endl << "Swap : " << std::endl << std::endl;

    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    std::cout << "v2.capacity() = " << v2.capacity() << std::endl;
    v1.swap(v2);
    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    std::cout << "v2.capacity() = " << v2.capacity() << std::endl;

    std::cout << std::endl << "Clear : " << std::endl << std::endl;

    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;
    v1.clear();
    std::cout << "v1.capacity() = " << v1.capacity() << std::endl;

    std::cout << std::endl << "Operators : " << std::endl << std::endl;

    std::cout << "v1 == v2 : " << (v1 == v2) << std::endl;
    std::cout << "v1 != v2 : " << (v1 != v2) << std::endl;
    std::cout << "v1 < v2 : " << (v1 < v2) << std::endl;
    std::cout << "v1 <= v2 : " << (v1 <= v2) << std::endl;
    std::cout << "v1 > v2 : " << (v1 > v2) << std::endl;
    std::cout << "v1 >= v2 : " << (v1 >= v2) << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "MAP" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl << std::endl;

    std::cout << std::endl << "Constructors & Size : " << std::endl << std::endl;

    NAMESPACE::map<int, int> m1;
    m1[0] = 0;
    m1[1] = 1;
    m1[2] = 2;
    m1[3] = 3;
    m1[4] = 4;
    m1[5] = 5;
    NAMESPACE::map<int, int> m2(m1);
    NAMESPACE::map<int, int> m3(m1.begin(), m1.end());
    NAMESPACE::map<int, int> m4(m1.begin(), m1.end(), m1.key_comp());
    NAMESPACE::map<int, int> m5(m1.begin(), m1.end(), m1.key_comp(), m1.get_allocator());
    std::cout << "m1.size() = " << m1.size() << std::endl;
    std::cout << "m2.size() = " << m2.size() << std::endl;
    std::cout << "m3.size() = " << m3.size() << std::endl;
    std::cout << "m4.size() = " << m4.size() << std::endl;
    std::cout << "m5.size() = " << m5.size() << std::endl;

    std::cout << std::endl << "Operators = : " << std::endl << std::endl;

    m1 = m2;
    std::cout << "m1.size() = " << m1.size() << std::endl;
    std::cout << "m2.size() = " << m2.size() << std::endl;

    std::cout << std::endl << "At : " << std::endl << std::endl;

    std::cout << "m1.at(0) = " << m1.at(0) << std::endl;
    std::cout << "m1.at(1) = " << m1.at(1) << std::endl;
    std::cout << "m1.at(2) = " << m1.at(2) << std::endl;
    std::cout << "m1.at(3) = " << m1.at(3) << std::endl;
    std::cout << "m1.at(4) = " << m1.at(4) << std::endl;
    std::cout << "m1.at(5) = " << m1.at(5) << std::endl;

    std::cout << std::endl << "Operator [] : " << std::endl << std::endl;

    std::cout << "m1[0] = " << m1[0] << std::endl;
    std::cout << "m1[1] = " << m1[1] << std::endl;
    std::cout << "m1[2] = " << m1[2] << std::endl;
    std::cout << "m1[3] = " << m1[3] << std::endl;
    std::cout << "m1[4] = " << m1[4] << std::endl;
    std::cout << "m1[5] = " << m1[5] << std::endl;

    std::cout << std::endl << "Begin : " << std::endl << std::endl;

    std::cout << "m1.begin()->first = " << m1.begin()->first << std::endl;
    std::cout << "m1.begin()->second = " << m1.begin()->second << std::endl;

    std::cout << std::endl << "Rbegin : " << std::endl << std::endl;

    std::cout << "m1.rbegin()->first = " << m1.rbegin()->first << std::endl;
    std::cout << "m1.rbegin()->second = " << m1.rbegin()->second << std::endl;

    std::cout << std::endl << "Empty : " << std::endl << std::endl;

    std::cout << "m1.empty() = " << m1.empty() << std::endl;
    std::cout << "m2.empty() = " << m2.empty() << std::endl;
    std::cout << "m3.empty() = " << m3.empty() << std::endl;
    std::cout << "m4.empty() = " << m4.empty() << std::endl;
    std::cout << "m5.empty() = " << m5.empty() << std::endl;

    std::cout << std::endl << "Max Size : " << std::endl << std::endl;

    std::cout << "m1.max_size() = " << m1.max_size() << std::endl;
    std::cout << "m2.max_size() = " << m2.max_size() << std::endl;
    std::cout << "m3.max_size() = " << m3.max_size() << std::endl;
    std::cout << "m4.max_size() = " << m4.max_size() << std::endl;
    std::cout << "m5.max_size() = " << m5.max_size() << std::endl;

    std::cout << std::endl << "Clear : " << std::endl << std::endl;

    m5.clear();
    std::cout << "m1.size() = " << m5.size() << std::endl;

    std::cout << std::endl << "Erase : " << std::endl << std::endl;

    m5.erase(5);
    std::cout << "m5.size() = " << m5.size() << std::endl;

    std::cout << std::endl << "Swap : " << std::endl << std::endl;

    m5.swap(m1);
    std::cout << "m1.size() = " << m1.size() << std::endl;
    std::cout << "m5.size() = " << m5.size() << std::endl;

    std::cout << std::endl << "Count : " << std::endl << std::endl;

    std::cout << "m1.count(0) = " << m1.count(0) << std::endl;
    std::cout << "m1.count(1) = " << m1.count(1) << std::endl;
    std::cout << "m1.count(2) = " << m1.count(2) << std::endl;
    std::cout << "m1.count(3) = " << m1.count(3) << std::endl;
    std::cout << "m1.count(4) = " << m1.count(4) << std::endl;
    std::cout << "m1.count(5) = " << m1.count(5) << std::endl;

    std::cout << std::endl << "Find : " << std::endl << std::endl;

    std::cout << "m1.find(0)->first = " << m1.find(0)->first << std::endl;
    std::cout << "m1.find(0)->second = " << m1.find(0)->second << std::endl;
    std::cout << "m1.find(1)->first = " << m1.find(1)->first << std::endl;
    std::cout << "m1.find(1)->second = " << m1.find(1)->second << std::endl;
    std::cout << "m1.find(2)->first = " << m1.find(2)->first << std::endl;
    std::cout << "m1.find(2)->second = " << m1.find(2)->second << std::endl;
    std::cout << "m1.find(3)->first = " << m1.find(3)->first << std::endl;
    std::cout << "m1.find(3)->second = " << m1.find(3)->second << std::endl;
    std::cout << "m1.find(4)->first = " << m1.find(4)->first << std::endl;
    std::cout << "m1.find(4)->second = " << m1.find(4)->second << std::endl;
    std::cout << "m1.find(5)->first = " << m1.find(5)->first << std::endl;
    std::cout << "m1.find(5)->second = " << m1.find(5)->second << std::endl;

    std::cout << std::endl << "Equal Range : " << std::endl << std::endl;

    std::cout << "m1.equal_range(0).first->first = " << m1.equal_range(0).first->first << std::endl;
    std::cout << "m1.equal_range(0).first->second = " << m1.equal_range(0).first->second << std::endl;
    std::cout << "m1.equal_range(0).second->first = " << m1.equal_range(0).second->first << std::endl;
    std::cout << "m1.equal_range(0).second->second = " << m1.equal_range(0).second->second << std::endl;
    std::cout << "m1.equal_range(1).first->first = " << m1.equal_range(1).first->first << std::endl;
    std::cout << "m1.equal_range(1).first->second = " << m1.equal_range(1).first->second << std::endl;
    std::cout << "m1.equal_range(1).second->first = " << m1.equal_range(1).second->first << std::endl;
    std::cout << "m1.equal_range(1).second->second = " << m1.equal_range(1).second->second << std::endl;
    std::cout << "m1.equal_range(2).first->first = " << m1.equal_range(2).first->first << std::endl;
    std::cout << "m1.equal_range(2).first->second = " << m1.equal_range(2).first->second << std::endl;
    std::cout << "m1.equal_range(2).second->first = " << m1.equal_range(2).second->first << std::endl;
    std::cout << "m1.equal_range(2).second->second = " << m1.equal_range(2).second->second << std::endl;
    std::cout << "m1.equal_range(3).first->first = " << m1.equal_range(3).first->first << std::endl;
    std::cout << "m1.equal_range(3).first->second = " << m1.equal_range(3).first->second << std::endl;
    std::cout << "m1.equal_range(3).second->first = " << m1.equal_range(3).second->first << std::endl;
    std::cout << "m1.equal_range(3).second->second = " << m1.equal_range(3).second->second << std::endl;
    std::cout << "m1.equal_range(4).first->first = " << m1.equal_range(4).first->first << std::endl;
    std::cout << "m1.equal_range(4).first->second = " << m1.equal_range(4).first->second << std::endl;
    std::cout << "m1.equal_range(4).second->first = " << m1.equal_range(4).second->first << std::endl;
    std::cout << "m1.equal_range(4).second->second = " << m1.equal_range(4).second->second << std::endl;
    std::cout << "m1.equal_range(5).first->first = " << m1.equal_range(5).first->first << std::endl;
    std::cout << "m1.equal_range(5).first->second = " << m1.equal_range(5).first->second << std::endl;
    std::cout << "m1.equal_range(5).second->first = " << m1.equal_range(5).second->first << std::endl;
    std::cout << "m1.equal_range(5).second->second = " << m1.equal_range(5).second->second << std::endl;

    std::cout << std::endl << "Lower Bound : " << std::endl << std::endl;

    std::cout << "m1.lower_bound(0)->first = " << m1.lower_bound(0)->first << std::endl;
    std::cout << "m1.lower_bound(0)->second = " << m1.lower_bound(0)->second << std::endl;
    std::cout << "m1.lower_bound(1)->first = " << m1.lower_bound(1)->first << std::endl;
    std::cout << "m1.lower_bound(1)->second = " << m1.lower_bound(1)->second << std::endl;
    std::cout << "m1.lower_bound(2)->first = " << m1.lower_bound(2)->first << std::endl;
    std::cout << "m1.lower_bound(2)->second = " << m1.lower_bound(2)->second << std::endl;
    std::cout << "m1.lower_bound(3)->first = " << m1.lower_bound(3)->first << std::endl;
    std::cout << "m1.lower_bound(3)->second = " << m1.lower_bound(3)->second << std::endl;
    std::cout << "m1.lower_bound(4)->first = " << m1.lower_bound(4)->first << std::endl;
    std::cout << "m1.lower_bound(4)->second = " << m1.lower_bound(4)->second << std::endl;
    std::cout << "m1.lower_bound(5)->first = " << m1.lower_bound(5)->first << std::endl;
    std::cout << "m1.lower_bound(5)->second = " << m1.lower_bound(5)->second << std::endl;

    std::cout << std::endl << "Upper Bound : " << std::endl << std::endl;

    std::cout << "m1.upper_bound(0)->first = " << m1.upper_bound(0)->first << std::endl;
    std::cout << "m1.upper_bound(0)->second = " << m1.upper_bound(0)->second << std::endl;
    std::cout << "m1.upper_bound(1)->first = " << m1.upper_bound(1)->first << std::endl;
    std::cout << "m1.upper_bound(1)->second = " << m1.upper_bound(1)->second << std::endl;
    std::cout << "m1.upper_bound(2)->first = " << m1.upper_bound(2)->first << std::endl;
    std::cout << "m1.upper_bound(2)->second = " << m1.upper_bound(2)->second << std::endl;
    std::cout << "m1.upper_bound(3)->first = " << m1.upper_bound(3)->first << std::endl;
    std::cout << "m1.upper_bound(3)->second = " << m1.upper_bound(3)->second << std::endl;
    std::cout << "m1.upper_bound(4)->first = " << m1.upper_bound(4)->first << std::endl;
    std::cout << "m1.upper_bound(4)->second = " << m1.upper_bound(4)->second << std::endl;
    std::cout << "m1.upper_bound(5)->first = " << m1.upper_bound(5)->first << std::endl;
    std::cout << "m1.upper_bound(5)->second = " << m1.upper_bound(5)->second << std::endl;

    std::cout << std::endl << "Key Comp : " << std::endl << std::endl;

    std::cout << "m1.key_comp()(0, 1) = " << m1.key_comp()(0, 1) << std::endl;
    std::cout << "m1.key_comp()(1, 0) = " << m1.key_comp()(1, 0) << std::endl;
    std::cout << "m1.key_comp()(0, 0) = " << m1.key_comp()(0, 0) << std::endl;
    std::cout << "m1.key_comp()(1, 1) = " << m1.key_comp()(1, 1) << std::endl;
    std::cout << "m1.key_comp()(2, 1) = " << m1.key_comp()(2, 1) << std::endl;
    std::cout << "m1.key_comp()(1, 2) = " << m1.key_comp()(1, 2) << std::endl;
    std::cout << "m1.key_comp()(2, 2) = " << m1.key_comp()(2, 2) << std::endl;

    std::cout << std::endl << "Operators : " << std::endl << std::endl;

    std::cout << "m1 == m2 = " << (m1 == m2) << std::endl;
    std::cout << "m1 != m2 = " << (m1 != m2) << std::endl;
    std::cout << "m1 < m2 = " << (m1 < m2) << std::endl;
    std::cout << "m1 <= m2 = " << (m1 <= m2) << std::endl;
    std::cout << "m1 > m2 = " << (m1 > m2) << std::endl;
    std::cout << "m1 >= m2 = " << (m1 >= m2) << std::endl;

    return 0;
}