#include "world_map.h"
#include "common.h"


void world_map::create_temp()
{
    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            /// the temperature is affected by the latitude
            world[i][j].avg_temp += 25 - ( abs( 30 - j*60/height ) );          

            /// the temperature is effected by the altitude
            if( world[i][j].altitude >= 0 )
            {
                world[i][j].avg_temp -= world[i][j].altitude/137;
            }

            /// the average minimum and maximum temperature are affected by the latitude
            if( world[i][j].state == LAND )
            {
                world[i][j].max_temp = world[i][j].avg_temp + 10 + ( abs( 10 - j*20/height ) );
                world[i][j].min_temp = world[i][j].avg_temp - 10 - ( abs( 10 - j*20/height ) );
            }
            else
            {
                world[i][j].max_temp = world[i][j].avg_temp + 1 + ( abs( 1 - j*2/height ) );
                world[i][j].min_temp = world[i][j].avg_temp - 1 - ( abs( 1 - j*2/height ) );
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
                world[i][j].avg_temp = ( ( world[i - 1][j - 1].avg_temp 
                                    + world[i - 1][j + 1].avg_temp )/SQRT_2
                                    + world[i - 1][j].avg_temp + world[i][j - 1].avg_temp 
                                    + world[i][j].avg_temp*2 ) / ( 4 + SQRT_2 );

                world[i][j].min_temp = ( ( world[i - 1][j - 1].min_temp 
                                    + world[i - 1][j + 1].min_temp )/SQRT_2
                                    + world[i - 1][j].min_temp + world[i][j - 1].min_temp 
                                    + world[i][j].min_temp*2 ) / ( 4 + SQRT_2 );

                world[i][j].max_temp = ( ( world[i - 1][j - 1].max_temp 
                                    + world[i - 1][j + 1].max_temp )/SQRT_2
                                    + world[i - 1][j].max_temp + world[i][j - 1].max_temp 
                                    + world[i][j].max_temp*2 ) / ( 4 + SQRT_2 );
            }
            else
            {
                world[i][j].avg_temp = ( ( world[i - 1][j - 1].avg_temp 
                                    + world[i - 1][j + 1].avg_temp )/SQRT_2
                                    + world[i - 1][j].avg_temp + world[i][j - 1].avg_temp 
                                    + world[i][j].avg_temp*10 ) / ( 12 + SQRT_2 );

                world[i][j].min_temp = ( ( world[i - 1][j - 1].min_temp 
                                    + world[i - 1][j + 1].min_temp )/SQRT_2
                                    + world[i - 1][j].min_temp + world[i][j - 1].min_temp 
                                    + world[i][j].min_temp*10 ) / ( 12 + SQRT_2 );

                world[i][j].max_temp = ( ( world[i - 1][j - 1].max_temp 
                                    + world[i - 1][j + 1].max_temp )/SQRT_2
                                    + world[i - 1][j].max_temp + world[i][j - 1].max_temp 
                                    + world[i][j].max_temp*10 ) / ( 12 + SQRT_2 );
            }   
        }
    }

    for( int i = width - 2 ; i > 0 ; i-- )
    {
        for( int j = height - 2 ; j > 0 ; j-- )
        {
            if( world[i][j].state == LAND )
            {
                world[i][j].avg_temp = ( ( world[i + 1][j + 1].avg_temp 
                                    + world[i + 1][j - 1].avg_temp )/SQRT_2
                                    + world[i + 1][j].avg_temp + world[i][j + 1].avg_temp
                                    + world[i][j].avg_temp*2 ) / ( 4 + SQRT_2 );

                world[i][j].min_temp = ( ( world[i + 1][j + 1].min_temp 
                                    + world[i + 1][j - 1].min_temp )/SQRT_2
                                    + world[i + 1][j].min_temp + world[i][j + 1].min_temp
                                    + world[i][j].min_temp*2 ) / ( 4 + SQRT_2 );

                world[i][j].max_temp = ( ( world[i + 1][j + 1].max_temp 
                                    + world[i + 1][j - 1].max_temp )/SQRT_2
                                    + world[i + 1][j].max_temp + world[i][j + 1].max_temp
                                    + world[i][j].max_temp*2 ) / ( 4 + SQRT_2 );
            }
            else
            {
                world[i][j].avg_temp = ( ( world[i + 1][j + 1].avg_temp 
                                    + world[i + 1][j - 1].avg_temp )/SQRT_2
                                    + world[i + 1][j].avg_temp + world[i][j + 1].avg_temp
                                    + world[i][j].avg_temp*10 ) / ( 12 + SQRT_2 );

                world[i][j].min_temp = ( ( world[i + 1][j + 1].min_temp 
                                    + world[i + 1][j - 1].min_temp )/SQRT_2
                                    + world[i + 1][j].min_temp + world[i][j + 1].min_temp
                                    + world[i][j].min_temp*10 ) / ( 12 + SQRT_2 );

                world[i][j].max_temp = ( ( world[i + 1][j + 1].max_temp 
                                    + world[i + 1][j - 1].max_temp )/SQRT_2
                                    + world[i + 1][j].max_temp + world[i][j + 1].max_temp
                                    + world[i][j].max_temp*10 ) / ( 12 + SQRT_2 );
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
            world[i][j].avg_temp_color[0] = 127.5 - world[i][j].avg_temp*127.5/35;
            world[i][j].avg_temp_color[1] = 0;
            world[i][j].avg_temp_color[2] = 127.5 + world[i][j].avg_temp*127.5/35;

            world[i][j].min_temp_color[0] = 127.5 - world[i][j].min_temp*127.5/35;
            world[i][j].min_temp_color[1] = 0;
            world[i][j].min_temp_color[2] = 127.5 + world[i][j].min_temp*127.5/35;

            world[i][j].max_temp_color[0] = 127.5 - world[i][j].max_temp*127.5/35;
            world[i][j].max_temp_color[1] = 0;
            world[i][j].max_temp_color[2] = 127.5 + world[i][j].max_temp*127.5/35;
        }
    }
}
