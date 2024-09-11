#include <iostream>
#include <random>
#include "bigInt_t.h"
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
#include <iomanip>

const unsigned long long DF = 1000000;

// Function to generate a random integer in a given range
long long randomInt(long long min, long long max) 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(min, max);
    return dis(gen);
}

// Function to generate a random floating-point number in a given range
double randomDouble(double min, double max) 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

void additionTest(bool W = true, bool D = true) 
{
    std::cin.tie(NULL);
    std::cin.sync_with_stdio(false);

    if(W)
    {
        for(unsigned long long i = 0; i < DF; ++i) 
        {
            std::cout << "AW " << i << '/' << DF << std::endl; 
            long long int1 = randomInt(-500000, 500000);
            long long int2 = randomInt(-500000, 500000);
            long long expected = int1 + int2;
            
            bigInt_t bigInt1 = int1;
            bigInt_t bigInt2 = int2;
            bigInt_t result = bigInt1 + bigInt2;
            
            if(result != expected)
            {
                std::cout << "Result: " << result << std::endl << "Excepted: " << expected << std::endl;
                std::cin.get();
            }
        }
    }
    if(D)
    {
        for (unsigned long long i = 0; i < DF; ++i)
        {
            std::cout << "AD " << i << '/' << DF << std::endl; 
        
            long double double1 = randomDouble(-500.000, 500.000);
            long double double2 = randomDouble(-500.000, 500.000), e = double1 + double2;
            
            bigInt_t bigInt1 = double1;
            bigInt_t bigInt2 = double2;
            bigInt_t result = bigInt1 + bigInt2;
        }
    }

}

void subtractionTest(bool W = true, bool D = true) 
{
    std::cin.tie(NULL);
    std::cin.sync_with_stdio(false);
    
    if(W)
    {
        for(unsigned long long i = 0; i < DF; ++i) 
        {
            std::cout << "SW " << i << '/' << DF << std::endl;
            
            long long int1 = randomInt(-500000, 500000);
            long long int2 = randomInt(-500000, 500000);
            long long expected = int1 - int2; 
            
            bigInt_t bigInt1 = int1;
            bigInt_t bigInt2 = int2;
            bigInt_t result = bigInt1 - bigInt2;

            if(result != expected)
            {
                std::cout << "Result: " << result << std::endl << "Excepted: " << expected << std::endl;
                std::cin.get();
            }
        }
    }
    if(D)
    {
        for(unsigned long long i = 0; i < DF; ++i)
        {
            std::cout << "SD " << i << '/' << DF << std::endl;
            
            long double double1 = randomDouble(-500.0000, 500.0000);
            long double double2 = randomDouble(-500.0000, 500.0000);
            long double expected = double1 - double2;
            
            bigInt_t bigInt1 = double1;
            bigInt_t bigInt2 = double2;
            bigInt_t result = bigInt1 - bigInt2;
        }
    }
}
void multiplicationTest(bool W = true, bool D = true) 
{
    std::cin.tie(NULL);
    std::cin.sync_with_stdio(false);
    std::fstream FILE1("t_1.txt"), FILE2("t_2.txt");

    if(W)
    {
        for (unsigned long long i = 0; i < DF; ++i) 
        {
            std::cout << "MW " << i << '/' << DF << std::endl;

            long long int1 = randomInt(-500000, 500000);
            long long int2 = randomInt(-500000, 500000);
            long long expected = int1 * int2;
            
            bigInt_t bigInt1 = int1;
            bigInt_t bigInt2 = int2;
            bigInt_t result = bigInt1 * bigInt2;
            
            if(result != expected)
            {
                std::cout << "Result: " << result << std::endl << "Excepted: " << expected << std::endl;
                std::cin.get();
            }
        }
    }
    if(D)
    {
        for(unsigned long long i = 0; i < DF; ++i) 
        {
            
            std::cout << "MD " << i << '/' << DF << std::endl;

            long double double1 = randomDouble(-500.000, 500.000);
            long double double2 = randomDouble(-500.000, 500.000);
            long double expected = double(double1 * double2);
            

            bigInt_t bigInt1 = double1;
            bigInt_t bigInt2 = double2;
            bigInt_t result = bigInt1 * bigInt2;
        }
    }
}
void divisionTest(bool W = true, bool D = true) 
{
    std::cin.tie(NULL);
    std::cin.sync_with_stdio(false);
    
    if(W)
    {
        for(unsigned long long i = 0; i < DF; ++i) 
        {
            std::cout << "DW " << i << '/' << DF << " ";
            
            long long int1 = randomInt(-500000, 500000);
            long long int2 = randomInt(-500000, 500000); // Avoid division by zero
            long double expected = int1 / int2;
        
            if(int1 == 0 || int2 == 0) continue;
        
            bigInt_t bigInt1 = int1;
            bigInt_t bigInt2 = int2;
            bigInt_t result = bigInt1 / bigInt2;
        }
    }
    if(D)
    {
        for(unsigned long long i = 0; i < DF; ++i) 
        {
            std::cout << "DD " << i << '/' << DF << std::endl; 

            long double double1 = randomDouble(-500.000, 500.000);
            long double double2 = randomDouble(-500.000, 500.000);

            if(double1 == 0 || double2 == 0) continue;
            double1 /= double2;

            bigInt_t bigInt1 = double1;
            bigInt_t bigInt2 = double2;
            bigInt_t result = bigInt1 / bigInt2;  
        }
    }
}

template<typename T>
std::string toString(const T num)
{
    std::ostringstream S;
    S << num;
    std::string str = S.str();
    return str;
}

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(0);


    system("pause");
    return 0;
}
