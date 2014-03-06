#ifndef _UTILITIES_GUARD
#define _UTILITIES_GUARD 1

#include<cmath>

using namespace std;

const unsigned int null = 0;

// log base 2 of the input value.
double log2(double value);

// How many bits in binary to represent this number?
unsigned int numBinaryBits(unsigned int value);
    
#endif