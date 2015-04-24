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
#include <cmath>
using namespace std;

/**************************************
* testForPrimality
*   This function will be using the
*     Sieve of Eratosthenes to find
*     if the number you have is a Prime
*     number.
**************************************/
bool testForPrimality(int num)
{

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
int int main(int argc, char const *argv[])
{

    return 0;
}