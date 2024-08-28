#include <iostream>
#include <random>
#include "bigInt_t.h"
#include <string>
#include <cmath>
#include <sstream>

// Function to generate a random integer in a given range
long long randomInt(long long min, long long max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(min, max);
    return dis(gen);
}

// Function to generate a random floating-point number in a given range
double randomDouble(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

void additionTest() {
    // Edge cases
    bigInt_t a1 = 0, b1 = 0;
    std::cout << "Addition Test 1: 0 + 0 = " << (a1 + b1) << std::endl;

    bigInt_t a2 = 500000, b2 = 0;
    std::cout << "Addition Test 2: 500000 + 0 = " << (a2 + b2) << std::endl;

    bigInt_t a3 = -500000, b3 = 500000;
    std::cout << "Addition Test 3: -500000 + 500000 = " << (a3 + b3) << std::endl;

    bigInt_t a4 = -500000, b4 = -500000;
    std::cout << "Addition Test 4: -500000 + -500000 = " << (a4 + b4) << std::endl;

    // Random cases
    for (int i = 0; i < 5; ++i) {
        long long int1 = randomInt(-500000, 500000);
        long long int2 = randomInt(-500000, 500000);
        bigInt_t bigInt1 = int1;
        bigInt_t bigInt2 = int2;
        bigInt_t result = bigInt1 + bigInt2;
        long long expected = int1 + int2;
        std::cout << "Addition Test " << (5 + i) << ": " << int1 << " + " << int2 << " = " << result;
        std::cout << " (Expected: " << expected << ")" << std::endl;
    }

    for (int i = 0; i < 5; ++i) {
        double double1 = randomDouble(-5000.00000, 5000.00000);
        double double2 = randomDouble(-5000.00000, 5000.00000);
        bigInt_t bigInt1 = double1;
        bigInt_t bigInt2 = double2;
        bigInt_t result = bigInt1 + bigInt2;
        double expected = double1 + double2;
        std::cout << "Addition Test " << (10 + i) << ": " << double1 << " + " << double2 << " = " << result;
        std::cout << " (Expected: " << expected << ")" << std::endl;
    }
}

void subtractionTest() {
    // Edge cases
    bigInt_t a1 = 0, b1 = 0;
    std::cout << "Subtraction Test 1: 0 - 0 = " << (a1 - b1) << std::endl;

    bigInt_t a2 = 500000, b2 = 0;
    std::cout << "Subtraction Test 2: 500000 - 0 = " << (a2 - b2) << std::endl;

    bigInt_t a3 = 500000, b3 = -500000;
    std::cout << "Subtraction Test 3: 500000 - -500000 = " << (a3 - b3) << std::endl;

    bigInt_t a4 = -500000, b4 = 500000;
    std::cout << "Subtraction Test 4: -500000 - 500000 = " << (a4 - b4) << std::endl;

    // Random cases
    for (int i = 0; i < 5; ++i) {
        long long int1 = randomInt(-500000, 500000);
        long long int2 = randomInt(-500000, 500000);
        bigInt_t bigInt1 = int1;
        bigInt_t bigInt2 = int2;
        bigInt_t result = bigInt1 - bigInt2;
        long long expected = int1 - int2;
        std::cout << "Subtraction Test " << (5 + i) << ": " << int1 << " - " << int2 << " = " << result;
        std::cout << " (Expected: " << expected << ")" << std::endl;
    }

    for (int i = 0; i < 5; ++i) {
        double double1 = randomDouble(-5000.00000, 5000.00000);
        double double2 = randomDouble(-5000.00000, 5000.00000);
        bigInt_t bigInt1 = double1;
        bigInt_t bigInt2 = double2;
        bigInt_t result = bigInt1 - bigInt2;
        double expected = double1 - double2;
        std::cout << "Subtraction Test " << (10 + i) << ": " << double1 << " - " << double2 << " = " << result;
        std::cout << " (Expected: " << expected << ")" << std::endl;
    }
}

void multiplicationTest() {
    // Edge cases
    bigInt_t a1 = 0, b1 = 0;
    std::cout << "Multiplication Test 1: 0 * 0 = " << (a1 * b1) << std::endl;

    bigInt_t a2 = 500000, b2 = 0;
    std::cout << "Multiplication Test 2: 500000 * 0 = " << (a2 * b2) << std::endl;

    bigInt_t a3 = -500000, b3 = 500000;
    std::cout << "Multiplication Test 3: -500000 * 500000 = " << (a3 * b3) << std::endl;

    bigInt_t a4 = -500000, b4 = -500000;
    std::cout << "Multiplication Test 4: -500000 * -500000 = " << (a4 * b4) << std::endl;

    // Random cases with integer values
    for (int i = 0; i < 5; ++i) {
        long long int1 = randomInt(-500000, 500000);
        long long int2 = randomInt(-500000, 500000);
        bigInt_t bigInt1 = int1;
        bigInt_t bigInt2 = int2;
        bigInt_t result = bigInt1 * bigInt2;
        long long expected = int1 * int2;
        std::cout << "Multiplication Test " << (5 + i) << ": " << int1 << " * " << int2 << " = " << result;
        std::cout << " (Expected: " << expected << ")" << std::endl;
    }

    // Random cases with floating-point values
    for (int i = 0; i < 5; ++i) {
        double double1 = randomDouble(-500.0000, 500.0000);
        double double2 = randomDouble(-500.0000, 500.0000);
        bigInt_t bigInt1 = double1;
        bigInt_t bigInt2 = double2;
        bigInt_t result = bigInt1 * bigInt2;
        double expected = double1 * double2;
        std::cout << "Multiplication Test " << (10 + i) << ": " << double1 << " * " << double2 << " = " << result;
        std::cout << " (Expected: " << expected << ")" << std::endl;
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
    system("cls");

    // additionTest();
    // subtractionTest();
    multiplicationTest();
    


    system("pause");
    return 0;
}
