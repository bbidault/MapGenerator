#include "common.h"

/** test if a value x is between two margins
 *
 * @param aX number to test
 * @param aLowMargin low margin
 * @param aHighMargin high margin
 */
bool between( double aX, double aLowMargin, double aHighMargin )
{
    if ( ( aX >= aLowMargin ) && ( aX < aHighMargin ) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/** return absolute value |aA|
 *
 * @param aA
 */
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

/** return aX^aY
 *
 * @param aX
 * @param aY
 */
int pow( int aX, int aY )
{
    int k = 1;

    for ( int i = 0; i < aY; i++ )
    {
        k *= aX;
    }

    return k;
}
