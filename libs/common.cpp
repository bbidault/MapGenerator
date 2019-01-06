#include "common.h"

bool between( double x, double a, double b )
{
    if( x >= a && x < b)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int abs( int a )
{
    if( a >= 0 )
    {
        return a;
    }
    else
    {
        return -a;
    }
}

int pow( int x, int y )
{
    int k = 1;

    for( int i = 0 ; i < y ; i++ )
    {
        k *= x;
    }

    return k;
}
