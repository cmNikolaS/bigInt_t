#include <iostream>
#include <string>
#include "bigInt_t.h"

int main()
{
    
    bigInt_t A, B;
    char op;
    while(true)
    {
        std::cout << "A: ";
        std::cin >> A;
        std::cout << "op: ";
        std::cin >> op;
        std::cout << "B: ";
        std::cin >> B;
        std::cout << A << ' ' << op << ' ' << B << " = ";
        if(op == '+')
        std::cout << A + B << std::endl;
        else if(op == '-')
        std::cout << A - B << std::endl;
        else if(op == '*')
        std::cout << A * B << std::endl;
        
    }

    return 0;
}