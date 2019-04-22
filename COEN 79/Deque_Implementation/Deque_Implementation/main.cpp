//
// main.cpp
// PROVIDES: A test file for deque and its iterator
//
// COEN 79
// Behnam Dezfouli, COEN, SCU


#include <iostream>
#include "deque.h"

using namespace coen79_lab8;

int main(int argc, const char * argv[]) {
    
    int test_number = 0;
    
    // ------------- Test: constructor -------------
    std::cout << "Test number: " << ++test_number << "\n";
    std::cout << "Testing constructor...!\n";
    coen79_lab8::deque<int> myDeque1;
    std::cout << "Done!\n\n";
    
    
    // ------------- Test: push_back() and back() -------------
    std::cout << "Test number: " << ++test_number << "\n";
    std::cout << "Testing push_back() and back()...!\n";
    for (int i = 0; i < 100; ++i)
    {
        myDeque1.push_back(i);
        std::cout << myDeque1.back() << " ";
    }
    std::cout << "\n" << "Done!\n\n";
    
    
    // ------------- Test: push_front() and front() -------------
    std::cout << "Test number: " << ++test_number << "\n";
    std::cout << "Testing push_front() and front()...!\n";
    for (int i = 0; i < 100; ++i)
    {
        myDeque1.push_front(i);
        std::cout << myDeque1.front() << " ";
    }
    std::cout << "\n" << "Done!\n\n";
    
    
    // ------------- Test: iterator -------------
    std::cout << "Test number: " << ++test_number << "\n";
    std::cout << "Testing iterator...!\n";
    for (deque<int>::iterator it = myDeque1.begin(); it != myDeque1.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n" << "Done!\n\n";
    
    
    // ------------- Test: pop_front() -------------
    std::cout << "Test number: " << ++test_number << "\n";
    std::cout << "Testing pop_front()...!\n";
    for (int i = 0; i < 100; ++i)
    {
        myDeque1.pop_front();
    }
    std::cout << "\nFront is: " << myDeque1.front();
    std::cout << "\nBack is: " << myDeque1.back();
    std::cout << "\n" << "Done!\n\n";
    
    
    // ------------- Test: pop_back() -------------
    std::cout << "Test number: " << ++test_number << "\n";
    std::cout << "Testing pop_back()...!\n";
    for (int i = 0; i < 10; ++i)
    {
        myDeque1.pop_back();
    }
    std::cout << "\nFront is: " << myDeque1.front();
    std::cout << "\nBack is: " << myDeque1.back();
    std::cout << "\n" << "Done!\n\n";
    
    
    // ------------- Test: iterator -------------
    std::cout << "Test number: " << ++test_number << "\n";
    std::cout << "Testing iterator...!\n";
    for (deque<int>::iterator it = myDeque1.begin(); it != myDeque1.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n" << "Done!\n\n";
    
    
    
    // ------------- Test: assignment operator -------------
    std::cout << "Test number: " << ++test_number << "\n";
    std::cout << "Testing assignment operator...!\n";
    coen79_lab8::deque<int> myDeque2;
    myDeque2.push_front(3);
    myDeque2.push_front(2);
    myDeque2.push_front(1);
    myDeque2.push_back(4);
    myDeque2.push_back(5);
    myDeque2.push_back(6);
    
    coen79_lab8::deque<int> myDeque3;
    myDeque3 = myDeque2;
    
    for (deque<int>::iterator it = myDeque3.begin(); it != myDeque3.end(); ++it)
        std::cout << *it << " ";
    
    std::cout << "\n" << "Done!\n\n";
    
    
    
    // ------------- Test: copy constructor-------------
    std::cout << "Test number: " << ++test_number << "\n";
    std::cout << "Testing copy constructor...!\n";
    coen79_lab8::deque<int> myDeque4(myDeque3);
    
    for (deque<int>::iterator it = myDeque4.begin(); it != myDeque4.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n" << "Done!\n\n";
    
    
    // ------------- Test: iterator-------------
    std::cout << "Test number: " << ++test_number << "\n";
    std::cout << "Testing iterator...!\n";
    deque<int>::iterator it_start = myDeque4.begin();
    deque<int>::iterator it_end = myDeque4.end();
    deque<int>::iterator it2 = it_start;
    
    
    while(it2 != it_end)
    {
        *it2 = 950;
        ++it2;
    }
    
    
    it2 = it_start;
    
    while(it2 != it_end)
    {
        std::cout << *it2 << " ";
        it2++;
    }
    std::cout << "\n" << "Done!\n\n";
    
    
    
    
    return 0;
}
