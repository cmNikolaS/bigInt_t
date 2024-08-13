#pragma once
#include <assert.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>

class bigInt_t
{
    private:
    std::string number = "0";
    bool isPositive = true;

    inline int charToInt(const char c) const
    {
        return c - '0';
    }

    inline char intToChar(const int i) const
    {
        return i + '0';
    }

    void takeNumber(const std::string NUMBER)
    {
        if(NUMBER[0] == '-')
        {
            isPositive = false;
            number = NUMBER.substr(1);
        }
        else if(NUMBER[0] == '+')
        {
            isPositive = true;
            number = NUMBER.substr(1);
        }
        else
        {
            isPositive = true;
            number = NUMBER;
        }
    }

    void formatNumber(bigInt_t &number) const 
    {

        int i = 0;
        while (i < number.number.size() && number.number[i] == '0')
        {
            ++i;
        }

        if (i == number.number.size())
        {
            number.number = "0";
            number.isPositive = true;
        }
        else
        {
            number.number = number.number.substr(i);
        }
    }

    public:
    //constructors
    bigInt_t()
    {
        number = "0";
        isPositive = true;
    }
    bigInt_t(const int NUMBER)
    {
        takeNumber(std::to_string(NUMBER));
    }
    bigInt_t(const std::string NUMBER)
    {
        takeNumber(NUMBER);
    }
    bigInt_t(const long long NUMBER)
    {
        takeNumber(std::to_string(NUMBER));
    }
    bigInt_t(const unsigned long long NUMBER)
    { 
        takeNumber(std::to_string(NUMBER));
    }
    //operator: int()
    operator int()
    {
        return stoi(number);
    }
    operator long long()
    {
        return stoll(number);
    }
    operator unsigned long long()
    {
        return stoull(number);
    }
    operator std::string()
    {
        std::string toR = "\0";
        if(!isPositive)
        {
            toR.push_back('-');
        }
        toR.append(number);
        return toR;
    }
    //operator: =
    void operator=(const bigInt_t num)
    {
        number = num.number;
        isPositive = num.isPositive;
    }
    void operator=(const int number) 
    { 
        takeNumber(std::to_string(number));
    }
    void operator=(const std::string number) 
    { 
        takeNumber(number);
    }
    void operator=(const long long number)
    {
        takeNumber(std::to_string(number));
    }
    void operator=(const unsigned long long number)
    {
        takeNumber(std::to_string(number));
    }
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
    //operator: ==
    const bool operator==(const bigInt_t number) const
    {
        if(this->isPositive == number.isPositive)
        {
            if(this->number.size() == number.number.size())
            {
                for(int i = 0; i < this->number.size(); i++)
                {
                    if(this->number[i] != number.number[i])
                        { return false; }
                }
                return true;
            }
        }
        return false;
    }
    const bool operator==(const int number) const
    {
        bigInt_t num = number;
        return this->operator==(num);
    }
    const bool operator==(const std::string number) const
    {
        bigInt_t num = number;
        return this->operator==(bigInt_t(number));
    }
    const bool operator==(const long long number) const
    {
        bigInt_t num = number;
        return this->operator==(num);
    }
    const bool operator==(const unsigned long long number) const
    {
        bigInt_t num = number;
        return this->operator==(num);
    }   
    //operator: !=
    const bool operator!=(const bigInt_t number) const
    {
        return !this->operator==(number);
    }
    const bool operator!=(const int number) const
    {
        return !this->operator==(number);
    }
    const bool operator!=(const std::string number) const
    {
        return !this->operator==(number);
    }
    const bool operator!=(const long long number) const
    {
        bigInt_t num = number;
        return !this->operator==(num);
    }
    const bool operator!=(const unsigned long long number) const
    {
        return !this->operator==(number);
    }
    //operator: <
    bool operator<(const bigInt_t number)
    {
        if(this->isPositive != number.isPositive)
        {
            if(number.isPositive == true)
            {
                return true;
            }
        }
        else
        {
            if(number.isPositive == true)
            {
                if(number.number.size() > this->number.size())
                {
                    return true;
                }
                else if (number.number.size() == this->number.size())
                {
                    for(int i = 0; i < number.number.size(); i++)
                    {
                        if(charToInt(number.number[i]) > charToInt(this->number[i]))
                        {
                            return true;
                        }
                    }
                }
            }
            else
            {
                if(number.number.size() < this->number.size())
                {
                    return true;
                }
                else if(number.number.size() == this->number.size())
                {
                    for(int i = 0; i < number.number.size(); i++)
                    {
                        if(charToInt(number.number[i]) < charToInt(this->number[i]))
                        {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
    bool operator<(const int number)
    {
        bigInt_t numberr = number;
        return this->operator<(number);
    }
    bool operator<(const std::string number)
    {
        bigInt_t numberr = number;
        return this->operator<(number);
    }
    bool operator<(const long long number)
    {
        bigInt_t numberr = number;
        return this->operator<(number);
    }
    bool operator<(const unsigned long long number)
    {
        bigInt_t numberr = number;
        return this->operator<(number);
    }
    //operator: >
    bool operator>(const bigInt_t number)
    {
        if(!this->operator==(number))
                    { return !this->operator<(number); }
        return false;
    }
    bool operator>(const int number)
    {
        if(!this->operator==(number))
                    { return !this->operator<(number); }
        return false;
    }
    bool operator>(const std::string number)
    {
        if(!this->operator==(number))
                    { return !this->operator<(number); }
        return false;
    }
    bool operator>(const long long number)
    {
        if(!this->operator==(number))
                    { return !this->operator<(number); }
        return false;
    }
    bool operator>(const unsigned long long number)
    {
        if(!this->operator==(number))
                    { return !this->operator<(number); }
        return false;
    }
    //operator: <=
    bool operator<=(const bigInt_t number)
    {
        if(this->operator<(number) || this->operator==(number))
                        {return true;}
        return false;
    }
    bool operator<=(const int number)
    {
        if(this->operator<(number) || this->operator==(number))
                        {return true;}
        return false;
    }
    bool operator<=(const std::string number)
    {
        if(this->operator<(number) || this->operator==(number))
                        {return true;}
        return false;
    }
    bool operator<=(const long long number)
    {
        if(this->operator<(number) || this->operator==(number))
                        {return true;}
        return false;
    }
    bool operator<=(const unsigned long long number)
    {
        if(this->operator<(number) || this->operator==(number))
                        {return true;}
        return false;
    }
    //operator: >=
    bool operator>=(const bigInt_t number)
    {
        if(this->operator>(number) || this->operator==(number))
                { return true; }
        return false;
    }
    bool operator>=(const int number)
    {
        if(this->operator>(number) || this->operator==(number))
                { return true; }
        return false;
    }
    bool operator>=(const std::string number)
    {
        if(this->operator>(number) || this->operator==(number))
                { return true; }
        return false;
    }
    bool operator>=(const long long number)
    {
        if(this->operator>(number) || this->operator==(number))
                { return true; }
        return false;
    }
    bool operator>=(const unsigned long long number)
    {
        if(this->operator>(number) || this->operator==(number))
                { return true; }
        return false;
    }
    //operator: ++
    bigInt_t operator++()
    {
        return this->operator+(1);
    }
    //operator: --
    bigInt_t operator--()
    {
        return this->operator-(1);
    }
    //operator: +=
    bigInt_t &operator+=(const bigInt_t number)
    {
        this->operator=(this->operator+(number));
        return *this;
    }
    bigInt_t &operator+=(const int number)
    {
        this->operator=(this->operator+(number));
        return *this;
    }
    bigInt_t &operator+=(const std::string number)
    {
        this->operator=(this->operator+(number));
        return *this;
    }
    bigInt_t &operator+=(const long long number)
    {
        this->operator=(this->operator+(number));
        return *this;
    }
    bigInt_t &operator+=(const unsigned long long number)
    {
        this->operator=(this->operator+(number));
        return *this;
    }
    //operator: -=
    bigInt_t &operator-=(const bigInt_t number)
    {
        *this = *this - number;
        return *this;
    }
    bigInt_t &operator-=(const int number)
    {
        *this = *this - number;
        return *this;
    }
    bigInt_t &operator-=(const std::string number)
    {
        *this = *this - number;
        return *this;
    }
    bigInt_t &operator-=(const long long number)
    {
        *this = *this - number;
        return *this;
    }
    bigInt_t &operator-=(const unsigned long long number)
    {
        *this = *this - number;
        return *this;
    }
    //operator *=
    bigInt_t &operator*=(const bigInt_t number)
    {
        *this = *this * number;
        return *this;
    }
    bigInt_t &operator*=(const int number)
    {
        *this = *this * number;
        return *this;
    }
    bigInt_t &operator*=(const std::string number)
    {
        *this = *this * number;
        return *this;
    }
    bigInt_t &operator*=(const long long number)
    {
        *this = *this * number;
        return *this;
    }
    bigInt_t &operator*=(const unsigned long long number)
    {
        *this = *this * number;
        return *this;
    }
    //operator: +
    const bigInt_t operator+(const bigInt_t num) const
    {
        bigInt_t number = num;
        bigInt_t thisNumber = *this;
        if(this->isPositive == number.isPositive)
        {
            bigInt_t result;
            result.isPositive = this->isPositive;
            number.isPositive = true;
            thisNumber.isPositive = true;
            //get smaller and bigger number 
            std::string number_1;
            std::string number_2;
            if(thisNumber >= number)
            {
                number_1 = this->number;
                number_2 = number.number;
            }
            else
            {
                number_2 = this->number;
                number_1 = number.number;
            }
            //reverse it
            std::reverse(number_1.begin(), number_1.end());
            std::reverse(number_2.begin(), number_2.end());
            //get size of smaller and bigger number
            int sizeOfMin = number_2.size();
            int sizeOfMax = number_1.size();
            //get default result
            std::string result_s;
            int remainder = 0;
            //operate
            for(int i = 0; i < sizeOfMax; ++i)
            {
                int tResult = charToInt(number_1[i]) + remainder;
                if(i < sizeOfMin)
                {
                    tResult += charToInt(number_2[i]);
                }
                result_s.push_back(intToChar(tResult % 10));
                remainder = tResult / 10;
            }
            if (remainder != 0)
            {
                result_s.push_back(intToChar(remainder));
            }
            //reverse and set result
            std::reverse(result_s.begin(), result_s.end());
            result.number = result_s;
            //format and return
            formatNumber(result);
            return result;
        }
        else
        {
            bigInt_t result;
            bool firstSign = thisNumber.isPositive;
            thisNumber.isPositive = number.isPositive = true;
            if(firstSign == true)
            {
                if(thisNumber > number)
                {
                    result = thisNumber - number;
                }
                else
                {
                    result = -(number - thisNumber);
                }
            }
            else
            {   
                thisNumber.isPositive = true;
                number.isPositive = true;
                if(thisNumber > number)
                {
                    result.isPositive = false;
                    result = -(thisNumber - number);
                }
                else
                {
                    result.isPositive = true;
                    result = number - thisNumber;                   
                }
            }
            formatNumber(result);
            return result;
        }
    }
    const bigInt_t operator+(const int number) const
    {
        bigInt_t number_ = number;
        return this->operator+(number_);
    }
    const bigInt_t operator+(const std::string number) const
    {
        bigInt_t number_ = number;
        return this->operator+(number_);
    }
    const bigInt_t operator+(const long long number) const
    {
        bigInt_t number_ = number;
        return this->operator+(number_);
    }
    const bigInt_t operator+(const unsigned long long number) const
    {
        bigInt_t number_ = number;
        return this->operator+(number_);
    }
    bigInt_t operator+() const
    {
        return *this;
    }
    //operator: -
    const bigInt_t operator-(const bigInt_t num) const
    {
        bigInt_t thisNumber = *this, number = num;
        if(this->isPositive == number.isPositive)
        {
            bigInt_t result;
            //handle number sign
            bool areNumberPositive = thisNumber.isPositive;
            number.isPositive = thisNumber.isPositive = true;
            if(thisNumber >= number)
            {
                result.isPositive = true;
            }
            else
            {
                result.isPositive = false;
            }
            if(!areNumberPositive)
            {
                result.isPositive = !result.isPositive;
            }
            
            //get smaller and bigger number
            std::string number_1, number_2;
            if (thisNumber >= number)
            {
                number_1 = this->number;
                number_2 = number.number;
            }
            else
            {
                number_1 = number.number;
                number_2 = this->number;
            }
            //reverse
            std::reverse(number_1.begin(), number_1.end());
            std::reverse(number_2.begin(), number_2.end());
            //size of min and max
            int sizeOfMin = number_2.size();
            int sizeOfMax = number_1.size();
            //prepare
            std::string result_s;
            int remainder = 0;
            for(int i = 0; i < sizeOfMax; ++i)
            {
                int tResult = charToInt(number_1[i])-remainder;
                if (i < sizeOfMin)
                {
                    tResult -= charToInt(number_2[i]);
                }
                remainder = 0;
                while(tResult < 0)
                {
                    tResult += 10;
                    remainder++;
                }
                result_s.push_back(intToChar(tResult));
            }
            //handle number
            std::reverse(result_s.begin(), result_s.end());
            result.number = result_s;
            //format and return
            if(remainder != 0)
            {
                std::string num1S(result_s.size(), '0');
                num1S = '1' + num1S;
                bigInt_t numm2 = result_s;
                bigInt_t numm1 = num1S;
                bigInt_t tR(numm1 - numm2);
                result.number = tR.number;
                result.isPositive = !result.isPositive;
            }
            formatNumber(result);
            return result;
        }
        else
        {
            bigInt_t result;
            bool isFirstNumberPositive;
            isFirstNumberPositive = this->isPositive;
            thisNumber.isPositive = number.isPositive = true;

            if(isFirstNumberPositive)
            {
                result = thisNumber + number;
            }
            else
            {
                result = -(thisNumber + number);
            }
            formatNumber(result);
            return result;
        }
    }
    const bigInt_t operator-(const int number) const
    {
        bigInt_t number_ = number;
        return this->operator-(number_);
    }
    const bigInt_t operator-(const std::string number) const
    {
        bigInt_t number_ = number;
        return this->operator-(number_);
    }
    const bigInt_t operator-(const long long number) const
    {
        bigInt_t number_ = number;
        return this->operator-(number_);
    }
    const bigInt_t operator-(unsigned long long number) const
    {
        bigInt_t number_ = number;
        return this->operator-(number_);
    }
    bigInt_t operator-() const
    {
        bigInt_t result = *this;
        result.isPositive = !this->isPositive;
        return result;
    }

    const bigInt_t operator*(const bigInt_t number) const
    {
        bigInt_t result;
        //handle 0
        if(*this == 0 || number == 0)
        {
            result = 0;
            return result;
        }
        //handle positivity
        result.isPositive = (this->isPositive == number.isPositive);
        //get bigger and smaller number
        std::string number_1, number_2;
        if(this->number.size() <= number.number.size())
        {
            number_1 = this->number;
            number_2 = number.number;
        }
        else
        {
            number_1 = number.number;
            number_2 = this->number;
        }
        int sizeOfMin = number_1.size();
        int sizeOfMax = number_2.size();
        //reverse
        std::reverse(number_1.begin(), number_1.end());
        std::reverse(number_2.begin(), number_2.end());

        bigInt_t result_T;
        int k = 0;
        int curr1 = 0, curr2 = 0;
        for(int i = 0; i < sizeOfMin; i++)
        {
            curr1 = charToInt(number_1[i]);
            std::string result_s_T = "\0";
            int remainder = 0, t = 0;
            for(int j = 0; j < sizeOfMax; j++)
            {
                curr2 = charToInt(number_2[j]);
                t = curr1 * curr2 + remainder;
                remainder = t / 10;
                result_s_T.push_back(intToChar(t % 10));
            }
            if(remainder != 0)
            {
                result_s_T.push_back(intToChar(remainder));
            }
            std::reverse(result_s_T.begin(), result_s_T.end());
            for(int k = 0; k < i; k++)
            {
                result_s_T.push_back('0');
            }
            result_T += result_s_T;
        }

        result.number = result_T.number;
        formatNumber(result);
        return result;
    }
    const bigInt_t operator*(const int num) const
    {
        bigInt_t number = num;
        return (*this * number);
    }
    const bigInt_t operator*(const std::string num) const
    {
        bigInt_t number = num;
        return (*this * number);
    }
    const bigInt_t operator*(const long long num) const
    {
        bigInt_t number = num;
        return (*this * number);
    }
    const bigInt_t operator*(const unsigned long long num) const
    {
        bigInt_t number = num;
        return (*this * number);
    }

};