#include "world_map.h"
#include "common.h"

void world_map::create_temp()
{
    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            /// the temperature is affected by the latitude
            /// Tropic of Cancer
            if ( j <= height * ( 90 - AXIAL_TILT ) / 180 )
            {
                world[i][j].Q3_temp = j * 40 / ( height * ( 90 - AXIAL_TILT ) / 180 );
            }
            else
            {
                world[i][j].Q3_temp = 40
                    - ( j - height * ( 90 - AXIAL_TILT ) / 180 ) * 70
                    / ( height - height * ( 90 - AXIAL_TILT ) / 180 );
            }

            /// Tropic of Capricorn
            if ( j <= height * ( 90 + AXIAL_TILT ) / 180 )
            {
                world[i][j].Q1_temp = -30 + j * 70 / ( height * ( 90 + AXIAL_TILT ) / 180 );
            }
            else
            {
                world[i][j].Q1_temp = 40
                    - ( j - height * ( 90 + AXIAL_TILT ) / 180 ) * 40
                    / ( height - height * ( 90 + AXIAL_TILT ) / 180 );
            }

            world[i][j].Q2_Q4_temp = ( world[i][j].Q1_temp + world[i][j].Q3_temp ) / 2;

            /// bodies of water are less affected by season,
            /// they work as thermal reservoirs
            if ( world[i][j].state != LAND )
            {
                world[i][j].Q1_temp = ( world[i][j].Q1_temp + 9 * world[i][j].Q2_Q4_temp ) / 10;
                world[i][j].Q3_temp = ( world[i][j].Q3_temp + 9 * world[i][j].Q2_Q4_temp ) / 10;
            }

            /// the temperature is effected by the altitude
            if ( world[i][j].altitude >= 0 )
            {
                world[i][j].Q1_temp    -= world[i][j].altitude / 137;
                world[i][j].Q3_temp    -= world[i][j].altitude / 137;
                world[i][j].Q2_Q4_temp -= world[i][j].altitude / 137;
            }
        }
    }

    for ( int i = 0; i < 30; i++ )
    {
        this->average_temperature();
    }
}

void world_map::average_temperature()
{
    for ( int i = 1; i < width - 1; i++ )
    {
        for ( int j = 1; j < height - 1; j++ )
        {
            /// land (soil) has a higher temperature dynamic than water
            if ( world[i][j].state == LAND )
            {
                world[i][j].Q2_Q4_temp = ( ( world[i - 1][j - 1].Q2_Q4_temp
                                             + world[i - 1][j + 1].Q2_Q4_temp ) / SQRT_2
                                           + world[i - 1][j].Q2_Q4_temp + world[i][j - 1].Q2_Q4_temp
                                           + world[i][j].Q2_Q4_temp * 2 ) / ( 4 + SQRT_2 );

                world[i][j].Q1_temp = ( ( world[i - 1][j - 1].Q1_temp
                                          + world[i - 1][j + 1].Q1_temp ) / SQRT_2
                                        + world[i - 1][j].Q1_temp + world[i][j - 1].Q1_temp
                                        + world[i][j].Q1_temp * 2 ) / ( 4 + SQRT_2 );

                world[i][j].Q3_temp = ( ( world[i - 1][j - 1].Q3_temp
                                          + world[i - 1][j + 1].Q3_temp ) / SQRT_2
                                        + world[i - 1][j].Q3_temp + world[i][j - 1].Q3_temp
                                        + world[i][j].Q3_temp * 2 ) / ( 4 + SQRT_2 );
            }
            else
            {
                world[i][j].Q2_Q4_temp = ( ( world[i - 1][j - 1].Q2_Q4_temp
                                             + world[i - 1][j + 1].Q2_Q4_temp ) / SQRT_2
                                           + world[i - 1][j].Q2_Q4_temp + world[i][j - 1].Q2_Q4_temp
                                           + world[i][j].Q2_Q4_temp * 20 ) / ( 22 + SQRT_2 );

                world[i][j].Q1_temp = ( ( world[i - 1][j - 1].Q1_temp
                                          + world[i - 1][j + 1].Q1_temp ) / SQRT_2
                                        + world[i - 1][j].Q1_temp + world[i][j - 1].Q1_temp
                                        + world[i][j].Q1_temp * 20 ) / ( 22 + SQRT_2 );

                world[i][j].Q3_temp = ( ( world[i - 1][j - 1].Q3_temp
                                          + world[i - 1][j + 1].Q3_temp ) / SQRT_2
                                        + world[i - 1][j].Q3_temp + world[i][j - 1].Q3_temp
                                        + world[i][j].Q3_temp * 20 ) / ( 22 + SQRT_2 );
            }
        }
    }

    for ( int i = width - 2; i > 0; i-- )
    {
        for ( int j = height - 2; j > 0; j-- )
        {
            if ( world[i][j].state == LAND )
            {
                world[i][j].Q2_Q4_temp = ( ( world[i + 1][j + 1].Q2_Q4_temp
                                             + world[i + 1][j - 1].Q2_Q4_temp ) / SQRT_2
                                           + world[i + 1][j].Q2_Q4_temp + world[i][j + 1].Q2_Q4_temp
                                           + world[i][j].Q2_Q4_temp * 2 ) / ( 4 + SQRT_2 );

                world[i][j].Q1_temp = ( ( world[i + 1][j + 1].Q1_temp
                                          + world[i + 1][j - 1].Q1_temp ) / SQRT_2
                                        + world[i + 1][j].Q1_temp + world[i][j + 1].Q1_temp
                                        + world[i][j].Q1_temp * 2 ) / ( 4 + SQRT_2 );

                world[i][j].Q3_temp = ( ( world[i + 1][j + 1].Q3_temp
                                          + world[i + 1][j - 1].Q3_temp ) / SQRT_2
                                        + world[i + 1][j].Q3_temp + world[i][j + 1].Q3_temp
                                        + world[i][j].Q3_temp * 2 ) / ( 4 + SQRT_2 );
            }
            else
            {
                world[i][j].Q2_Q4_temp = ( ( world[i + 1][j + 1].Q2_Q4_temp
                                             + world[i + 1][j - 1].Q2_Q4_temp ) / SQRT_2
                                           + world[i + 1][j].Q2_Q4_temp + world[i][j + 1].Q2_Q4_temp
                                           + world[i][j].Q2_Q4_temp * 20 ) / ( 22 + SQRT_2 );

                world[i][j].Q1_temp = ( ( world[i + 1][j + 1].Q1_temp
                                          + world[i + 1][j - 1].Q1_temp ) / SQRT_2
                                        + world[i + 1][j].Q1_temp + world[i][j + 1].Q1_temp
                                        + world[i][j].Q1_temp * 20 ) / ( 22 + SQRT_2 );

                world[i][j].Q3_temp = ( ( world[i + 1][j + 1].Q3_temp
                                          + world[i + 1][j - 1].Q3_temp ) / SQRT_2
                                        + world[i + 1][j].Q3_temp + world[i][j + 1].Q3_temp
                                        + world[i][j].Q3_temp * 20 ) / ( 22 + SQRT_2 );
            }
        }
    }
}

void world_map::color_temp()
{
    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            world[i][j].Q2_Q4_temp_color[0] = 127.5 - world[i][j].Q2_Q4_temp * 127.5 / 40;
            world[i][j].Q2_Q4_temp_color[1] = 0;
            world[i][j].Q2_Q4_temp_color[2] = 127.5 + world[i][j].Q2_Q4_temp * 127.5 / 40;

            world[i][j].Q1_temp_color[0] = 127.5 - world[i][j].Q1_temp * 127.5 / 40;
            world[i][j].Q1_temp_color[1] = 0;
            world[i][j].Q1_temp_color[2] = 127.5 + world[i][j].Q1_temp * 127.5 / 40;

            world[i][j].Q3_temp_color[0] = 127.5 - world[i][j].Q3_temp * 127.5 / 40;
            world[i][j].Q3_temp_color[1] = 0;
            world[i][j].Q3_temp_color[2] = 127.5 + world[i][j].Q3_temp * 127.5 / 40;
        }
    }
}
