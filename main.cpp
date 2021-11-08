#include <iostream>
#include "vector.hpp"
#include "stack.hpp"
#include <vector>
#include <stack>

int main() {

    std::vector<int> realVector(22);
    ft::vector<int> myVector;
    std::cout << myVector.size() << std::endl;

    std::stack<int, std::vector<int> > stackVector;
    ft::stack<int> myStack;

    myStack.push(22);
    stackVector.push(33);

    std::cout << stackVector.top() << " stackVector" << std::endl;
    std::cout << myStack.top() << " myStack" << std::endl;

    return 0;
}
