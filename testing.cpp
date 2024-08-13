#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "bigInt_t.h" 
#include <windows.h>
int main()
{   

    std::cin.tie(0);
    std::cin.sync_with_stdio(false);
    srand(time(0));

    long long iA, iB;

    for(int i = 0; i < 90000; i++)
    {
        std::cout << i << '.' << " ";

        iA = rand() % 1000;
        iA = iA - (2*iA);

        iB = rand() % 1000;
        iB = iB - (2*iB);
        
        bigInt_t A = iA;

        bigInt_t B = iB;

        // std::cout << "A: " << A << " iA: " << iA << std::endl;
        // std::cout << "B: " << B << " iB: " << iB << std::endl;
        A *= B;
        iA *= iB;
        if(A != iA)
        {

        std::cout << "A: " << A << " iA: " << iA << std::endl;
        std::cout << "B: " << B << " iB: " << iB << std::endl;
        // std::cout << "C: " << C << " iC: " << iC << std::endl;
        
            system("pause");
        }
    }
    

    return 0;
}