/****************************************************
* Program:
*   findSweetness.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This will be testing out the range of Euler's
*       plynomial.
****************************************************/

#include <iostream>
#include <string.h>
#include <cmath>
#include <limits>
#include <cassert>
#include <string>
#include <stdlib.h>
using namespace std;

// For debugging purposes.
// To output debug type in command line: g++ -DDEBUG <file>
#ifdef DEBUG
#define Debug(x) x
#else
#define Debug(x)
#endif

bool * primes; // Global variable, don't do this normally.

/**************************************
* seiveEratosthenes
*   This function will be using the
*     Sieve of Eratosthenes to find
*     all the possible prime numbers in
*     the range.
**************************************/
void seiveEratosthenes(const int min, const int max)
{
    // Make sure the range is greater than or equal to 2.
    // 2 is the only smallest prime number.
    if (max >= 2)
    {
        // Create an array that will hold all the primes in the range
        // and initalize everything to zero.
        memset(primes, 0, sizeof(primes));

        // Now loop through the range of numbers and change
        // all the numbers to 1 that are not prime!
        for (int i = 2; i <= max; ++i)
        {
            if (primes[i] == 0)
            {
                for (int j = i; (j * i) <= max && (j * i) > 0; ++j)
                {
                    primes[i * j] = 1; // You are not a prime!
                }
            }
        }

        // For output purposes
#ifdef DEBUG
        for (int i = min; i <= max; ++i)
        {
            if (primes[i] == 1)
            {
                cout << "\033[1;31m" << i << "\033[0m";
            }
            else
            {
                cout << i;
            }
            cout << " ";
        }
        cout << endl << endl;
#endif
    }

    return;
}

/*******************************************************
* testEulersPolynomial
*   This will have a given range, and will
*     test that range using Euler's Polynomial function
*     and then check it's primality.
*******************************************************/
void testEulersPolynomial(int min, int max, int c)
{
    // Start from the min and work our way up to the max.
    for (int i = min; i < max; ++i)
    {
        // Now use Euler's Polynomial!
        //  num =     x^2 + x + C
        int num = (i * i) + i + c;

        // Now test for it's primality!
    }
}

/*************************
* readCommandLine
*   This will read the arguments
*       given by the user.
*************************/
void readCommandLine(int & min, int & max, int & c, int argc, const char **argv)
{
    bool showHelp = false;

    for (int i = 1; i < argc && !showHelp; ++i)
    {
        if (argv[i] == string("-h") || argv[i] == string("--help"))
        {
            cout << "\nCommand line arguments for a.out:\n\n"
                 << "     a.out [options] [value]\n\n"
                 << "     Options:\n"
                 << "\t-mn, --min\tMinimum range. Default 0.\n"
                 << "\t-mx, --max\tMaximum range. REQUIRED.\n"
                 << "\t-c\t\tValue for C.\n\n";

            showHelp = true;
        }
        else if (argv[i] == string("-mn") || argv[i] == string("--min"))
        {
            min = atoi(argv[i + 1]);
        }
        else if (argv[i] == string("-mx") || argv[i] == string("--max"))
        {
            max = atoi(argv[i + 1]);
        }
        else if (argv[i] == string("-c"))
        {
            c = atoi(argv[i + 1]);
        }
        else
        {
            if (!isdigit(argv[i][0]))
            {
                cout << "\nOption: " << argv[i] << " is not a valid option.\nType -h for help.\n\n";
                showHelp = true;
            }
        }
    }

    if (max == 0 && !showHelp)
    {
        cout << "\nThere was an error in your command line.\nType -h for help.\n\n";
    }

    return;
}

/*************************
* main
*   Driver function.
*************************/
int main(int argc, const char *argv[])
{
    // Grab the command line arguments!
    int max = 0;
    int min = 0;
    int c   = 0;

    readCommandLine(min, max, c, argc, argv);

    // Allocate the memore for primes!
    primes = new bool[max];

    // Now grab the primes within that range!
    seiveEratosthenes(min, max);

    // Now delete the allocation
    delete [] primes;

    return 0;
}
