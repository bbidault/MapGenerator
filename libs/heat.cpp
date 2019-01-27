#include "world_map.h"
#include "common.h"


void world_map::create_heat()
{
    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            /// the temperature is affected by the latitude
            world[i][j].temperature += 25 - ( abs( 50 - j*100/height ) );            

            /// the temperature is effected by the altitude
            if( world[i][j].altitude >= 0 )
            {
                world[i][j].temperature -= world[i][j].altitude/200;
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
                world[i][j].temperature = ( ( world[i - 1][j - 1].temperature + world[i - 1][j + 1].temperature )/SQRT_2
                                    + world[i - 1][j].temperature + world[i][j - 1].temperature 
                                    + world[i][j].temperature*2 ) / ( 4 + SQRT_2 );
            }
            else
            {
                world[i][j].temperature = ( ( world[i - 1][j - 1].temperature + world[i - 1][j + 1].temperature )/SQRT_2
                                    + world[i - 1][j].temperature + world[i][j - 1].temperature 
                                    + world[i][j].temperature*10 ) / ( 12 + SQRT_2 );
            }   
        }
    }

    for( int i = width - 2 ; i > 0 ; i-- )
    {
        for( int j = height - 2 ; j > 0 ; j-- )
        {
            if( world[i][j].state == LAND )
            {
                world[i][j].temperature = ( ( world[i + 1][j + 1].temperature + world[i + 1][j - 1].temperature )/SQRT_2
                                    + world[i + 1][j].temperature + world[i][j + 1].temperature
                                    + world[i][j].temperature*2 ) / ( 4 + SQRT_2 );
            }
            else
            {
                world[i][j].temperature = ( ( world[i + 1][j + 1].temperature + world[i + 1][j - 1].temperature )/SQRT_2
                                    + world[i + 1][j].temperature + world[i][j + 1].temperature
                                    + world[i][j].temperature*10 ) / ( 12 + SQRT_2 );
            }
        }
    }
}

void world_map::color_heat()
{
    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            world[i][j].heat_color[0] = 127.5 - world[i][j].temperature*127.5/25;
            world[i][j].heat_color[1] = 0;
            world[i][j].heat_color[2] = 127.5 + world[i][j].temperature*127.5/25;
        }
    }
}
