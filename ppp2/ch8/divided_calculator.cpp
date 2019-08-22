/*
    Simple Calculator
    
    input from cin
    output to cout
*/

#include "Calculator.hpp"

#include <exception>
#include <iostream>

int main() try
{
    Calculator cl {std::cin};
    cl.calculate();
    return 0;
}
catch (const std::exception &e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
catch (...)
{
    std::cerr << "something went wrong" << std::endl;
    return 2;
}
