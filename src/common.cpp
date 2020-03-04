#include "common.h"

/** test if a value x is between two margins
 *
 * @param aX number to test
 * @param aLowMargin low margin
 * @param aHighMargin high margin
 */
bool between( float aX, float aLowMargin, float aHighMargin )
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
