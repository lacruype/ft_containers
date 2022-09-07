#include <iostream>
#include "tests.hpp"
// #include "../include/utils.hpp"

// #include "../include/vector.hpp"

bool mypredicate (int i, int j) {
  return (i==j);
}

void test_equal()
{
    print_header("Equal");
    
    int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
    ft::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

    // using default comparison:
    if ( ft::equal (myvector.begin(), myvector.end(), myints) )
        std::cout << "The contents of both sequences are equal.\n";
    else
        std::cout << "The contents of both sequences differ.\n";

    myvector[3]=81;                                 // myvector: 20 40 60 81 100

    // // using predicate comparison:
    // if ( ft::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
    //     std::cout << "The contents of both sequences are equal.\n";
    // else
    //     std::cout << "The contents of both sequences differ.\n";
    return ;
}