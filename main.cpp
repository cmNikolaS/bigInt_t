#include <iostream>
#include <string>
#include "bigInt_t.h"
#include <iterator>
#include <iomanip>

void getNumbersAndOp(const std::string problem, bigInt_t &A, bigInt_t &B, char &op)
{
    auto a = problem.find(' ');
    std::string first = problem.substr(0, a);
    op = problem.at(a + 1);
    std::string second = problem.substr(a + 3);
    A = first;
    B = second;
}

int main()
{
    bigInt_t A, B;

    do
    {
        char op;
        std::string problem;
        std::cout << "Enter a problem (e.g., 123 + 456): ";
        std::getline(std::cin, problem);
        getNumbersAndOp(problem, A, B, op);
        if(op == '+')
        std::cout << A << " + " << B << " = " << A + B << std::endl;
        else if(op == '-')
        std::cout << A << " - " << B << " = " << A - B << std::endl;
        else if(op == '*')
        std::cout << A << " * " << B << " = " << A * B << std::endl;
        else if(op == '/')
        std::cout << A << " / " << B << " = " << A / B << std::endl;
    }while(true);

    return 0;
}