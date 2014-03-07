#include "Utilities.h"

//
// log base 2 of the input value.
//
double log2(double value)
{
    if (value <= 0) return 0;

    return log10(value) / log10(2.0);
}

//
// How many bits in binary to represent this number?
//
unsigned int numBinaryBits(unsigned int value)
{
    return floor(log2(value)) + 1;
}