#include <iostream>
#include "tests.hpp"


template <class T>
typename ft::enable_if<ft::is_integral<T>::value,bool>::type
  is_odd (T i) {return bool(i%2);}

template < class T>
typename ft::enable_if<ft::is_integral<T>::value, bool>::type
is_even (T i) {return !bool(i%2);}


int test_enable_if()
{
    print_header("Enable if / Is Integral");
    short int i = 1;    // code does not compile if type of i is not integral

    std::cout << "i = " << i << " il est donc impaire " << std::endl;
    check("i is impaire", (is_odd(i)));
    check("i is paire", (is_even(i)));

  return 0;
}