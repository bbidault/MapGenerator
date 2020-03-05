#include "world_map.h"
#include "common.h"

/**
 * @brief generate temperature map from longitude and altitude
 */
void WorldMap::createTemp()
{
    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            // the temperature is affected by the latitude
            // Tropic of Cancer
            if ( j <= height * ( 90 - AXIAL_TILT ) / 180 )
            {
                world[i][j].q3Temp = j * 40 / ( height * ( 90 - AXIAL_TILT ) / 180 );
            }
            else
            {
                world[i][j].q3Temp = 40
                    - ( j - height * ( 90 - AXIAL_TILT ) / 180 ) * 70
                    / ( height - height * ( 90 - AXIAL_TILT ) / 180 );
            }

            // Tropic of Capricorn
            if ( j <= height * ( 90 + AXIAL_TILT ) / 180 )
            {
                world[i][j].q1Temp = -30 + j * 70 / ( height * ( 90 + AXIAL_TILT ) / 180 );
            }
            else
            {
                world[i][j].q1Temp = 40
                    - ( j - height * ( 90 + AXIAL_TILT ) / 180 ) * 40
                    / ( height - height * ( 90 + AXIAL_TILT ) / 180 );
            }

            world[i][j].q2Q4Temp = ( world[i][j].q1Temp + world[i][j].q3Temp ) / 2;

            // bodies of water are less affected by season,
            // they work as thermal reservoirs
            if ( world[i][j].state != LAND )
            {
                world[i][j].q1Temp = ( world[i][j].q1Temp + 9 * world[i][j].q2Q4Temp ) / 10;
                world[i][j].q3Temp = ( world[i][j].q3Temp + 9 * world[i][j].q2Q4Temp ) / 10;
            }

            // the temperature is effected by the altitude
            if ( world[i][j].altitude >= 0 )
            {
                world[i][j].q1Temp   -= world[i][j].altitude / Constants::MetersPerDegreeDrop_mpd;
                world[i][j].q3Temp   -= world[i][j].altitude / Constants::MetersPerDegreeDrop_mpd;
                world[i][j].q2Q4Temp -= world[i][j].altitude / Constants::MetersPerDegreeDrop_mpd;
            }
        }
    }

    for ( int i = 0; i < 30; i++ )
    {
        averageTemperature();
    }
}

/**
 * @brief average temperature across the map
 */
void WorldMap::averageTemperature()
{
    for ( int i = 1; i < width - 1; i++ )
    {
        for ( int j = 1; j < height - 1; j++ )
        {
            // land (soil) has a higher temperature dynamic than water
            if ( world[i][j].state == LAND )
            {
                world[i][j].q2Q4Temp = ( ( world[i - 1][j - 1].q2Q4Temp
                                           + world[i - 1][j + 1].q2Q4Temp ) / SQRT_2
                                         + world[i - 1][j].q2Q4Temp + world[i][j - 1].q2Q4Temp
                                         + world[i][j].q2Q4Temp * 2 ) / ( 4 + SQRT_2 );

                world[i][j].q1Temp = ( ( world[i - 1][j - 1].q1Temp
                                         + world[i - 1][j + 1].q1Temp ) / SQRT_2
                                       + world[i - 1][j].q1Temp + world[i][j - 1].q1Temp
                                       + world[i][j].q1Temp * 2 ) / ( 4 + SQRT_2 );

                world[i][j].q3Temp = ( ( world[i - 1][j - 1].q3Temp
                                         + world[i - 1][j + 1].q3Temp ) / SQRT_2
                                       + world[i - 1][j].q3Temp + world[i][j - 1].q3Temp
                                       + world[i][j].q3Temp * 2 ) / ( 4 + SQRT_2 );
            }
            else
            {
                world[i][j].q2Q4Temp = ( ( world[i - 1][j - 1].q2Q4Temp
                                           + world[i - 1][j + 1].q2Q4Temp ) / SQRT_2
                                         + world[i - 1][j].q2Q4Temp + world[i][j - 1].q2Q4Temp
                                         + world[i][j].q2Q4Temp * 20 ) / ( 22 + SQRT_2 );

                world[i][j].q1Temp = ( ( world[i - 1][j - 1].q1Temp
                                         + world[i - 1][j + 1].q1Temp ) / SQRT_2
                                       + world[i - 1][j].q1Temp + world[i][j - 1].q1Temp
                                       + world[i][j].q1Temp * 20 ) / ( 22 + SQRT_2 );

                world[i][j].q3Temp = ( ( world[i - 1][j - 1].q3Temp
                                         + world[i - 1][j + 1].q3Temp ) / SQRT_2
                                       + world[i - 1][j].q3Temp + world[i][j - 1].q3Temp
                                       + world[i][j].q3Temp * 20 ) / ( 22 + SQRT_2 );
            }
        }
    }

    for ( int i = width - 2; i > 0; i-- )
    {
        for ( int j = height - 2; j > 0; j-- )
        {
            if ( world[i][j].state == LAND )
            {
                world[i][j].q2Q4Temp = ( ( world[i + 1][j + 1].q2Q4Temp
                                           + world[i + 1][j - 1].q2Q4Temp ) / SQRT_2
                                         + world[i + 1][j].q2Q4Temp + world[i][j + 1].q2Q4Temp
                                         + world[i][j].q2Q4Temp * 2 ) / ( 4 + SQRT_2 );

                world[i][j].q1Temp = ( ( world[i + 1][j + 1].q1Temp
                                         + world[i + 1][j - 1].q1Temp ) / SQRT_2
                                       + world[i + 1][j].q1Temp + world[i][j + 1].q1Temp
                                       + world[i][j].q1Temp * 2 ) / ( 4 + SQRT_2 );

                world[i][j].q3Temp = ( ( world[i + 1][j + 1].q3Temp
                                         + world[i + 1][j - 1].q3Temp ) / SQRT_2
                                       + world[i + 1][j].q3Temp + world[i][j + 1].q3Temp
                                       + world[i][j].q3Temp * 2 ) / ( 4 + SQRT_2 );
            }
            else
            {
                world[i][j].q2Q4Temp = ( ( world[i + 1][j + 1].q2Q4Temp
                                           + world[i + 1][j - 1].q2Q4Temp ) / SQRT_2
                                         + world[i + 1][j].q2Q4Temp + world[i][j + 1].q2Q4Temp
                                         + world[i][j].q2Q4Temp * 20 ) / ( 22 + SQRT_2 );

                world[i][j].q1Temp = ( ( world[i + 1][j + 1].q1Temp
                                         + world[i + 1][j - 1].q1Temp ) / SQRT_2
                                       + world[i + 1][j].q1Temp + world[i][j + 1].q1Temp
                                       + world[i][j].q1Temp * 20 ) / ( 22 + SQRT_2 );

                world[i][j].q3Temp = ( ( world[i + 1][j + 1].q3Temp
                                         + world[i + 1][j - 1].q3Temp ) / SQRT_2
                                       + world[i + 1][j].q3Temp + world[i][j + 1].q3Temp
                                       + world[i][j].q3Temp * 20 ) / ( 22 + SQRT_2 );
            }
        }
    }
}

/**
 * @brief color temperature map
 */
void WorldMap::colorTemp()
{
    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            world[i][j].q2Q4TempColor[0] = 127.5 - world[i][j].q2Q4Temp * 127.5 / 40;
            world[i][j].q2Q4TempColor[1] = 0;
            world[i][j].q2Q4TempColor[2] = 127.5 + world[i][j].q2Q4Temp * 127.5 / 40;

            world[i][j].q1TempColor[0] = 127.5 - world[i][j].q1Temp * 127.5 / 40;
            world[i][j].q1TempColor[1] = 0;
            world[i][j].q1TempColor[2] = 127.5 + world[i][j].q1Temp * 127.5 / 40;

            world[i][j].q3TempColor[0] = 127.5 - world[i][j].q3Temp * 127.5 / 40;
            world[i][j].q3TempColor[1] = 0;
            world[i][j].q3TempColor[2] = 127.5 + world[i][j].q3Temp * 127.5 / 40;
        }
    }
}
