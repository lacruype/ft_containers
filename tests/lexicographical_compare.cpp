#include <iostream>
#include "tests.hpp"
#include "../include/utils.hpp"

// a case-insensitive comparison function:
bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }   

void test_lexicographical_compare()  
{
    print_header("Lexicographical_compare");

    char foo[]="Apple";
    char bar[]="apartement";

    std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

   
    //Le 1er est vrai car il s'arrete a la comparaison A < a et donc oui il est vrai
    check("Using default comparison (operator<): ", (ft::lexicographical_compare(foo,foo+5,bar,bar+9)));
  

    //Le 2e mets les lettres en minuscules donc il avance jusqu'a la 3e et on a donc p < a qui est donc faux car p > a
    check("Using mycomp as comparison object: ", (ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp)));



    return ;
}