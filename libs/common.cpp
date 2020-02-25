#include "common.h"

bool between( double aX, double aA, double aB )
{
    if ( ( aX >= aA ) && ( aX < aB ) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

int abs( int aA )
{
    if ( aA >= 0 )
    {
        return aA;
    }
    else
    {
        return -aA;
    }
}

int pow( int aX, int aY )
{
    int k = 1;

    for ( int i = 0; i < aY; i++ )
    {
        k *= aX;
    }

    return k;
}
