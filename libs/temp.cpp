#include "world_map.h"
#include "common.h"


void world_map::create_temp()
{
    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            /// the temperature is affected by the latitude
            world[i][j].Q2_Q4_temp += 25 - ( abs( 30 - j*60/height ) );          

            /// the temperature is effected by the altitude
            if( world[i][j].altitude >= 0 )
            {
                world[i][j].Q2_Q4_temp -= world[i][j].altitude/137;
            }

            /// the seasonal minimum and maximum temperature are affected by the latitude
            if( world[i][j].state == LAND )
            {
                world[i][j].Q3_temp = world[i][j].Q2_Q4_temp + 20 - j*40/height;
                world[i][j].Q1_temp = world[i][j].Q2_Q4_temp - 20 + j*40/height;
            }
            else
            {
                world[i][j].Q3_temp = world[i][j].Q2_Q4_temp + 2 - j*4/height;
                world[i][j].Q1_temp = world[i][j].Q2_Q4_temp - 2 + j*4/height;
            }
            
             
        }
    }

    for( int i = 0 ; i < 30 ; i++ )
    {
        this->average_temperature();
    }
}

void world_map::average_temperature()
{
    for( int i = 1 ; i < width - 1 ; i++ )
    {
        for( int j = 1 ; j < height - 1 ; j++ )
        {
            /// land (soil) has a higher temperature dynamic than water
            if( world[i][j].state == LAND )
            {
                world[i][j].Q2_Q4_temp = ( ( world[i - 1][j - 1].Q2_Q4_temp 
                                    + world[i - 1][j + 1].Q2_Q4_temp )/SQRT_2
                                    + world[i - 1][j].Q2_Q4_temp + world[i][j - 1].Q2_Q4_temp 
                                    + world[i][j].Q2_Q4_temp*2 ) / ( 4 + SQRT_2 );

                world[i][j].Q1_temp = ( ( world[i - 1][j - 1].Q1_temp 
                                    + world[i - 1][j + 1].Q1_temp )/SQRT_2
                                    + world[i - 1][j].Q1_temp + world[i][j - 1].Q1_temp 
                                    + world[i][j].Q1_temp*2 ) / ( 4 + SQRT_2 );

                world[i][j].Q3_temp = ( ( world[i - 1][j - 1].Q3_temp 
                                    + world[i - 1][j + 1].Q3_temp )/SQRT_2
                                    + world[i - 1][j].Q3_temp + world[i][j - 1].Q3_temp 
                                    + world[i][j].Q3_temp*2 ) / ( 4 + SQRT_2 );
            }
            else
            {
                world[i][j].Q2_Q4_temp = ( ( world[i - 1][j - 1].Q2_Q4_temp 
                                    + world[i - 1][j + 1].Q2_Q4_temp )/SQRT_2
                                    + world[i - 1][j].Q2_Q4_temp + world[i][j - 1].Q2_Q4_temp 
                                    + world[i][j].Q2_Q4_temp*10 ) / ( 12 + SQRT_2 );

                world[i][j].Q1_temp = ( ( world[i - 1][j - 1].Q1_temp 
                                    + world[i - 1][j + 1].Q1_temp )/SQRT_2
                                    + world[i - 1][j].Q1_temp + world[i][j - 1].Q1_temp 
                                    + world[i][j].Q1_temp*10 ) / ( 12 + SQRT_2 );

                world[i][j].Q3_temp = ( ( world[i - 1][j - 1].Q3_temp 
                                    + world[i - 1][j + 1].Q3_temp )/SQRT_2
                                    + world[i - 1][j].Q3_temp + world[i][j - 1].Q3_temp 
                                    + world[i][j].Q3_temp*10 ) / ( 12 + SQRT_2 );
            }   
        }
    }

    for( int i = width - 2 ; i > 0 ; i-- )
    {
        for( int j = height - 2 ; j > 0 ; j-- )
        {
            if( world[i][j].state == LAND )
            {
                world[i][j].Q2_Q4_temp = ( ( world[i + 1][j + 1].Q2_Q4_temp 
                                    + world[i + 1][j - 1].Q2_Q4_temp )/SQRT_2
                                    + world[i + 1][j].Q2_Q4_temp + world[i][j + 1].Q2_Q4_temp
                                    + world[i][j].Q2_Q4_temp*2 ) / ( 4 + SQRT_2 );

                world[i][j].Q1_temp = ( ( world[i + 1][j + 1].Q1_temp 
                                    + world[i + 1][j - 1].Q1_temp )/SQRT_2
                                    + world[i + 1][j].Q1_temp + world[i][j + 1].Q1_temp
                                    + world[i][j].Q1_temp*2 ) / ( 4 + SQRT_2 );

                world[i][j].Q3_temp = ( ( world[i + 1][j + 1].Q3_temp 
                                    + world[i + 1][j - 1].Q3_temp )/SQRT_2
                                    + world[i + 1][j].Q3_temp + world[i][j + 1].Q3_temp
                                    + world[i][j].Q3_temp*2 ) / ( 4 + SQRT_2 );
            }
            else
            {
                world[i][j].Q2_Q4_temp = ( ( world[i + 1][j + 1].Q2_Q4_temp 
                                    + world[i + 1][j - 1].Q2_Q4_temp )/SQRT_2
                                    + world[i + 1][j].Q2_Q4_temp + world[i][j + 1].Q2_Q4_temp
                                    + world[i][j].Q2_Q4_temp*10 ) / ( 12 + SQRT_2 );

                world[i][j].Q1_temp = ( ( world[i + 1][j + 1].Q1_temp 
                                    + world[i + 1][j - 1].Q1_temp )/SQRT_2
                                    + world[i + 1][j].Q1_temp + world[i][j + 1].Q1_temp
                                    + world[i][j].Q1_temp*10 ) / ( 12 + SQRT_2 );

                world[i][j].Q3_temp = ( ( world[i + 1][j + 1].Q3_temp 
                                    + world[i + 1][j - 1].Q3_temp )/SQRT_2
                                    + world[i + 1][j].Q3_temp + world[i][j + 1].Q3_temp
                                    + world[i][j].Q3_temp*10 ) / ( 12 + SQRT_2 );
            }
        }
    }
}

void world_map::color_temp()
{
    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            world[i][j].Q2_Q4_temp_color[0] = 127.5 - world[i][j].Q2_Q4_temp*127.5/35;
            world[i][j].Q2_Q4_temp_color[1] = 0;
            world[i][j].Q2_Q4_temp_color[2] = 127.5 + world[i][j].Q2_Q4_temp*127.5/35;

            world[i][j].Q1_temp_color[0] = 127.5 - world[i][j].Q1_temp*127.5/35;
            world[i][j].Q1_temp_color[1] = 0;
            world[i][j].Q1_temp_color[2] = 127.5 + world[i][j].Q1_temp*127.5/35;

            world[i][j].Q3_temp_color[0] = 127.5 - world[i][j].Q3_temp*127.5/35;
            world[i][j].Q3_temp_color[1] = 0;
            world[i][j].Q3_temp_color[2] = 127.5 + world[i][j].Q3_temp*127.5/35;
        }
    }
}
