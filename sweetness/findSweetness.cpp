/****************************************************
* Program:
*   findSweetness.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This will be testing out the range of Euler's
*       plynomial.
****************************************************/

#include <vector>
#include <iostream>
#include <string.h>
#include <cmath>
#include <limits>
#include <cassert>
#include <string>
#include <stdlib.h>
#include <string>
#include <map>
#include <sstream>
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
int maxInt = numeric_limits<int>::max() - 1;

/******************************
* displayLearnedAndDirections
*   Display the learned page and
*       directions.
******************************/
void displayLearnedAndDirections() throw (string)
{
    string message = "How to use this program type: 'a.out --help'\n\n";

    throw(message);
    return;
}

/******************************
* parseCommandLine
*   This will parse the command
*       line.
******************************/
void parseCommandLine(map<string, int> & args, int argc, const char **argv) throw (string)
{
    Debug("Parsing command line\n");

    for (int i = 1; i < argc; ++i)
    {
        if (argv[i] == string("-h") || argv[i] == string("--help"))
        {
            args["help"] = 1;
        }
        else if (argv[i] == string("-mn") || argv[i] == string("--min"))
        {
            int min = atoi(argv[i + 1]);

            args["min"] = min;

            i++;
        }
        else if (argv[i] == string("-mx") || argv[i] == string("--max"))
        {
            int max = atoi(argv[i + 1]);

            args["max"] = max;

            i++;
        }
        else if (argv[i] == string("-c"))
        {
            int c = atoi(argv[i + 1]);

            args["c"] = c;

            i++;
        }
        else if (argv[i]== string("-f") || argv[i] == string("--find"))
        {
            args["find"] = 1;
        }
        else
        {
            string message = "\nOption: ";
            message = message + argv[i] + " is not a valid option.\nType a.out -h for help.\n\n";
            throw(message);
        }
    }

    return;
}

/*******************************
* readCommandLine
*   This will read the arguments
*       given by the user.
*******************************/
void readCommandLine(map<string, int> & args) throw (string)
{
    string message = "";
    int max = args["max"];
    int min = args["min"];
    int c   = args["c"];

    if (args["min"] < -46341)
    {
        message = "\nERROR: your minimum x is too small.\nType a.out -h for help.\n\n";
    }
    else if (args["max"] > 46341)
    {
        message = "\nERROR: your maximum x is too big.\nType a.out -h for help.\n\n";
    }
    else if (((max * max) + max + c) < 0 ||
            ((min * min) + min + c) < 0)
    {
        cout << ((max * max) + max + c) << endl
             << ((min * min) + min + c) << endl;

        int maxC = 0;

        if (max > abs(min))
        {
            maxC = maxInt - (max * max) + max;
        }
        else
        {
            maxC = maxInt - (abs(min) * abs(min)) + abs(min);
        }

        // Convert int to string.
        ostringstream convert;
        convert << maxC;

        message = "\nERROR: your value c is too big compared to your x range.\n";
        message = message + "\tWith given range c must be less than this: " + convert.str() +
                  "\nType a.out -h for help.\n\n";
    }

    // No matter what you should show this if defined.
    if (args["help"] == 1)
    {
        message = "\nCommand line arguments for a.out:\n\n";

        message = message + "     a.out [options] [value]\n\n" +
              "     Options:\n" +
              "\t-mn, --min\t Minimum range of x. MINIMUM x is -46341.\n" +
              "\t-mx, --max\t Maximum range of x. MAXIMUM x is 46341.\n" +
              "\t-c\t\t Value for C. Maximum c is computed by given x.\n" +
              "\t-f   --find\t This will find the best x and c value.\n\n";
    }

    // Throw the message if there is one.
    if (message != string(""))
    {
        throw(message);
    }

    // Check these to see which functions to do.
    if (max == 0 && min == 0 && c == 0 && args["find"] != 1)
    {
        displayLearnedAndDirections();
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
void testEulersPolynomial(map<string, int> & args)
{
    cout << "\nComputing probability with given range and c...\n";

    float count = 0;
    float totalPoss = 0;
    int min = args["min"];
    int max = args["max"];
    int c   = args["c"];

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
* grabSize
*   Get the right size!
*************************/
void grabSize(map<string, int> & args)
{
    // Check to see if we need the max int.
    if (args["find"] == 1)
    {
        sizeOfPrimes = maxInt;
        return;
    }

    if (abs(args["min"]) > abs(args["max"]))
    {
        int min = args["min"];
        int c = args["c"];
        sizeOfPrimes = (min * min) + min + c;
    }
    else
    {
        sizeOfPrimes = (args["max"] * args["max"]) + args["max"] + args["c"];
    }

    return;
}

/************************
* findMaxC
*   This will find the max C.
************************/
int findMaxC(int max, int min)
{
    int maxC = 0;
    int x = 0;

    if (max > min)
        x = max;
    else
        x = min;

    maxC = maxInt - (x * x) + x;

    return maxC;
}

/*************************
* findBestXAndC
*   This will go throug all
*       the x ranges and c.
*       to find the best probability.
*       of getting a prime.
*************************/
void findBestXAndC()
{
    cout << "\nNow finding the best x range and c...\n";

    // Make some variables!
    vector<float> bestProb;
    bestProb.push_back(0.0); // bestProb[0] == min of X.
    bestProb.push_back(0.0); // bestProb[1] == max of X.
    bestProb.push_back(0.0); // bestProb[2] == best c.
    bestProb.push_back(0.0); // bestProb[3] == probability.
    int minX = -46341;
    int maxX = -36341;
    int maxC = findMaxC(abs(maxX), abs(minX));

#ifdef DEBUG
    cout << "maxC = " << maxC << endl;
#endif

    float count;
    float totalPoss = 10000;

    // One more while loop to go through all the ranges!
    while (minX <= 1)
    {
        // For loop for c
        for (int c = 1; c <= maxC; ++c)
        {
            count = 0;

            // Now to run through all of x!
            for (int i = minX; i <= maxX; ++i)
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

            float prob = (count / 10000) * 100;

            // Now check the vector!
            if (prob > bestProb[3])
            {
                // Insert the best x and c!
                bestProb[0] = minX;
                bestProb[1] = maxX;
                bestProb[2] = c;
                bestProb[3] = prob;
            }
        }

        // Now increment the range and get max c!
        maxC = findMaxC(abs(++maxX), abs(++minX));
    }

    cout << "\n**************************************\n"
         << "************Best Probability**********\n"
         << "**************************************\n\n"
         << "With given variables: " << bestProb[0] << " <= x <= " << bestProb[1]
         << " and C = " << bestProb[2] << endl
         << "Your probability of getting a prime is " << bestProb[3] << "%\n\n";

    return;
}

/*************************
* main
*   Driver function.
*************************/
int main(int argc, const char *argv[])
{
    // Set up map!
    map<string, int> args;
    args["help"] = 0;
    args["min"]  = 0;
    args["max"]  = 0;
    args["find"] = 0;
    args["c"]    = 0;

    try
    {
        // Parse arguments
        parseCommandLine(args, argc, argv);

        // Grab the command line arguments!
        readCommandLine(args);

        // Grab the right size!
        grabSize(args);

        // Now allocate it!
        primesArray = new bool[sizeOfPrimes];

        // Now find all the primes!
        seiveEratosthenes();

        // Now test Euler's Polynomial
        if (args["find"] == 1)
           findBestXAndC();
        else
            testEulersPolynomial(args);

        // Delete the array
        delete [] primesArray;
    }
    catch(string error)
    {
        cout << error;
    }

    return 0;
}