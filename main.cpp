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

    myVector.push_back(4);myVector.push_back(45);myVector.push_back(466);myVector.push_back(4777);
    myStack.push(22); myStack.push(23); myStack.push(24); myStack.push(25); myStack.push(26);

    std::vector<int>::iterator it = realVector.begin();
    ft::vector<int>::iterator myIt = myVector.begin();

    myIt = myVector.begin();
    std::cout << *myIt << " myIt" << std::endl;
    std::cout << *it << " it" << std::endl;
//    myVector.insert(myIt, 4444); // проблемы с наследованием
//    realVector.insert(it, 4444);

    std::cout << *(myIt) << " myIt" << std::endl;

    std::cout << myVector.size() << " myVector.size()" << std::endl;
    std::cout << realVector.size() << " realVector.size()" << std::endl;

    std::cout << stackVector.top() << " stackVector.top()" << std::endl;
    std::cout << myStack.top() << " myStack.top()" << std::endl;

//    resize()
    std::cout << realVector.size() << std::endl;
    realVector.resize(3);
    std::cout << realVector.size() << std::endl;

    return 0;
}
