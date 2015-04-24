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
using namespace std;

/****************************
* deleteMultiples
*   This will delete all the
*     multiples for the NUM.
****************************/
void deleteMultiples(bool primes[], int num, int range)
{
    assert(num <= range);

    // Start at 2 since everything is a multiple of 1 :)
    int i = 2;
    bool done = false;
    int n;

    while (!done)
    {
        n = i * num;

        if (n <= range)
        {
            assert(primes[n-1] == 0 || primes[n-1] == 1);

            primes[n - 1] = 1; // You are not prime!
            ++i;
        }
        else
            done = true;
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
void seiveEratosthenes(int range)
{
    // Make sure the range is greater than or equal to 2.
    // 2 is the only smallest prime number.
    if (range >= 2)
    {
        // Create an array that will hold all the primes in the range.
        // And initalize everything to zero.
        bool * primes = new bool[range];
        memset(primes, 0, sizeof(primes));

        // Now loop through the range of numbers and change
        // all the numbers to 1 that are not prime!
        for (int i = 1; i < range; ++i)
        {
            if (primes[i] == 0)
            {
                // Now delete all the multiples of i + 1
                deleteMultiples(primes, i + 1, range);
            }
        }

        delete primes;
        // For output purposes
#ifdef DEBUG
        for (int i = 0; i < range; ++i)
        {
            if (primes[i] == 1)
            {
                cout << "\033[1;31m" << i + 1 << "\033[0m";
            }
            else
            {
                cout << i + 1;
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
* main
*   Driver function.
*************************/
int main(int argc, char const *argv[])
{
    int range = numeric_limits<int>::max();
    seiveEratosthenes(range - 1);
    return 0;
}