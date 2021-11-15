#include <iostream>
#include "vector.hpp"
#include "stack.hpp"
#include <vector>
#include <stack>
#include <iterator>

int main() {

    std::vector<int> realVector;
    std::stack<int, std::vector<int> > stackVector;

    ft::vector<int> myVector;
    ft::stack<int> myStack;

    realVector.push_back(56); realVector.push_back(57); realVector.push_back(58); realVector.push_back(59);
    stackVector.push(33); stackVector.push(34);stackVector.push(35);stackVector.push(36);stackVector.push(37);stackVector.push(38);

    myVector.push_back(4);myVector.push_back(45);myVector.push_back(466);myVector.push_back(4777);myVector.push_back(48888);myVector.push_back(499999);
    myStack.push(22); myStack.push(23); myStack.push(24); myStack.push(25); myStack.push(26);

    std::vector<int>::iterator it = realVector.begin();
    ft::vector<int>::iterator myIt = myVector.begin();

//    iterator *
//    std::cout << *myIt << " myIt" << std::endl;
//    std::cout << *it << " it" << std::endl;

// increment decrement
//    std::cout << *myIt++ << " myIt postfix ++" << std::endl;
//    std::cout << *++myIt << " myIt prefix ++" << std::endl;
//    std::cout << *myIt-- << " myIt postfix --" << std::endl;
//    std::cout << *--myIt << " myIt prefix --" << std::endl;

//    insert
//    std::cout << myVector.size() << " myVector.size()" << std::endl;
//    std::cout << myVector.size() << " myVector.size()" << std::endl;
//    std::cout << *myVector.insert(myVector.end(), 9999) << " myIt " << std::endl;
//    std::cout << myVector.size() << " myVector.size()" << std::endl;
//    myVector.insert(myVector.end(), 2, 123);
//    std::cout << *(myVector.end() - 2) << " *(myVector.end() - 2)" << std::endl;
//    std::cout << *(myVector.end() - 1) << " *(myVector.end() - 1)" << std::endl;
//    std::cout << myVector.size() << " myVector.size() + 2" << std::endl;
//    myVector.insert(myVector.end(), realVector.begin(), realVector.begin() + 2);
//    std::cout << *(myVector.end() - 2) << " *(myVector.end() - 2)" << std::endl;
//    std::cout << *(myVector.end() - 1) << " *(myVector.end() - 1)" << std::endl;
//    std::cout << myVector.size() << " myVector.size() + 2" << std::endl;

// erase
    std::cout << myVector.size() << " myVector.size()" << std::endl;
    std::cout << *myVector.erase(myVector.begin() + 1, myVector.begin() + 3) << " myVector.erase" << std::endl;
    std::cout << myVector.size() << " myVector.size()" << std::endl;
    std::cout << *myVector.erase(myVector.begin()) << " myVector.erase" << std::endl;
    std::cout << myVector.size() << " myVector.size()" << std::endl;



//    vec size()
//    std::cout << myVector.size() << " myVector.size()" << std::endl;
//    std::cout << realVector.size() << " realVector.size()" << std::endl;

//    vector top
//    std::cout << stackVector.top() << " stackVector.top()" << std::endl;
//    std::cout << myStack.top() << " myStack.top()" << std::endl;

//    resize()
//    std::cout << realVector.size() << "realVector.size()" << std::endl;
//    realVector.resize(3);
//    std::cout << realVector.size() << "realVector.size()" << std::endl;

    return 0;
}
