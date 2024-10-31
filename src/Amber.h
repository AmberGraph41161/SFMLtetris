#ifndef AMBER_H
#define AMBER_H

#include <iostream>
#include <chrono>
#include <vector>
#include <limits>
#include <random>

namespace AMBER
{
    //function definitions
    void SLEEP(double seconds);
    int random(int minimum, int maximum);
    double randomdouble(double minimum, double maximum);

    //templates and structures
    template <typename T>
    T input(std::string message)
    {
        T input;
        std::cout << message << std::endl;
        std::cout << "> ";
        if constexpr(std::is_same<T, std::string>::value)
        {
            std::getline(std::cin, input);
        } else
        {
            std::cin >> input;
        }

        while(std::cin.bad() || std::cin.fail())
        {
            std::cout << "[BAD INPUT]" << std::endl;
            std::cout << "[PLEASE TRY AGAIN]" << std::endl;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << message << std::endl;
            std::cout << "> ";

            if constexpr(std::is_same<T, std::string>::value)
            {
                std::getline(std::cin, input);
            } else
            {
                std::cin >> input;
            }
        }
        return input;
    }

    typedef struct RATIO
    {
        int num;
        int den;

        RATIO()
        {
            num = 1;
            den = 1;
        }
        RATIO(int num, int den)
        {
            this->num = num;
            this->den = den;
        }

        //Greatest Common Divisor
        //https://www.tutorialspoint.com/cplusplus-program-to-find-gcd
        //https://en.m.wikipedia.org/wiki/Euclidean_algorithm
        int gcd(int num, int den)
        {
            if(den == 0)
            {
                return num;
            }
            return gcd(den, num % den);
        }
        void simplify()
        {
            int GCD = gcd(num, den);
            if(GCD < 0)
            {
                GCD *= -1;
            }
            num /= GCD;
            den /= GCD;
        }
    } fraction, fract;

    struct DOUBLERATIO
    {
        double num;
        double den;

        DOUBLERATIO()
        {
            num = 1;
            den = 1;
        }
        DOUBLERATIO(double num, double den)
        {
            this->num = num;
            this->den = den;
        }

        int getdecimalplaces(double num)
        {
            std::string stringnum = std::to_string(num);
            //get rid of trailing zeros on decimal
            for(int x = stringnum.length() - 1; x > 0; x--)
            {
                if(stringnum[x] == '0')
                {
                    stringnum.pop_back();
                } else
                {
                    break;
                }
            }
            return ((stringnum.length() - 1) - stringnum.find('.'));
        }
        //Greatest Common Divisor
        //https://www.tutorialspoint.com/cplusplus-program-to-find-gcd
        //https://en.m.wikipedia.org/wiki/Euclidean_algorithm
        double gcd(int num, int den)
        {
            if(den == 0)
            {
                return num;
            }
            return gcd(den, num % den);
        }
        void simplify()
        {
            //convert to int
            int numdecimalplaces = getdecimalplaces(num);
            int dendecimalplaces = getdecimalplaces(den);
            for(int x = 0; x < numdecimalplaces; x++)
            {
                num *= 10;
            }
            for(int x = 0; x < dendecimalplaces; x++)
            {
                den *= 10;
            }

            //do GCD calculations
            int GCD = gcd((int)num, (int)den);
            if(GCD < 0)
            {
                GCD *= -1;
            }
            num /= GCD;
            den /= GCD;

            //convert back to double
            for(int x = 0; x < numdecimalplaces; x++)
            {
                num *= 0.1;
            }
            for(int x = 0; x < dendecimalplaces; x++)
            {
                den *= 0.1;
            }
        }
    };

    struct TIMER
    {
        std::chrono::time_point<std::chrono::system_clock> START, END;
        TIMER()
        {
            START = std::chrono::high_resolution_clock::now();
        }
        ~TIMER()
        {
            END = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = END - START;
            std::cout << "operation completed in " << duration.count() << " seconds" << std::endl;
        }
    };
}

#endif // AMBER_H
