#pragma once
#include <assert.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <sstream>

class bigInt_t
{
    private:
    std::string number = "0";
    bool isPositive = true;

    template<typename T>
    std::string toString(const T num) const
    {
        std::ostringstream S;
        S << num;
        std::string str = S.str();
        return str;
    }
    inline int charToInt(const char c) const
    {
        if(!isdigit(c))
        {
            std::cerr << "char: " << c << std::endl;
            assert(false && "charToInt, char is not digit char(0-9)!");
        }
        int i = int(c) - int('0');
        return i;
    }
    inline char intToChar(const int i) const
    {
        char c = char(i + int('0'));
        if(!isdigit(c))
        {
            std::cerr << "char: " << c << std::endl;
            assert(false && "IntToChar, char is not digit char(0-9)!");
        }
        return c;
    }
    bool isNumValid()
    {
        //checking if there is dot if first char is 0
        if(number.at(0) == '0' && number.size() > 1)
        {
            if(number.at(1) != '.')
            {
                std::cerr << number << "<-- this Number is not Valid!" << std::endl;
                assert(false && "isNumValid, first char is '0' but second is not '.'!");
            }
        }
        //checking if last char is dot
        if(number.at(number.size() - 1) == '.')
        {
            std::cerr << number << "<-- this Number is not Valid!" << std::endl;
            assert(false && "isNumValid, last char is '.'!");
        }
        //checking if all characters are digits
        int numOfDots = 0;
        for(char c : number)
        {
            if(c == '.') numOfDots++;
            else if(!isdigit(c))
            {
                std::cerr << number << "<-- this Number is not Valid!" << std::endl;
                assert(false && "isNumValid, char is not digit char(0-9)!");
            }
        }
        //checking if there is more then one digit
        if(numOfDots > 1)
        {
            std::cerr << number << "<-- this Number is not Valid!" << std::endl;
            assert(false && "There is more then 1 dots in number!");
        }
        //checking if dot if first or last character
        if(number.at(0) == '.' || number.at(number.size() - 1) == '.')
        {
            std::cerr << number << "<-- this Number is not Valid!" << std::endl;
            assert(false && "Dot is First/Last character in Number!");
        }
        if(getNumOfDec(number) != 0)
        {
            for(int i = int(number.size()) - 1; i >= 0; i--)
            {
                char c = number.at(std::string::size_type(i));
                if(c == '.') break;
                if (c != '0') break;
                if(c == '0')
                {
                    std::cerr << number << "<-- this Number is not Valid!" << std::endl;
                    assert(false && "isNumValid, number is decimal and ends with 0!");
                }
                std::cerr << number << "<-- this Number is not Valid!" << std::endl;
                std::cerr << number.at(std::string::size_type(i)) << "<-- this is not digit nor dot" << std::endl;
                std::cerr << "How the *** we got here" << std::endl;
                assert(false && "isNumValid, number is decimal and ends with 0!");
            }
        }
        return true;
    }
    void takeNumber(const std::string NUMBER)
    {
        if(NUMBER.at(0) == '-')
        {
            isPositive = false;
            number = NUMBER.substr(1);
        }
        else if(NUMBER.at(0) == '+')
        {
            isPositive = true;
            number = NUMBER.substr(1);
        }
        else
        {
            isPositive = true;
            number = NUMBER;
        }
        bigInt_t num;
        num.number = number;
        num.isPositive = isPositive;
        formatNumber(num);
        number = num.number;
        if(!num.isPositive)
            isPositive = false;
    }
    void formatNumber(bigInt_t &num) const 
    {    
        bigInt_t old = num;
        std::string::size_type i = 0;

        while ((i < num.number.size()) && (num.number.at(i) == '0')) ++i;

        if (i == num.number.size())
        {
            num.number = "0";
            num.isPositive = true;
        }
        else
        {
            if(getNumOfDec(num.number) > 0)
            {
                num.number = num.number.substr(i);
                if(num.number.at(0) == '.')
                {
                    num.number = '0' + num.number;
                    if(num.number == "0.")
                    {
                        num.number = "0";
                        num.isPositive = true;
                    }
                }
            }
            else
            {
                num.number = num.number.substr(i);
            }
        }

        if(getNumOfDec(num.number) != 0)
        {
            for (i = num.number.size() - 1; i > 0; --i)
            {
                if (num.number.at(i) == '0') num.number.pop_back();
                else break;
            }
            if(num.number.at(num.number.size() - 1) == '.')
            {
                num.number.erase(num.number.size() - 1, 1);
            }
        }
        
        if(!num.isNumValid())
        {
            std::cerr << "Number is not valid!" << std::endl;
            std::cerr << "Old: " << old << std::endl;
            std::cerr << "New: " << num << std::endl;
            assert(false && "Number is not valid!");
        }
    }
    std::string::size_type getNumOfDec(const std::string num) const
    {   
        std::string::size_type pos = num.find('.');
        if (pos == std::string::npos) return 0;
        return (num.size() - pos - 1);
    }
    //removes first dot
    inline void removeDot(std::string &num) const
    {
        std::string::size_type numOfDecimals = getNumOfDec(num);
        if (numOfDecimals > 0)
        num.erase(num.size() - numOfDecimals - 1, 1);
    }
    void removeZerosAndDots(std::string &num) const
    {
        std::string::size_type n = getNumOfDec(num);
        for(std::string::size_type i = 0; i < n; i++)
            {
                if(num.at(i) == '0' || num.at(i) == '.')
                num.erase(i, 1);
                else break;
            }
        removeDot(num);
    }

    public:
    std::string::size_type getNumberOfDecimals()
    {
        return getNumOfDec(number);
    }
    bigInt_t percision(std::string::size_type p)
    {
        if(p == getNumberOfDecimals()) return *this;
        
        bigInt_t T = *this;        
        if(p < getNumberOfDecimals())
        {
            T.number = this->number.substr(0, p + std::string::size_type(numOfNonDecPlaces()));
            if(p == 0)
            {
                T.number.pop_back();
            }
            else if((T.number.size()) < (this->number.size() - 1))
            {
                if(charToInt(T.number.at(T.number.size())) > 4)
                {
                    if(T.number.at(T.number.size() - 1) != '9')
                    {
                        T.number.at(T.number.size() - 1) = intToChar(charToInt(T.number.at(T.number.size() - 1)) + 1); 
                    }
                }
            }
        }
        else 
        {
            if(getNumberOfDecimals() == 0) T.number.push_back('.');
            T.number.append(p - std::string::size_type(getNumberOfDecimals()), '0');
        }
        return T;
    }
    std::string::size_type numOfNonDecPlaces() const
    {
        std::string::size_type p = number.find('.');
        if(p == std::string::npos) return number.size(); 
        return p;
    }
                //ASSIGMENT OPERATORS
    //constructors
    bigInt_t()
    {
        number = "0";
        isPositive = true;
    }
    bigInt_t(const bigInt_t &num)
    {
        number = num.number;
        isPositive = num.isPositive;
    }
    bigInt_t(const int num)
    {
        takeNumber(std::to_string(num));
    }
    bigInt_t(std::string num)
    {
        takeNumber(num);
    }
    bigInt_t(const long long num)
    {
        takeNumber(std::to_string(num));
    }
    bigInt_t(const unsigned long long num)
    { 
        takeNumber(std::to_string(num));
    }    
    bigInt_t(const float num)
    {
        takeNumber(toString<float>(num));
    }
    bigInt_t(const double num)
    {
        takeNumber(toString<double>(num));
    }
    bigInt_t(const long double num)
    {
        takeNumber(toString<long double>(num));
    }
    //converson operators:
    operator int()
    {
        std::string num = number;
        if(!isPositive) num = '-' + number;
        return stoi(number);
    }
    operator std::string()
    {
        std::string num = number;
        if(!isPositive) num = '-' + number;
        return num;
    }
    operator long long()
    {
        std::string num = number;
        if(!isPositive) num = '-' + number;
        return stoll(number);
    }
    operator unsigned long long()
    {
        std::string num = number;
        if(!isPositive) num = '-' + number;
        return stoull(number);
    }
    operator float()
    {
        std::string num = number;
        if(!isPositive) num = '-' + number;
        return stof(number);
    }
    operator double()
    {
        std::string num = number;
        if(!isPositive) num = '-' + number;
        return stod(number);
    }
    operator long double()
    {
        std::string num = number;
        if(!isPositive) num = '-' + number;
        return stold(number);
    }
    //operator: =
    void operator=(const bigInt_t num)
    {
        this->number = num.number;
        this->isPositive = num.isPositive;
    }
    void operator=(const int num) 
    { 
        takeNumber(std::to_string(num));
    }
    void operator=(const std::string num) 
    { 
        takeNumber(num);
    }
    void operator=(const long long num)
    {
        takeNumber(std::to_string(num));
    }
    void operator=(const unsigned long long num)
    {
        takeNumber(std::to_string(num));
    }
    void operator=(const float num)
    {
        takeNumber(toString<float>(num));
    }
    void operator=(const double num)
    {
        takeNumber(toString<double>(num));
    }
    void operator=(const long double num)
    {
        takeNumber(toString<long double>(num));
    }
                //I/O OPERATORS
    //operator: <<
    friend std::ostream &operator<<(std::ostream &os, const bigInt_t number)
    {
        if(!number.isPositive)
        {
          os << '-';  
        }
        os << number.number;
        return os;
    }
    //operator: >>
    friend std::istream &operator>>(std::istream &is, bigInt_t &number)
    {
        std::string temp;
        is >> temp;
        number.takeNumber(temp);
        return is;
    }
                //RELATIONAL OPERATORS:
    //operator: ==
    bool operator==(const bigInt_t num) const 
    {
        bigInt_t A(*this), B(num);
        formatNumber(A);
        formatNumber(B);
        if (B.isPositive != A.isPositive) return false;
        if (B.number != A.number) return false;
        return true;
    }
    bool operator==(const int num) const
    {
        return (*this == bigInt_t(num));
    }
    bool operator==(const std::string num) const
    {
        return (*this == bigInt_t(num));
    }
    bool operator==(const long long num) const
    {
        return (*this == bigInt_t(num));
    }
    bool operator==(const unsigned long long num) const
    {
        return (*this == bigInt_t(num));
    }   
    bool operator==(const float num) const
    {
        return (*this == bigInt_t(num));
    }   
    bool operator==(const double num) const
    {
        return (*this == bigInt_t(num));
    }
    bool operator==(const long double num) const
    {
        return (*this == bigInt_t(num));
    }
    friend bool operator==(const int B1, const bigInt_t B2); 
    friend bool operator==(const std::string B1, const bigInt_t B2); 
    friend bool operator==(const long long B1, const bigInt_t B2); 
    friend bool operator==(const unsigned long long B1, const bigInt_t B2); 
    friend bool operator==(const float B1, const bigInt_t B2); 
    friend bool operator==(const double B1, const bigInt_t B2); 
    friend bool operator==(const long double B1, const bigInt_t B2);
    //operator: !=
    bool operator!=(const bigInt_t num) const
    {
        return !(*this == num);
    }
    bool operator!=(const int num) const
    {
        return !(*this == num);
    }
    bool operator!=(const std::string num) const
    {
        return !(*this == num);
    }
    bool operator!=(const long long num) const
    {
        return !(*this == num);
    }
    bool operator!=(const unsigned long long num) const
    {
        return !(*this == num);
    }
    bool operator!=(const float num) const
    {
        return !(*this == num);
    }
    bool operator!=(const double num) const
    {
        return !(*this == num);
    }
    bool operator!=(const long double num) const
    {
        return !(*this == num);
    }
    friend bool operator!=(const int B1, const bigInt_t B2); 
    friend bool operator!=(const std::string B1, const bigInt_t B2); 
    friend bool operator!=(const long long B1, const bigInt_t B2); 
    friend bool operator!=(const unsigned long long B1, const bigInt_t B2); 
    friend bool operator!=(const float B1, const bigInt_t B2); 
    friend bool operator!=(const double B1, const bigInt_t B2); 
    friend bool operator!=(const long double B1, const bigInt_t B2);
    //operator: <
    bool operator<(const bigInt_t num) const
    {
        if(this->isPositive != num.isPositive) return this->isPositive;

        if(*this == num) return false;

        std::string::size_type tD = getNumOfDec(this->number), nD = getNumOfDec(num.number); 
        
        bool isSmaller = false;

        if(this->numOfNonDecPlaces() < num.numOfNonDecPlaces()) isSmaller = true;
        else if(this->numOfNonDecPlaces() > num.numOfNonDecPlaces()) isSmaller = false;
        else
        {  
            std::string thisNumber = this->number, number_2 = num.number;
            if(tD > nD)
            {
                if(nD == 0)
                {
                    number_2.push_back('.');
                    tD--;
                }
                number_2.append(tD - nD, '0');
            }
            else if (nD > tD)
            {
                if(tD == 0)
                {
                    thisNumber.push_back('.');
                    nD--;
                }
                thisNumber.append(nD - tD, '0');
            }
            std::string::size_type i = 0, min = number_2.size();
            for(; i < min; i++)
            {
                if(thisNumber.at(i) == '.' && number_2.at(i) == '.') continue;
                if(charToInt(thisNumber.at(i)) < charToInt(number_2.at(i))) { isSmaller = true; break; }
                else if(charToInt(thisNumber.at(i)) > charToInt(number_2.at(i))){ isSmaller = false; break; }
                else
                {
                    if(i == min)
                    return false;
                }
            }
        }
        if(!this->isPositive)
        isSmaller = !isSmaller;
        
        return isSmaller;
    }
    bool operator<(const int num) const
    {
        return *this < bigInt_t(num);
    }
    bool operator<(const std::string num) const
    {
        return *this < bigInt_t(num);
    }
    bool operator<(const long long num) const
    {
        return *this < bigInt_t(num);
    }
    bool operator<(const unsigned long long num) const
    {
        return *this < bigInt_t(num);
    }
    bool operator<(const float num) const
    {
        return *this < bigInt_t(num);
    }
    bool operator<(const double num) const
    {
        return *this < bigInt_t(num);
    }
    bool operator<(const long double num) const
    {
        return *this < bigInt_t(num);
    }
    friend bool operator<(const int B1, const bigInt_t B2); 
    friend bool operator<(const std::string B1, const bigInt_t B2); 
    friend bool operator<(const long long B1, const bigInt_t B2); 
    friend bool operator<(const unsigned long long B1, const bigInt_t B2); 
    friend bool operator<(const float B1, const bigInt_t B2); 
    friend bool operator<(const double B1, const bigInt_t B2); 
    friend bool operator<(const long double B1, const bigInt_t B2);
    //operator: >
    bool operator>(const bigInt_t num) const
    {
        if(!(*this == num) && !(*this < num)) return true;
        return false;
    }
    bool operator>(const int num) const
    {
        if(!(*this == num) && !(*this < num)) return true;
        return false;
    }
    bool operator>(const std::string num) const
    {
        if(!(*this == num) && !(*this < num)) return true;
        return false;    }
    bool operator>(const long long num) const
    {
        if(!(*this == num) && !(*this < num)) return true;
        return false;    }
    bool operator>(const unsigned long long num) const
    {
        if(!(*this == num) && !(*this < num)) return true;
        return false;
    }
    bool operator>(const float num) const
    {
        if(!(*this == num) && !(*this < num)) return true;
        return false;
    }
    bool operator>(const double num) const
    {
        if(!(*this == num) && !(*this < num)) return true;
        return false;
    }
    bool operator>(const long double num) const
    {
        if(!(*this == num) && !(*this < num)) return true;
        return false;
    }
    friend bool operator>(const int B1, const bigInt_t B2); 
    friend bool operator>(const std::string B1, const bigInt_t B2); 
    friend bool operator>(const long long B1, const bigInt_t B2); 
    friend bool operator>(const unsigned long long B1, const bigInt_t B2); 
    friend bool operator>(const float B1, const bigInt_t B2); 
    friend bool operator>(const double B1, const bigInt_t B2); 
    friend bool operator>(const long double B1, const bigInt_t B2);
    //operator: <=
    bool operator<=(const bigInt_t num) const
    {  
        return (*this < num || *this == num);
    }
    bool operator<=(const int num) const
    {
        return (*this < num || *this == num);
    }
    bool operator<=(const std::string num) const
    {
        return (*this < num || *this == num);
    }
    bool operator<=(const long long num) const
    {
        return (*this < num || *this == num);
    }
    bool operator<=(const unsigned long long num) const
    {
        return (*this < num || *this == num);
    }
    bool operator<=(const float num) const
    {
        return (*this < num || *this == num);
    }
    bool operator<=(const double num) const
    {
        return (*this < num || *this == num);
    }
    bool operator<=(const long double num) const
    {
        return (*this < num || *this == num);
    }
    friend bool operator<=(const int B1, const bigInt_t B2); 
    friend bool operator<=(const std::string B1, const bigInt_t B2); 
    friend bool operator<=(const long long B1, const bigInt_t B2); 
    friend bool operator<=(const unsigned long long B1, const bigInt_t B2); 
    friend bool operator<=(const float B1, const bigInt_t B2); 
    friend bool operator<=(const double B1, const bigInt_t B2); 
    friend bool operator<=(const long double B1, const bigInt_t B2); 
    //operator: >=
    bool operator>=(const bigInt_t num) const
    {
        return (*this > num || *this == num);
    }
    bool operator>=(const int num) const
    {
        return (*this > num || *this == num);
    }
    bool operator>=(const std::string num) const
    {
        return (*this > num || *this == num);
    }
    bool operator>=(const long long num) const
    {
        return (*this > num || *this == num);
    }
    bool operator>=(const unsigned long long num) const
    {
        return (*this > num || *this == num);
    }
    bool operator>=(const float num) const
    {
        return (*this > num || *this == num);
    }
    bool operator>=(const double num) const
    {
        return (*this > num || *this == num);
    }
    bool operator>=(const long double num) const
    {
        return (*this > num || *this == num);
    }
    friend bool operator>=(const int B1, const bigInt_t B2); 
    friend bool operator>=(const std::string B1, const bigInt_t B2); 
    friend bool operator>=(const long long B1, const bigInt_t B2); 
    friend bool operator>=(const unsigned long long B1, const bigInt_t B2); 
    friend bool operator>=(const float B1, const bigInt_t B2); 
    friend bool operator>=(const double B1, const bigInt_t B2); 
    friend bool operator>=(const long double B1, const bigInt_t B2); 

            //UNARY OPERATORS:
    //operator: ++
    bigInt_t operator++()
    {
        *this = *this + 1;
        return *this;
    }
    bigInt_t operator++(int)
    {
        bigInt_t old = *this;
        operator++();
        return old;
    }
    //operator: --
    bigInt_t operator--()
    {
        return *this - 1;    
    }
    bigInt_t operator--(int)
    {
        bigInt_t old = *this;
        operator--();
        return old;
    }
                //ASSIGMENT OPERATORS 2:
    //operator: +=
    bigInt_t operator+=(const bigInt_t num)
    {
        *this = *this + num;
        return *this;
    }
    bigInt_t operator+=(const int num)
    {
        *this = *this + num;
        return *this;
    }
    bigInt_t operator+=(const std::string num)
    {
        *this = *this + num;
        return *this;
    }
    bigInt_t operator+=(const long long num)
    {
        *this = *this + num;
        return *this;
    }
    bigInt_t operator+=(const unsigned long long num)
    {
        *this = *this + num;
        return *this;
    }
    bigInt_t operator+=(const float num)
    {
        *this = *this + num;
        return *this;
    }
    bigInt_t operator+=(const double num)
    {
        *this = *this + num;
        return *this;
    }
    bigInt_t operator+=(const long double num)
    {
        *this = *this + num;
        return *this;
    }
    friend bigInt_t operator+=(const int B1, const bigInt_t B2);
    friend bigInt_t operator+=(const long long, const bigInt_t B2);
    friend bigInt_t operator+=(const unsigned long long B1, const bigInt_t B2);
    friend bigInt_t operator+=(const float B1, const bigInt_t B2);
    friend bigInt_t operator+=(const double B1, const bigInt_t B2);
    friend bigInt_t operator+=(const long double B1, const bigInt_t B2);
    //operator: -=
    bigInt_t operator-=(const bigInt_t num)
    {
        *this = *this - num;
        return *this;
    }
    bigInt_t operator-=(const int num)
    {
        return *this - num;
    }
    bigInt_t operator-=(const std::string num)
    {
        return *this - num;
    }
    bigInt_t operator-=(const long long num)
    {
        return *this - num;
    }
    bigInt_t operator-=(const unsigned long long num)
    {
        return *this - num;
    }
    bigInt_t operator-=(const float num)
    {
        *this = *this - num;
        return *this;
    }
    bigInt_t operator-=(const double num)
    {
        *this = *this - num;
        return *this;
    }
    bigInt_t operator-=(const long double num)
    {
        *this = *this - num;
        return *this;
    }
    friend bigInt_t operator-=(const int B1, const bigInt_t B2);
    friend bigInt_t operator-=(const long long, const bigInt_t B2);
    friend bigInt_t operator-=(const unsigned long long B1, const bigInt_t B2);
    friend bigInt_t operator-=(const float B1, const bigInt_t B2);
    friend bigInt_t operator-=(const double B1, const bigInt_t B2);
    friend bigInt_t operator-=(const long double B1, const bigInt_t B2);
    //operator *=
    bigInt_t operator*=(const bigInt_t num)
    {
        *this = *this * num;
        return *this;
    }
    bigInt_t operator*=(const int num)
    {
        *this = *this * num;
        return *this;
    }
    bigInt_t operator*=(const std::string num)
    {
        *this = *this * num;
        return *this;
    }
    bigInt_t operator*=(const long long num)
    {
        *this = *this * num;
        return *this;
    }
    bigInt_t operator*=(const unsigned long long num)
    {
        *this = *this * num;
        return *this;
    }
    bigInt_t operator*=(const float num)
    {
        *this = *this * num;
        return *this;
    }
    bigInt_t operator*=(const double num)
    {
        *this = *this * num;
        return *this;
    }
    bigInt_t operator*=(const long double num)
    {
        *this = *this * num;
        return *this;
    }
    friend bigInt_t operator*=(const int B1, const bigInt_t B2);
    friend bigInt_t operator*=(const long long, const bigInt_t B2);
    friend bigInt_t operator*=(const unsigned long long B1, const bigInt_t B2);
    friend bigInt_t operator*=(const float B1, const bigInt_t B2);
    friend bigInt_t operator*=(const double B1, const bigInt_t B2);
    friend bigInt_t operator*=(const long double B1, const bigInt_t B2);
    //operator: /=
    bigInt_t operator/=(const int num)
    {
        *this = *this / num;
        return *this;
    }
    bigInt_t operator/=(const std::string num)
    {
        *this = *this / num;
        return *this;
    }
    bigInt_t operator/=(const long long num)
    {
        *this = *this / num;
        return *this;
    }
    bigInt_t operator/=(const unsigned long long num)
    {
        *this = *this / num;
        return *this;
    }
    bigInt_t operator/=(const float num)
    {
        *this = *this / num;
        return *this;
    }
    bigInt_t operator/=(const double num)
    {
        *this = *this / num;
        return *this;
    }
    bigInt_t operator/=(const long double num)
    {
        *this = *this / num;
        return *this;
    }
    friend bigInt_t operator/=(const int B1, const bigInt_t B2);
    friend bigInt_t operator/=(const long long, const bigInt_t B2);
    friend bigInt_t operator/=(const unsigned long long B1, const bigInt_t B2);
    friend bigInt_t operator/=(const float B1, const bigInt_t B2);
    friend bigInt_t operator/=(const double B1, const bigInt_t B2);
    friend bigInt_t operator/=(const long double B1, const bigInt_t B2);
    //operator: +
    const bigInt_t operator+(const bigInt_t Num) const
    {
        bigInt_t num = Num;
        bigInt_t tNum = *this;
        bigInt_t result;

        if(this->isPositive == num.isPositive)
        {
            result.isPositive = this->isPositive;

            num.isPositive = true;
            tNum.isPositive = true;

            std::string number_1 = tNum.number;
            std::string number_2 = num.number;

            std::string::size_type numOfD_1 = getNumOfDec(number_1);
            std::string::size_type numOfD_2 = getNumOfDec(number_2);
            std::string::size_type maxDec = std::max(numOfD_1, numOfD_2);

            removeDot(number_1);
            removeDot(number_2);
            
            if (numOfD_1 < maxDec) number_1.append(maxDec - numOfD_1, '0');  
            if (numOfD_2 < maxDec) number_2.append(maxDec - numOfD_2, '0');

            std::reverse(number_1.begin(), number_1.end());
            std::reverse(number_2.begin(), number_2.end());

            std::string::size_type sizeOfMax = std::max(number_1.size(), number_2.size());

            std::string result_s;
            std::string::size_type remainder = 0;

            for (std::string::size_type i = 0; i < sizeOfMax; ++i) 
            {
                std::string::size_type digit1 = (i < number_1.size()) ?
                std::string::size_type(charToInt(number_1.at(i))) : std::string::size_type(0);
                
                std::string::size_type digit2 = (i < number_2.size()) ?
                std::string::size_type(charToInt(number_2.at(i))) : std::string::size_type(0);

                std::string::size_type sum = digit1 + digit2 + remainder;
                remainder = sum / 10;
                result_s.push_back(intToChar(int(sum) % 10));
            }
            if (remainder != 0) result_s.push_back(intToChar(int(remainder)));

            std::reverse(result_s.begin(), result_s.end());

            if (maxDec > 0) result_s.insert(result_s.size() - maxDec, 1, '.');
    
            result.number = result_s;
        }
        else
        {
            bool firstSign = tNum.isPositive;
            tNum.isPositive = num.isPositive = true;
            if(firstSign)
            {
                if(tNum >= num)
                {
                    result = tNum - num;
                    result.isPositive = true;
                }
                else
                {
                    result = num - tNum;
                    result.isPositive = false;
                }
            } 
            else
            {   
                if(tNum >= num)
                {
                    result = tNum - num;
                    result.isPositive = false;
                }
                else
                {
                    result = (num - tNum);
                    result.isPositive = true;
                }
            }
        }
        formatNumber(result);
        return result;
    }
    const bigInt_t operator+(const int num) const
    {
        return *this + bigInt_t(num);
    }
    const bigInt_t operator+(const std::string num) const
    {
        return *this + bigInt_t(num);
    }
    const bigInt_t operator+(const long long num) const
    {
        return *this + bigInt_t(num);
    }
    const bigInt_t operator+(const unsigned long long num) const
    {
        return *this + bigInt_t(num);
    }
    const bigInt_t operator+(const float num) const
    {
        return *this + bigInt_t(num);
    }
    const bigInt_t operator+(const double num) const
    {
        return *this + bigInt_t(num);
    }
    const bigInt_t operator+(const long double num) const
    {
        return *this + bigInt_t(num);
    }
    friend bigInt_t operator+(const int B1, const bigInt_t B2);
    friend bigInt_t operator+(const std::string B1, const bigInt_t B2);
    friend bigInt_t operator+(const long long B1, const bigInt_t B2);
    friend bigInt_t operator+(const unsigned long long B1, const bigInt_t B2);
    friend bigInt_t operator+(const float B1, const bigInt_t B2);
    friend bigInt_t operator+(const double B1, const bigInt_t B2);
    friend bigInt_t operator+(const long double B1, const bigInt_t B2);
    bigInt_t operator+() const
    {
        return *this;
    }
    //operator: -
    const bigInt_t operator-(const bigInt_t Num) const
    {            
        bigInt_t result;
        bigInt_t thisNumber = *this, num = Num;
        if(this->isPositive == num.isPositive)
        {
            //handle number sign
            bool areNumberPositive = thisNumber.isPositive;
            num.isPositive = thisNumber.isPositive = true;
            
            //handle number and result positivity
            std::string number_1, number_2;
            if(thisNumber > num)
            {
                result.isPositive = true;
                number_1 = thisNumber.number;
                number_2 = num.number;
            } 
            else
            {
                result.isPositive = false;
                number_1 = num.number;
                number_2 = thisNumber.number;
            }
            if(!areNumberPositive) result.isPositive = !result.isPositive;
            

            //handle dots
            std::string::size_type
             nOfD1 = getNumOfDec(number_1),
             nOfD2 = getNumOfDec(number_2),
             maxDec = std::max(nOfD1, nOfD2);
            
            removeDot(number_1);
            removeDot(number_2);

            if(nOfD1 < maxDec) number_1.append(maxDec - nOfD1, '0');
            if(nOfD2 < maxDec) number_2.append(maxDec - nOfD2, '0');
            //reverse
            std::reverse(number_1.begin(), number_1.end());
            std::reverse(number_2.begin(), number_2.end());
            //size of min and max
            std::string::size_type sizeOfMin = number_2.size();
            std::string::size_type sizeOfMax = number_1.size();
            //prepare
            std::string result_s = "\0";
            int remainder = 0;
            for(std::string::size_type i = 0; i < sizeOfMax; ++i)
            {
                int tResult = charToInt(number_1.at(i));
                if (i < sizeOfMin) tResult -= charToInt(number_2.at(i));
                tResult -= remainder;
                if(tResult < 0)
                {
                    tResult += 10;
                    remainder = 1;
                }
                else remainder = 0;

                result_s.push_back(intToChar(tResult));
            }
            //handle remainder
            std::reverse(result_s.begin(), result_s.end());
            if (maxDec > 0) result_s.insert(result_s.size() - maxDec, 1, '.');
            result.number = result_s;
        }
        else
        {
            bool isFirstNumberPositive;
            isFirstNumberPositive = this->isPositive;
            thisNumber.isPositive = num.isPositive = true;
            result = thisNumber + num;
            if(!isFirstNumberPositive)
            result = -result;
        }
        formatNumber(result);
        return result;
    }
    const bigInt_t operator-(const int num) const
    {
        return *this - bigInt_t(num);
    }
    const bigInt_t operator-(const std::string num) const
    {
        return *this - bigInt_t(num);
    }
    const bigInt_t operator-(const long long num) const
    {
        return *this - bigInt_t(num);
    }
    const bigInt_t operator-(const unsigned long long num) const
    {
        return *this - bigInt_t(num);
    }
    const bigInt_t operator-(const float num) const
    {
        return *this - bigInt_t(num);
    }
    const bigInt_t operator-(const double num) const
    {
        return *this - bigInt_t(num);
    }
    const bigInt_t operator-(const long double num) const
    {
        return *this - bigInt_t(num);
    }
    friend bigInt_t operator-(const int B1, const bigInt_t B2);
    friend bigInt_t operator-(const std::string B1, const bigInt_t B2);
    friend bigInt_t operator-(const long long B1, const bigInt_t B2);
    friend bigInt_t operator-(const unsigned long long B1, const bigInt_t B2);
    friend bigInt_t operator-(const float B1, const bigInt_t B2);
    friend bigInt_t operator-(const double B1, const bigInt_t B2);
    friend bigInt_t operator-(const long double B1, const bigInt_t B2);
    const bigInt_t operator-() const
    {
        bigInt_t result = *this;
        result.isPositive = !this->isPositive;
        return result;
    }
    //operator: *
    const bigInt_t operator*(const bigInt_t &tNum) const
    {
        bigInt_t num = tNum;
        bigInt_t result;
        //handle 0
        if(*this == 0 || num == 0)
        {
            result = 0;
            return 0;
        }
        //handle positivity
        result.isPositive = (this->isPositive == num.isPositive);
        //get bigger and smaller num
        std::string num_1, num_2;
        if(this->number.size() <= num.number.size())
        {
            num_1 = this->number;
            num_2 = num.number;
        }
        else
        {
            num_1 = num.number;
            num_2 = this->number;
        }
        const std::string::size_type numOfD = (getNumOfDec(num_1) + getNumOfDec(num_2));

        removeZerosAndDots(num_1);
        removeZerosAndDots(num_2);

        const std::string::size_type sizeOfMin = num_1.size(), sizeOfMax = num_2.size();
        //reverse
        std::reverse(num_1.begin(), num_1.end());
        std::reverse(num_2.begin(), num_2.end());
        bigInt_t result_T = 0;
        int curr1 = 0, curr2 = 0;
        for(std::string::size_type i = 0; i < sizeOfMin; i++)
        {
            curr1 = charToInt(num_1.at(i));
            std::string result_s_T = "\0";
            int remainder = 0, t = 0;
            for(std::string::size_type j = 0; j < sizeOfMax; j++)
            {
                curr2 = charToInt(num_2.at(j));
                t = curr1 * curr2 + remainder;
                remainder = t / 10;
                result_s_T.push_back(intToChar(t % 10));
            }
            if(remainder != 0) result_s_T.push_back(intToChar(remainder));

            std::reverse(result_s_T.begin(), result_s_T.end());
            for(std::string::size_type k = 0; k < i; k++)
            {
                result_s_T.push_back('0');
            }
            result_T += result_s_T;
        }
        if(numOfD > 0)
        {
            if(numOfD >= result_T.number.size())
            {
                result_T.number.insert(0, numOfD - result_T.number.size() + 1, '0');
                result_T.number.insert(1, 1, '.');
            }
            else
            {
                result_T.number.insert(result_T.number.size() - numOfD, 1, '.');
            }
        }
        result.number = result_T.number;
        formatNumber(result);
        return result;
    }
    const bigInt_t operator*(const int num) const
    {
        return *this * bigInt_t(num);
    }
    const bigInt_t operator*(const std::string num) const
    {
        return *this * bigInt_t(num);
    }
    const bigInt_t operator*(const long long num) const
    {
        return *this * bigInt_t(num);
    }
    const bigInt_t operator*(const unsigned long long num) const
    {
        return *this * bigInt_t(num);
    }
    const bigInt_t operator*(const float num) const
    {
        return *this * bigInt_t(num);
    }
    const bigInt_t operator*(const double num) const
    {
        return *this * bigInt_t(num);
    }
    const bigInt_t operator*(const long double num) const
    {
        return *this * bigInt_t(num);
    }
    friend bigInt_t operator*(const int B1, const bigInt_t B2);
    friend bigInt_t operator*(const std::string B1, const bigInt_t B2);
    friend bigInt_t operator*(const long long B1, const bigInt_t B2);
    friend bigInt_t operator*(const unsigned long long B1, const bigInt_t B2);
    friend bigInt_t operator*(const float B1, const bigInt_t B2);
    friend bigInt_t operator*(const double B1, const bigInt_t B2);
    friend bigInt_t operator*(const long double B1, const bigInt_t B2);
    //operator: /
    const bigInt_t operator/(const bigInt_t num) const
    {
        //handle 0
        assert((num != 0 && *this != 0) && "Divison with zero is impossible.");
        //get result positivity
        bigInt_t result = 0;
        result.isPositive = (this->isPositive == num.isPositive);
        //prepare
        bigInt_t number1 = this->number;
        bigInt_t number2 = num.number;
        std::string result_s = "\0";        
        //LOGIC
        int i = 0;

        int numOfDecimals = 7;

        bool hasDot = false;
        // std::cout << "Pre while0" << std::endl;
        // while(number1 < number2)
        // {
        //     i++;
        //     number1 *= 10;
        // }
        // if(i >= numOfDecimals) return bigInt_t(0);
        // result_s.append(i, '0');
        // std::cout << "Posle while0" << std::endl;
        // if(i == 1)
        // {
        //     result_s.push_back('.');
        //     hasDot = true;
        // }
        // else if(i > 0)
        // {
        //     if(!hasDot){
        //     result_s.insert(1, 1, '.');
        //     hasDot = true;}
        // }
        while(i < numOfDecimals)
        {    
            i++;
            while(number1 < number2)
            {            i++;

                if(!hasDot)
                {
                    result_s.push_back('.');
                    hasDot = true;
                }
                else result_s.push_back('0');

                number1 *= 10;
                if(i == numOfDecimals)
                {
                    break;
                }
            }
            if(number1 == number2)
            {
                result_s.push_back('1');
                break;
            }

            bigInt_t j = 1;
            while(number2 * (j+100000000000000) <= number1)//mrzi me da ovo automatizujem sad
            {
                j+=100000000000000;
            }
            while(number2 * (j+100000000000) <= number1)
            {
                j+=100000000000;
            }
            while(number2 * (j+10000000000) <= number1)
            {
                j+=10000000000;
            }
            while(number2 * (j+1000000000) <= number1)
            {
                j+=1000000000;
            }
            while(number2 * (j+100000000) <= number1)
            {
                j+=100000000;
            }
            while(number2 * (j+10000000) <= number1)
            {
                j+=10000000;
            }
            while(number2 * (j+1000000) <= number1)
            {
                j+=1000000;
            }
            while(number2 * (j+100000) <= number1)
            {
                j+=100000;
            }
            while(number2 * (j+10000) <= number1)
            {
                j+=10000;
            }
            while(number2 * (j+1000) <= number1)
            {
                j+=1000;
            }
            while(number2 * (j+100) <= number1)
            {
                j+=100;
            }
            while(number2 * (j+10) <= number1)
            {
                j+=10;
            }
            while(number2 * (j+1) <= number1)
            {
                j++;
            }
            std::cout << "f";
            result_s.append(toString<bigInt_t>(j));
            if(!hasDot)
            {
                result_s.push_back('.');
                hasDot = true;
            }
            number1 -= (number2 * j);
            number1 *= 10;
            if(number1 == 0)
            {
                break;
            }
        }

        if(result_s.size() > 0)
        if(result_s.at(result_s.size() - 1) == '.')
        {
            result_s.pop_back();
        }

        if(i == numOfDecimals)
        {
            if((charToInt(result_s.at(result_s.size() - 1)) > 4) && (charToInt(result_s.at(result_s.size() - 2)) < 9))
            {
                result_s.at(result_s.size() - 2) = intToChar(charToInt(result_s.at(result_s.size() - 2)) + 1);
            }
            result_s.pop_back();
        }

        result.number = result_s;
        //FORMAT AND RETURN
        formatNumber(result);
        return result;
    }
    const bigInt_t operator/(const int num) const
    {
        return *this / bigInt_t(num);
    }
    const bigInt_t operator/(const std::string num) const
    {
        return *this / bigInt_t(num);
    }
    const bigInt_t operator/(const long long num) const
    {
        return *this / bigInt_t(num);
    }
    const bigInt_t operator/(const unsigned long long num) const
    {
        return *this / bigInt_t(num);
    }
    const bigInt_t operator/(const float num) const
    {
        return *this / bigInt_t(num);
    }
    const bigInt_t operator/(const double num) const
    {
        return *this / bigInt_t(num);
    }
    const bigInt_t operator/(const long double num) const
    {
        return *this / bigInt_t(num);
    }
    friend bigInt_t operator/(const int B1, const bigInt_t B2);
    friend bigInt_t operator/(const std::string B1, const bigInt_t B2);
    friend bigInt_t operator/(const long long B1, const bigInt_t B2);
    friend bigInt_t operator/(const unsigned long long B1, const bigInt_t B2);
    friend bigInt_t operator/(const float B1, const bigInt_t B2);
    friend bigInt_t operator/(const double B1, const bigInt_t B2);
    friend bigInt_t operator/(const long double B1, const bigInt_t B2);
};

namespace big_Int_t
{
    bigInt_t min(const bigInt_t a, const bigInt_t b)
{
    if(b < a) return b;
    return a;
}
    bigInt_t max(const bigInt_t a, const bigInt_t b)
{
    if(b > a) return b;
    return a;
}
}
//operator: +
bigInt_t operator+(const int B1, const bigInt_t B2)
{
    return bigInt_t(B1) + B2;
}
bigInt_t operator+(const std::string B1, const bigInt_t B2)
{
    return bigInt_t(B1) + B2;
}
bigInt_t operator+(const long long B1, const bigInt_t B2)
{
    return bigInt_t(B1) + B2;
}
bigInt_t operator+(const unsigned long long B1, const bigInt_t B2)
{
    return bigInt_t(B1) + B2;
}
bigInt_t operator+(const float B1, const bigInt_t B2)
{
    return bigInt_t(B1) + B2;
}
bigInt_t operator+(const double B1, const bigInt_t B2)
{
    return bigInt_t(B1) + B2;
}
bigInt_t operator+(const long double B1, const bigInt_t B2)
{
    return bigInt_t(B1) + B2;
}
//operator: -
bigInt_t operator-(const int B1, const bigInt_t B2)
{
    return bigInt_t(B1) - B2;
}
bigInt_t operator-(const std::string B1, const bigInt_t B2)
{
    return bigInt_t(B1) - B2;
}
bigInt_t operator-(const long long B1, const bigInt_t B2)
{
    return bigInt_t(B1) - B2;
}
bigInt_t operator-(const unsigned long long B1, const bigInt_t B2)
{
    return bigInt_t(B1) - B2;
}
bigInt_t operator-(const float B1, const bigInt_t B2)
{
    return bigInt_t(B1) - B2;
}
bigInt_t operator-(const double B1, const bigInt_t B2)
{
    return bigInt_t(B1) - B2;
}
bigInt_t operator-(const long double B1, const bigInt_t B2)
{
    return bigInt_t(B1) - B2;
}
//operator: *
bigInt_t operator*(const int B1, const bigInt_t B2)
{
    return bigInt_t(B1) * B2;
}
bigInt_t operator*(const std::string B1, const bigInt_t B2)
{
    return bigInt_t(B1) * B2;
}
bigInt_t operator*(const long long B1, const bigInt_t B2)
{
    return bigInt_t(B1) * B2;
}
bigInt_t operator*(const unsigned long long B1, const bigInt_t B2)
{
    return bigInt_t(B1) * B2;
}
bigInt_t operator*(const float B1, const bigInt_t B2)
{
    return bigInt_t(B1) * B2;
}
bigInt_t operator*(const double B1, const bigInt_t B2)
{
    return bigInt_t(B1) * B2;
}
bigInt_t operator*(const long double B1, const bigInt_t B2)
{
    return bigInt_t(B1) * B2;
}
//operator: /
bigInt_t operator/(const int B1, const bigInt_t B2)
{
    return bigInt_t(B1) / B2;
}
bigInt_t operator/(const std::string B1, const bigInt_t B2)
{
    return bigInt_t(B1) / B2;
}
bigInt_t operator/(const long long B1, const bigInt_t B2)
{
    return bigInt_t(B1) / B2;
}
bigInt_t operator/(const unsigned long long B1, const bigInt_t B2)
{
    return bigInt_t(B1) / B2;
}
bigInt_t operator/(const float B1, const bigInt_t B2)
{
    return bigInt_t(B1) / B2;
}
bigInt_t operator/(const double B1, const bigInt_t B2)
{
    return bigInt_t(B1) / B2;
}
bigInt_t operator/(const long double B1, const bigInt_t B2)
{
    return bigInt_t(B1) / B2;
}
//operator: +=
bigInt_t operator+=(int B1, const bigInt_t B2)
{
    B1 = B1 + B2;
    return B1;
}
bigInt_t operator+=(long long B1, const bigInt_t B2)
{
    B1 = B1 + B2;
    return B1;
}
bigInt_t operator+=(unsigned long long B1, const bigInt_t B2)
{
    B1 = B1 + B2;
    return B1;
}
bigInt_t operator+=(float B1, const bigInt_t B2)
{
    B1 = B1 + B2;
    return B1;
}
bigInt_t operator+=(double B1, const bigInt_t B2)
{
    B1 = B1 + B2;
    return B1;
}
bigInt_t operator+=(long double B1, const bigInt_t B2)
{
    B1 = B1 + B2;
    return B1;
}
//operator -=
bigInt_t operator-=(int B1, const bigInt_t B2)
{
    B1 = B1 - B2;
    return B1;
}
bigInt_t operator-=(long long B1, const bigInt_t B2)
{
    B1 = B1 - B2;
    return B1;
}
bigInt_t operator-=(unsigned long long B1, const bigInt_t B2)
{
    B1 = B1 - B2;
    return B1;
}
bigInt_t operator-=(float B1, const bigInt_t B2)
{
    B1 = B1 - B2;
    return B1;
}
bigInt_t operator-=(double B1, const bigInt_t B2)
{
    B1 = B1 - B2;
    return B1;
}
bigInt_t operator-=(long double B1, const bigInt_t B2)
{
    B1 = B1 - B2;
    return B1;
}
//operator: *=
bigInt_t operator*=(int B1, const bigInt_t B2)
{
    B1 = B1 * B2;
    return B1;
}
bigInt_t operator*=(long long B1, const bigInt_t B2)
{
    B1 = B1 * B2;
    return B1;
}
bigInt_t operator*=(unsigned long long B1, const bigInt_t B2)
{
    B1 = B1 * B2;
    return B1;
}
bigInt_t operator*=(float B1, const bigInt_t B2)
{
    B1 = B1 * B2;
    return B1;
}
bigInt_t operator*=(double B1, const bigInt_t B2)
{
    B1 = B1 * B2;
    return B1;
}
bigInt_t operator*=(long double B1, const bigInt_t B2)
{
    B1 = B1 * B2;
    return B1;
}
//operator: /=
bigInt_t operator/=(int B1, const bigInt_t B2)
{
    B1 = B1 / B2;
    return B1;
}
bigInt_t operator/=(long long B1, const bigInt_t B2)
{
    B1 = B1 / B2;
    return B1;
}
bigInt_t operator/=(unsigned long long B1, const bigInt_t B2)
{
    B1 = B1 / B2;
    return B1;
}
bigInt_t operator/=(float B1, const bigInt_t B2)
{
    B1 = B1 / B2;
    return B1;
}
bigInt_t operator/=(double B1, const bigInt_t B2)
{
    B1 = B1 / B2;
    return B1;
}
bigInt_t operator/=(long double B1, const bigInt_t B2)
{
    B1 = B1 / B2;
    return B1;
}
//operator: ==
bool operator==(const int B1, const bigInt_t B2)
{
    return bigInt_t(B1) == B2;
}
bool operator==(const std::string B1, const bigInt_t B2)
{
    return bigInt_t(B1) == B2;
}
bool operator==(const long long B1, const bigInt_t B2)
{
    return bigInt_t(B1) == B2;
}
bool operator==(const unsigned long long B1, const bigInt_t B2)
{
    return bigInt_t(B1) == B2;
}
bool operator==(const float B1, const bigInt_t B2)
{
    return bigInt_t(B1) == B2;
}
bool operator==(const double B1, const bigInt_t B2)
{
    return bigInt_t(B1) == B2;
}
bool operator==(const long double B1, const bigInt_t B2)
{
    return bigInt_t(B1) == B2;
}
//operator: !=
bool operator!=(const int B1, const bigInt_t B2)
{
    return !(bigInt_t(B1) == B2);
}
bool operator!=(const std::string B1, const bigInt_t B2)
{
    return !(bigInt_t(B1) == B2);
}
bool operator!=(const long long B1, const bigInt_t B2)
{
    return !(bigInt_t(B1) == B2);
}
bool operator!=(const unsigned long long B1, const bigInt_t B2)
{
    return !(bigInt_t(B1) == B2);
}
bool operator!=(const float B1, const bigInt_t B2)
{
    return !(bigInt_t(B1) == B2);
}
bool operator!=(const double B1, const bigInt_t B2)
{
    return !(bigInt_t(B1) == B2);
}
bool operator!=(const long double B1, const bigInt_t B2)
{
    return !(bigInt_t(B1) == B2);
}
//operator: <
bool operator<(const int B1, const bigInt_t B2)
{
    return bigInt_t(B1) < B2;
}
bool operator<(const std::string B1, const bigInt_t B2)
{
    return bigInt_t(B1) < B2;
}
bool operator<(const long long B1, const bigInt_t B2)
{
    return bigInt_t(B1) < B2;
}
bool operator<(const unsigned long long B1, const bigInt_t B2)
{
    return bigInt_t(B1) < B2;
}
bool operator<(const float B1, const bigInt_t B2)
{
    return bigInt_t(B1) < B2;
}
bool operator<(const double B1, const bigInt_t B2)
{
    return bigInt_t(B1) < B2;
}
bool operator<(const long double B1, const bigInt_t B2)
{
    return bigInt_t(B1) < B2;
}
//operator: >
bool operator>(const int B1, const bigInt_t B2)
{
        if(!(bigInt_t(B1) == B2) && !(bigInt_t(B1) < B2)) return true;
        return false;
}
bool operator>(const std::string B1, const bigInt_t B2)
{
        if(!(bigInt_t(B1) == B2) && !(bigInt_t(B1) < B2)) return true;
        return false;
}
bool operator>(const long long B1, const bigInt_t B2)
{
        if(!(bigInt_t(B1) == B2) && !(bigInt_t(B1) < B2)) return true;
        return false;
}
bool operator>(const unsigned long long B1, const bigInt_t B2)
{
        if(!(bigInt_t(B1) == B2) && !(bigInt_t(B1) < B2)) return true;
        return false;
}
bool operator>(const float B1, const bigInt_t B2)
{
        if(!(bigInt_t(B1) == B2) && !(bigInt_t(B1) < B2)) return true;
        return false;
}
bool operator>(const double B1, const bigInt_t B2)
{
        if(!(bigInt_t(B1) == B2) && !(bigInt_t(B1) < B2)) return true;
        return false;
}
bool operator>(const long double B1, const bigInt_t B2)
{
        if(!(bigInt_t(B1) == B2) && !(bigInt_t(B1) < B2)) return true;
        return false;
}
//operator: <=
bool operator<=(const int B1, const bigInt_t B2)
{
    return (bigInt_t(B1) < B2 || bigInt_t(B1) == B2);
} 
bool operator<=(const std::string B1, const bigInt_t B2)
{
    return (bigInt_t(B1) < B2 || bigInt_t(B1) == B2);
} 
bool operator<=(const long long B1, const bigInt_t B2)
{
    return (bigInt_t(B1) < B2 || bigInt_t(B1) == B2);
} 
bool operator<=(const unsigned long long B1, const bigInt_t B2)
{
    return (bigInt_t(B1) < B2 || bigInt_t(B1) == B2);
} 
bool operator<=(const float B1, const bigInt_t B2)
{
    return (bigInt_t(B1) < B2 || bigInt_t(B1) == B2);
} 
bool operator<=(const double B1, const bigInt_t B2)
{
    return (bigInt_t(B1) < B2 || bigInt_t(B1) == B2);
} 
bool operator<=(const long double B1, const bigInt_t B2)
{
    return (bigInt_t(B1) < B2 || bigInt_t(B1) == B2);
} 
//operator: >=
bool operator>=(const int B1, const bigInt_t B2)
{
    return (bigInt_t(B1) > B2 || bigInt_t(B1) == B2);
} 
bool operator>=(const std::string B1, const bigInt_t B2)
{
    return (bigInt_t(B1) > B2 || bigInt_t(B1) == B2);
} 
bool operator>=(const long long B1, const bigInt_t B2)
{
    return (bigInt_t(B1) > B2 || bigInt_t(B1) == B2);
} 
bool operator>=(const unsigned long long B1, const bigInt_t B2)
{
    return (bigInt_t(B1) > B2 || bigInt_t(B1) == B2);
} 
bool operator>=(const float B1, const bigInt_t B2)
{
    return (bigInt_t(B1) > B2 || bigInt_t(B1) == B2);
} 
bool operator>=(const double B1, const bigInt_t B2)
{
    return (bigInt_t(B1) > B2 || bigInt_t(B1) == B2);
} 
bool operator>=(const long double B1, const bigInt_t B2)
{
    return (bigInt_t(B1) > B2 || bigInt_t(B1) == B2);
} 
