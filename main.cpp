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

    realVector.push_back(22); realVector.push_back(23); realVector.push_back(24); realVector.push_back(266);
    stackVector.push(33); stackVector.push(34);stackVector.push(35);stackVector.push(36);stackVector.push(37);stackVector.push(38);

    myVector.push_back(4);myVector.push_back(45);myVector.push_back(466);myVector.push_back(4777);myVector.push_back(48888);//myVector.push_back(499999);
    myStack.push(22); myStack.push(23); myStack.push(24); myStack.push(25); myStack.push(26);

    std::vector<int>::iterator it = realVector.begin();
    ft::vector<int>::iterator myIt = myVector.begin();

//    max size
    std::cout << myVector.max_size() << " myVector.max_size()" << std::endl;


//iterator *
//    std::cout << *myIt << " myIt" << std::endl;
//    std::cout << *it << " it" << std::endl;

//increment decrement
//    std::cout << *myIt++ << " myIt postfix ++" << std::endl;
//    std::cout << *++myIt << " myIt prefix ++" << std::endl;
//    std::cout << *myIt-- << " myIt postfix --" << std::endl;
//    std::cout << *--myIt << " myIt prefix --" << std::endl;

//const vs noconst
//    ft::vector<int>::const_iterator myConstIt = myVector.begin();
//    ft::vector<int>::const_iterator myConstIt2(myVector.begin());
//    std::vector<int>::const_iterator realConst(it + 2);
//    myConstIt = myIt;
//    myIt = myIt;
////    *myConstIt = 123;
//    std::cout << (myConstIt == myIt) << " - (myConstIt == myIt)" << std::endl;
//    std::cout << (myConstIt2 != myIt) << " - (myConstIt2 != myIt)" << std::endl;
//    std::cout << ((myIt + 2) - myConstIt2) << " - ((myIt + 2) - myConstIt2)" << std::endl;

// reverse iterator
//    ft::vector<int>::reverse_iterator myRevIt = myVector.rbegin();
//    for (int i = 0; i < 5; ++i)
//        myRevIt[i] = (5 - i) * 5;
//    realVector.push_back(26);
//    std::vector<int>::reverse_iterator revIt = realVector.rbegin();
//    for (int i = 0; i < 5; ++i)
//        revIt[i] = (5 - i) * 5;
//    std::cout << realVector.size() << " realVector.size() " << std::endl;
//    std::cout << myVector.size() << " myVector.size()" << std::endl;
//    revIt = revIt + 5;
//    myRevIt = myRevIt + 5;
//    myRevIt = 1 + myRevIt;
//    revIt = 1 + revIt;
//    myRevIt = myRevIt - 4;
//    revIt = revIt - 4;
//    std::cout << *(revIt += 2) << std::endl;
//    std::cout << *(myRevIt += 2) << std::endl;
//    std::cout << *(revIt -= 1) << std::endl;
//    std::cout << *(myRevIt -= 1) << std::endl;
//    ft::vector<int>::const_reverse_iterator myConstRevIt(myVector.rbegin());
//    std::vector<int>::reverse_iterator revIt(realVector.begin());
//    std::cout << *revIt << " - *revIt" << std::endl;
//    std::cout << (myRevIt < myConstRevIt) << " - (myRevIt == myConstRevIt)" << std::endl;


//insert
//    std::cout << myVector.size() << " myVector.size()" << std::endl;
//    std::cout << *myVector.insert(myVector.end(), 9999) << " myVector.insert(myVector.end(), 9999) " << std::endl;
//    std::cout << myVector.size() << " myVector.size()" << std::endl;
//    myVector.insert(myVector.end(), 2, 123);
//    std::cout << *(myVector.end() - 2) << " *(myVector.end() - 2)" << std::endl;
//    std::cout << *(myVector.end() - 1) << " *(myVector.end() - 1)" << std::endl;
//    std::cout << myVector.size() << " myVector.size() =+ 2" << std::endl << std::endl;
//
//    myVector.clear();
//    myVector.insert(myVector.end(),42);
//    myVector.insert(myVector.begin(), 2, 21);
//    myVector.insert(myVector.end() - 2,42);
//
//    std::cout << *(myVector.begin()) << " TEST " << std::endl;
//    std::cout << *(myVector.end() - 2) << " TEST " << std::endl;
//    std::cout << *(myVector.end() - 1) << " TEST *(myVector.end() - 1)" << std::endl;
//    std::cout << myVector.size() << " myVector.size()" << std::endl << std::endl;

//    myVector.insert(myVector.end(), realVector.begin(), realVector.begin() + 2);
//    realVector.clear();
//    std::cout << realVector.size() << " realVector.size() " << std::endl;
//    std::cout << *(myVector.end() - 2) << " *(myVector.end() - 2)" << std::endl;
//    std::cout << *(myVector.end() - 1) << " *(myVector.end() - 1)" << std::endl;
//    std::cout << myVector.size() << " myVector.size() =+ 2" << std::endl;

//assign
//    std::cout << realVector.size() << " realVector.size() " << std::endl;
//    realVector.assign(0, 22);
//    std::cout << realVector.size() << " realVector.size() " << std::endl;
//    std::cout << myVector.size() << " myVector.size()" << std::endl;
//    myVector.assign(2, 22);
//    std::cout << myVector.size() << " myVector.size()" << std::endl;


//erase
//    std::cout << myVector.size() << " myVector.size()" << std::endl;
//    std::cout << *myVector.erase(myVector.begin() + 2, myVector.begin() + 3) << " myVector.erase" << std::endl;
//    std::cout << myVector.size() << " myVector.size()" << std::endl;
//    std::cout << *myVector.erase(myVector.end() - 2) << " myVector.erase" << std::endl;
//    std::cout << myVector.size() << " myVector.size()" << std::endl;

//swap
//    std::cout << myVector.size() << " myVector.size()" << std::endl;
//    ft::vector<int> some;
//    myVector.swap(some);
//    std::cout << myVector.size() << " myVector.size()" << std::endl;

//vec size()
//    std::cout << myVector.size() << " myVector.size()" << std::endl;
//    std::cout << realVector.size() << " realVector.size()" << std::endl;

//vector top
//    std::cout << stackVector.top() << " stackVector.top()" << std::endl;
//    std::cout << myStack.top() << " myStack.top()" << std::endl;

//resize()
//    std::cout << realVector.size() << "realVector.size()" << std::endl;
//    realVector.resize(3);
//    std::cout << realVector.size() << "realVector.size()" << std::endl;

    return 0;
}
