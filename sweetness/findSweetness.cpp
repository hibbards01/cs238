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
#include <string>
using namespace std;

// For debugging purposes.
// To output debug type in command line: g++ -DDEBUG <file>
#ifdef DEBUG
#define Debug(x) x
#else
#define Debug(x)
#endif

bool * primesArray; // Global variable, don't do this normally.
int sizeOfPrimes;

/*************************
* readCommandLine
*   This will read the arguments
*       given by the user.
*************************/
void readCommandLine(int & min, int & max, int & c, int argc, const char **argv) throw (string)
{
    string message;

    for (int i = 1; i < argc; ++i)
    {
        if (argv[i] == string("-h") || argv[i] == string("--help"))
        {
            message = "\nCommand line arguments for a.out:\n\n";

            message = message + "     a.out [options] [value]\n\n" +
                  "     Options:\n" +
                  "\t-mn, --min\t Minimum range of x. REQUIRED. MINIMUM x is -46340.\n" +
                  "\t-mx, --max\t Maximum range of x. REQUIRED. MAXIMUM x is 46340.\n" +
                  "\t-c\t\t Value for C. REQUIRED. MIN and MAX of c is 0 to 10,000.\n" +
                  "\t-l,  --learned\t What was learned in this exploration.\n" +
                  "\t-f   --find\t This will find the best c between 0 to 10,000 with x being -46340 < x < 46340.\n\n";

            throw(message);
        }
        else if (argv[i] == string("-mn") || argv[i] == string("--min"))
        {
            min = atoi(argv[i + 1]);

            if (min < -46340)
            {
                message = "\nERROR: your minimum x: ";
                message = message + argv[i + 1] + " is too small.\nType a.out -h for help.\n\n";
                throw(message);
            }
            else
            {
                i++;
            }
        }
        else if (argv[i] == string("-mx") || argv[i] == string("--max"))
        {
            max = atoi(argv[i + 1]);

            if (max > 46340)
            {
                message = "\nERROR: your maximum x: ";
                message = message + argv[i + 1] + " is too big.\nType a.out -h for help.\n\n";
                throw(message);
            }
            else
            {
                i++;
            }
        }
        else if (argv[i] == string("-c"))
        {
            c = atoi(argv[i + 1]);

            if (c > 10000 || c < 0)
            {
                message = "\nERROR: your value c: ";
                message = message + argv[i + 1] + " is invalid.\nType a.out -h for help.\n\n";
                throw(message);
            }
            else
            {
                i++;
            }
        }
        else
        {
            message = "\nOption: ";
            message = message + argv[i] + " is not a valid option.\nType a.out -h for help.\n\n";
            throw(message);
        }
    }

    if (max == 0 || min == 0 || c == 0)
    {
        message = "\nERROR: your command agruments is missing some values.\nType a.out -h for help\n\n";
        throw(message);
    }

    return;
}

/**************************************
* seiveEratosthenes
*   This function will be using the
*     Sieve of Eratosthenes to find
*     all the possible prime numbers in
*     the range.
**************************************/
void seiveEratosthenes()
{
    cout << "\nGrabbing all the primes...\n";

    // Create an array that will hold all the primes in the range
    // and initalize everything to zero.
    memset(primesArray, 0, sizeof(primesArray));

    // Now loop through the range of numbers and change
    // all the numbers to 1 that are not prime!
    for (int i = 2; i <= sizeOfPrimes; ++i)
    {
        if (primesArray[i] == 0)
        {
            for (int j = i; (j * i) <= sizeOfPrimes && (j * i) > 0; ++j)
            {
                primesArray[i * j] = 1; // You are not a prime!
            }
        }
    }

    // For output purposes
#ifdef DEBUG
        for (int i = 2; i <= sizeOfPrimes; ++i)
        {
            if (primesArray[i] == 1)
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

    return;
}

/*******************************************************
* testEulersPolynomial
*   This will have a given range, and will
*     test that range using Euler's Polynomial function
*     and then check it's primality.
*******************************************************/
void testEulersPolynomial(const int min, const int max, const int c)
{
    cout << "\nComputing probability with given range and c...\n";

    float count = 0;
    float totalPoss = 0;

    if (min >= 0)
        totalPoss = max - min;
    else
        totalPoss = abs(min) + max;

    // Start from the min and work our way up to the max.
    for (int i = min; i < max; ++i)
    {
        // Now use Euler's Polynomial!
        //  num =     x^2 + x + C
        int num = abs((i * i) + i + c);

        // Now test for it's primality!
        if (primesArray[num] == 0)
        {
            count++;
        }
    }

#ifdef DEBUG
    cout << "\n\ncount = " << count;
    cout << "\ntotal possibilities is: " << totalPoss;
#endif

    cout << "\nWith given conditions:\n"
         << "\t" << min << " < x < " << max << " and c = " << c << endl
         << "\nProbability of you getting a prime with any x is: "
         << (count / totalPoss) * 100 << "%\n\n";
}

/*************************
* main
*   Driver function.
*************************/
int main(int argc, const char *argv[])
{
    int max = 0;
    int min = 0;
    int c   = 0;

    try
    {
        // Grab the command line arguments!
        readCommandLine(min, max, c, argc, argv);

        // Allocate memory
        sizeOfPrimes = (max * max) + max + c;
        primesArray = new bool[sizeOfPrimes];

        // Now find all the primes!
        seiveEratosthenes();

        // Now test Euler's Polynomial
        testEulersPolynomial(min, max, c);

        // Delete the array
        delete [] primesArray;
    }
    catch(string error)
    {
        cout << error;
    }

    return 0;
}